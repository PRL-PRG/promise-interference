#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_EDGE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_EDGE_H

#include "Annotation.h"
#include <ostream>

namespace analysis::strictness {

class Node;

class Edge {
  public:
    enum class Type { Undefined, Argument, Call };

    explicit Edge(Node *source, Node *target)
        : source_(source), target_(target), type_(Type::Undefined) {}

    Node *get_source() { return source_; }

    const Node *get_source() const { return source_; }

    Node *get_target() { return target_; }

    const Node *get_target() const { return target_; }

    Type get_type() const { return type_; }

    void set_type(Type type) { type_ = type; }

    Annotation &get_annotation() { return annotation_; }

    const Annotation &get_annotation() const { return annotation_; }

    void to_dot(std::ostream &os) const;

  private:
    Node *source_;
    Node *target_;
    Type type_;
    Annotation annotation_;
};

} // namespace analysis::strictness

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_EDGE_H */
