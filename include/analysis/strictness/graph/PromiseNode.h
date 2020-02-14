#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_PROMISE_NODE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_PROMISE_NODE_H

#include "Node.h"
#include <ostream>

namespace analysis::strictness::graph {

class CallNode;

class PromiseNode : public Node {
  public:
    explicit PromiseNode(promise_id_t promise_id)
        : Node(Node::Type::Promise), promise_id_(promise_id), forced_(false),
          metaprogrammed_(false),
          dot_node_name_("p_" + std::to_string(promise_id)),
          parameter_name_("?"), formal_parameter_position_(-1),
          parent_call_(nullptr) {}

    promise_id_t get_promise_id() const { return promise_id_; }

    void set_forced() { forced_ = true; }

    bool is_forced() const { return forced_; }

    void set_metaprogrammed() { metaprogrammed_ = true; }

    bool is_metaprogrammed() const { return metaprogrammed_; }

    void set_parameter_name(const variable_name_t &parameter_name) {
        parameter_name_ = parameter_name;
    }

    const variable_name_t &get_parameter_name() const {
        return parameter_name_;
    }

    void set_formal_parameter_position(int formal_parameter_position) {
        formal_parameter_position_ = formal_parameter_position;
    }

    const int get_formal_parameter_position() const {
        return formal_parameter_position_;
    }

    void set_parent_call(CallNode *parent_call) { parent_call_ = parent_call; }

    CallNode *get_parent_call() { return parent_call_; }

    const CallNode *get_parent_call() const { return parent_call_; }

    const std::string &get_dot_node_name() const override {
        return dot_node_name_;
    }

    void to_dot(std::ostream &os) const override {
        os << get_dot_node_name();
        os << " [shape=circle label="
           << "<"
           << "<b>"
           << "p_" << get_promise_id() << "</b>"
           << "<br/>"
           << "<i>" << get_parameter_name() << "</i>"
           << "<br/>" << get_formal_parameter_position() << ">";

        os << " style=\"filled";

        if (is_metaprogrammed()) {
            os << ", dotted";
        }

        os << "\"";

        if (is_forced()) {
            os << " fillcolor=white";
        } else {
            os << " fillcolor=lightblue";
        }

        os << "]"
           << ";" << std::endl;
    }

  private:
    promise_id_t promise_id_;
    bool forced_;
    bool metaprogrammed_;
    const std::string dot_node_name_;
    variable_name_t parameter_name_;
    int formal_parameter_position_;
    CallNode *parent_call_;
};

} // namespace analysis::strictness::graph

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_PROMISE_NODE_H */
