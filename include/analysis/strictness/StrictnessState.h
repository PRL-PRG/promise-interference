#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H

#include "graph/CallNode.h"
#include "graph/PromiseNode.h"
#include "utilities.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* There are 5 kinds of edges:
   - write-read edge: An edge from write of x to a subsequent read of x
   - read-write edge: An edge from read of x to a subsequent write of x
   - create-force edge: An edge from creation point of promise to its forcing
   point
   - force-create edge: An edge from forcing point of a promise to the creation
   point
                        of the first promise in its body.
   - creation-creation edge: An edge from the creation point of a promise to the
   next
                             promise created in the same parent promise.

 */
namespace analysis::strictness {
class StrictnessState {
  public:
    // std::size_t UNDEFINED_INDEX = std::numeric_limits<std::size_t>::max();
    StrictnessState() {}

    // create edge and update variable writer
    void write_variable(const variable_id_t variable_id,
                        const variable_name_t &variable_name) {
        /* if stack is empty, it means that side effects are happening at a
         * global level and there is no context to deal with. */
        if (stack_.empty()) {
            return;
        }

        /* since the current context is writing to the variable, it has to be
         * placed after any parent context that either read from or wrote to the
         * variable. We want to retain order of variable read-write and
         * write-write */

        graph::Node *current_context = stack_.back();
        std::vector<graph::Node *> &user_seq = users_[variable_id];
        if (user_seq.size() != 0) {
            graph::Node *user_context = user_seq.back();
            /* create edge iff the two nodes are different */
            if (user_context != current_context) {
                user_context->add_edge(current_context)
                    .get_annotation()
                    .get_write_variables()
                    .insert(variable_name);
            }
        }

        /* we have to add the current context as one of the writers and
         * users of this variable for future consideration.*/
        writers_[variable_id].push_back(stack_.back());
        user_seq.push_back(stack_.back());
    }

    // create edge and update variable reader
    void read_variable(const variable_id_t variable_id,
                       const variable_name_t &variable_name) {
        /* if stack is empty, it means that side effects are happening at a
         * global level and there is no context to deal with. */
        if (stack_.empty()) {
            return;
        }

        /* since the current context is reading from the variable, it has to be
         * placed after any parent context that wrote to the
         * variable. We want to retain order of variable write-read. The order
         * of variable read-read is not important. */

        graph::Node *current_context = stack_.back();
        std::vector<graph::Node *> &writer_seq = writers_[variable_id];
        if (writer_seq.size() != 0) {
            graph::Node *writer_context = writer_seq.back();
            /* create edge iff the two nodes are different */
            if (writer_context != current_context) {
                writer_context->add_edge(current_context)
                    .get_annotation()
                    .get_read_variables()
                    .insert(variable_name);
            }
        }

        /* we have to add the current context as one of the writers and
         * users of this variable for future consideration.*/
        readers_[variable_id].push_back(stack_.back());
        users_[variable_id].push_back(stack_.back());
    }

    graph::PromiseNode *create_promise(const promise_id_t promise_id) {
        graph::PromiseNode *promise = new graph::PromiseNode(promise_id);

        promises_.push_back(promise);

        promise_map_[promise_id] = promise;

        return promise;
    }

    graph::PromiseNode *get_or_create_promise(const promise_id_t promise_id) {
        auto iter = promise_map_.find(promise_id);

        if (iter == promise_map_.end()) {
            return create_promise(promise_id);
        }

        return iter->second;
    }

    void associate_promise(promise_id_t promise_id, call_id_t call_id,
                           int formal_paramter_position,
                           const variable_name_t &variable_name) {
        graph::Node *node = stack_.back();

        if (node->is_promise()) {
            std::cerr << "Promise encountered on stack on function exit";
            exit(EXIT_FAILURE);
        }

        graph::CallNode *call = static_cast<graph::CallNode *>(node);

        if (call->get_call_id() != call_id) {
            std::cerr
                << "Function entry call id mismatches function exit call id.";
            exit(EXIT_FAILURE);
        }

        graph::PromiseNode *promise = get_or_create_promise(promise_id);
        promise->set_parameter_name(variable_name);
        promise->set_formal_parameter_position(formal_paramter_position);
        call->add_edge(promise).set_type(graph::Edge::Type::Argument);
        call->add_argument(promise);
    }

    void enter_promise(const promise_id_t promise_id) {
        graph::PromiseNode *promise = get_or_create_promise(promise_id);

        promise->set_forced();

        stack_.push_back(promise);
    }

