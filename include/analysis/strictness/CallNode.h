#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_CALL_NODE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_CALL_NODE_H

#include "Node.h"
#include "utilities.h"

namespace analysis::strictness {

class PromiseNode;

class CallNode : public Node {
  public:
    explicit CallNode(call_id_t call_id, const function_id_t &function_id,
                      const std::string &function_names)
        : Node(Node::Type::Call), call_id_(call_id), function_id_(function_id),
          function_names_(function_names),
          dot_node_name_("c_" + std::to_string(call_id)) {}

    call_id_t get_call_id() const { return call_id_; }

    const function_id_t &get_function_id() const { return function_id_; }

    const std::string &get_dot_node_name() const override {
        return dot_node_name_;
    }

    const std::string &get_function_names() const { return function_names_; }

    void to_dot(std::ostream &os) const override {
        os << get_dot_node_name();
        os << " [shape=box label="
           << "<"
           << "<b>" << get_dot_node_name() << "</b>"
           << ">"
           << "];" << std::endl;
    }

    void add_argument(PromiseNode *promise) { arguments_.push_back(promise); }

    const std::vector<PromiseNode *> &get_arguments() const {
        return arguments_;
    }

  private:
    const call_id_t call_id_;
    const function_id_t function_id_;
    const std::string function_names_;
    const std::string dot_node_name_;
    std::vector<PromiseNode *> arguments_;
};

} // namespace analysis::strictness

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_CALL_NODE_H */

