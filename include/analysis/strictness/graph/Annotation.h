#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_ANNOTATION_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_ANNOTATION_H

#include "utilities.h"
#include <ostream>
#include <unordered_set>

namespace analysis::strictness::graph {

class Annotation {
  public:
    explicit Annotation() {}

    std::unordered_set<variable_name_t> &get_read_variables() {
        return read_variables_;
    }

    const std::unordered_set<variable_name_t> &get_read_variables() const {
        return read_variables_;
    }

    std::unordered_set<variable_name_t> &get_write_variables() {
        return write_variables_;
    }

    const std::unordered_set<variable_name_t> &get_write_variables() const {
        return write_variables_;
    }

    void to_dot(std::ostream &os) const {
        if (get_read_variables().size()) {
            os << "r(" << concatenate(get_read_variables()) << ")";
        }

        if (get_read_variables().size() && get_write_variables().size()) {
            os << "<br/>";
        }

        if (get_write_variables().size()) {
            os << "w(" << concatenate(get_write_variables()) << ")";
        }
    }

  private:
    std::unordered_set<variable_name_t> read_variables_;
    std::unordered_set<variable_name_t> write_variables_;
};

} // namespace analysis::strictness::graph

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_ANNOTATION_H */