    void exit_promise(const promise_id_t promise_id) {
        graph::Node *node = stack_.back();

        if (node->is_call()) {
            std::cerr << "Function encountered on stack on promise exit";
            exit(EXIT_FAILURE);
        }

        graph::PromiseNode *promise = static_cast<graph::PromiseNode *>(node);

        if (promise->get_promise_id() != promise_id) {
            std::cerr << "Promise entry id mismatches promise exit id.";
            exit(EXIT_FAILURE);
        }

        stack_.pop_back();
    }

    void metaprogram_promise(const promise_id_t promise_id) {
        graph::PromiseNode *promise = get_or_create_promise(promise_id);

        promise->set_metaprogrammed();
    }

    void enter_function(const function_id_t &function_id,
                        const call_id_t call_id,
                        const std::string &function_names) {
        graph::CallNode *call =
            new graph::CallNode(call_id, function_id, function_names);

        calls_.push_back(call);

        graph::Node *caller = nullptr;

        if (!stack_.empty()) {
            caller = stack_.back();
        }

        if (caller != nullptr) {
            caller->add_edge(call).set_type(graph::Edge::Type::Call);
        }

        stack_.push_back(call);
    }

    void exit_function(const call_id_t call_id) {
        graph::Node *node = stack_.back();

        if (node->is_promise()) {
            std::cerr << "Promise encountered on stack on function exit";
            exit(EXIT_FAILURE);
        }

        graph::CallNode *call = static_cast<graph::CallNode *>(node);

        if (call->get_call_id() != call_id) {
            std::cerr
                << "Function entry call id mismatches function exit call id.";
            exit(EXIT_FAILURE);
        }

        stack_.pop_back();
    }

    std::string indent(int indentation) const {
        return std::string(indentation, ' ');
    }

    void to_dot(std::ostream &os) const {

        os << "digraph {" << std::endl;

        os << indent(4) << "{ /* nodes */" << std::endl;

        for (const graph::CallNode *call : calls_) {
            os << indent(8);
            call->to_dot(os);
        }

        for (const graph::PromiseNode *promise : promises_) {
            os << indent(8);
            promise->to_dot(os);
        }

        os << indent(4) << "}" << std::endl << std::endl;

        os << indent(4) << "{ /* edges */" << std::endl;

        for (const graph::CallNode *call : calls_) {
            for (const graph::Edge &edge : call->get_edges()) {
                os << indent(8);
                edge.to_dot(os);
            }
        }

        for (const graph::PromiseNode *promise : promises_) {
            for (const graph::Edge &edge : promise->get_edges()) {
                os << indent(8);
                edge.to_dot(os);
            }
        }

        os << indent(4) << "}" << std::endl << std::endl;

        os << indent(4) << "/* clusters */" << std::endl << std::endl;

        for (const graph::CallNode *call : calls_) {

            os << indent(4) << "subgraph cluster_" << call->get_call_id()
               << " {" << std::endl;

            os << indent(8) << "label="
               << "<" << call->get_call_id() << "<br/>"
               << "<font point-size='10'>" << call->get_function_id()
               << "</font>"
               << "<br/>" << call->get_function_names() << ">"
               << ";" << std::endl;

            os << indent(8) << call->get_dot_node_name() << "; ";

            for (const graph::PromiseNode *promise : call->get_arguments()) {
                os << promise->get_dot_node_name() << "; ";
            }

            os << std::endl;

            os << indent(4) << "}" << std::endl;
        }

        os << "}" << std::endl;
    }

  private:
    std::vector<graph::Node *> stack_;
    std::vector<graph::CallNode *> calls_;
    std::vector<graph::PromiseNode *> promises_;
    std::unordered_map<variable_id_t, std::vector<graph::Node *>> readers_;
    std::unordered_map<variable_id_t, std::vector<graph::Node *>> writers_;
    std::unordered_map<variable_id_t, std::vector<graph::Node *>> users_;
    std::unordered_map<promise_id_t, graph::PromiseNode *> promise_map_;
};
} // namespace analysis::strictness

inline std::ostream &
operator<<(std::ostream &os,
           const analysis::strictness::StrictnessState &state) {

    state.to_dot(os);
    /*
    for (const auto &kv : state.get_edges()) {
        os << state.get_node(kv.first) << " : ";
        for (const auto &value : kv.second) {
            os << state.get_node(value) << " ";
        }
        os << std::endl;
    }
    */
    return os;
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H */
