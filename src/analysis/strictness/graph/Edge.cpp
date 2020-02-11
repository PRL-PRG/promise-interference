#include "analysis/strictness/graph/Edge.h"
#include "analysis/strictness/graph/Node.h"

void analysis::strictness::graph::Edge::to_dot(std::ostream &os) const {
    const Node *source = get_source();
    const Node *target = get_target();
    const Annotation &annotation = get_annotation();

    os << source->get_dot_node_name();
    os << " -> ";
    os << target->get_dot_node_name();
    os << "[label="
       << "<";
    annotation.to_dot(os);
    os << ">";

    if (get_type() == Type::Call) {
        os << " color=green";
    } else if (get_type() == Type::Argument) {
        os << " color=blue";
    } else {
        os << " color=red";
    }

    os << "];" << std::endl;
}
