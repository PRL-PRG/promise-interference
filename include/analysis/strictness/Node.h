#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H

#include "Edge.h"
#include <vector>

namespace analysis::strictness {

class Node {
  public:
    enum class Type { Call, Promise };

    explicit Node(Type type) : type_(type) {}

    virtual ~Node(){};

    virtual const std::string &get_dot_node_name() const = 0;

    virtual void to_dot(std::ostream &os) const = 0;

    Type get_type() const { return type_; }

    bool is_promise() const { return get_type() == Type::Promise; }

    bool is_call() const { return get_type() == Type::Call; }

    Edge &add_edge(Node *target) {
        for (Edge &edge : edges_) {
            if (edge.get_target() == target) {
                return edge;
            }
        }

        edges_.push_back(Edge(this, target));

        return edges_.back();
    }

    Edge &get_edge(Node *target) {
        for (Edge &edge : edges_) {
            if (edge.get_target() == target) {
                return edge;
            }
        }
    }

    const std::vector<Edge> get_edges() const { return edges_; }

  private:
    Type type_;
    std::vector<Edge> edges_;
};

} // namespace analysis::strictness

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H */
