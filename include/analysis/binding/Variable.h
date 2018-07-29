#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_VARIABLE_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_VARIABLE_H

#include "utilities.h"
#include <iostream>
#include <sstream>

namespace analysis::binding {

class Variable {
  public:
    Variable(const variable_id_t &id, const variable_name_t &name)
        : id_(id), name_(name) {}

    const variable_name_t &get_name() const { return name_; }

    const variable_id_t get_id() const { return id_; }

    bool operator==(const Variable &rhs) const {
        if (get_id() == rhs.get_id()) {
            if (get_name() != rhs.get_name()) {
                std::cerr << "variable name mismatch" << std::endl;
                std::cerr << "variable id: " << get_id() << std::endl;
                std::cerr << "name: " << get_name() << std::endl;
                std::cerr << "name: " << rhs.get_name() << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        return true;
    }

    bool operator!=(const Variable &rhs) const { return !(operator==(rhs)); }

    std::string to_string() const {
        std::stringstream stream;
        stream << "Variable(" << get_id() << ", " << get_name() << ")";
        return stream.str();
    }

  private:
    variable_id_t id_;
    variable_name_t name_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::binding::Variable &variable) {
    return os << variable.to_string();
}

namespace std {

template <> struct hash<analysis::binding::Variable> {

    std::size_t operator()(const analysis::binding::Variable &variable) const {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + std::hash<variable_id_t>()(variable.get_id());
        res = res * 31 + std::hash<variable_name_t>()(variable.get_name());
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_VARIABLE_H */
