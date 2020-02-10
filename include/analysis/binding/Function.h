#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_FUNCTION_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_FUNCTION_H

#include "utilities.h"
#include <sstream>

namespace analysis::binding {

class Function {
  public:
    explicit Function(const sexp_type_t &type, const function_id_t &id,
                      const call_id_t call_id,
                      const environment_id_t environment_id)
        : type_{type}, id_{id}, call_id_{call_id},
          environment_id_{environment_id} {}

    const sexp_type_t &get_type() const { return type_; }

    const function_id_t &get_id() const { return id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    const call_id_t get_call_id() const { return call_id_; }

    const std::string to_string() const {
        std::stringstream stream;
        stream << "Function(" << get_type() << ", " << get_id() << ", "
               << get_call_id() << ", " << get_environment_id() << ")";
        return stream.str();
    }

    bool operator==(const Function &rhs) const {
        return (get_type() == rhs.get_type() && get_id() == rhs.get_id() &&
                get_call_id() == rhs.get_call_id() &&
                get_environment_id() == rhs.get_environment_id());
    }

    bool operator!=(const Function &rhs) const { return !(operator==(rhs)); }

  private:
    sexp_type_t type_;
    function_id_t id_;
    call_id_t call_id_;
    environment_id_t environment_id_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::binding::Function &function) {
    return os << function.to_string();
}

namespace std {

template <> struct hash<analysis::binding::Function> {

    std::size_t operator()(const analysis::binding::Function &function) const {
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + std::hash<sexp_type_t>()(function.get_type());
        res = res * 31 + std::hash<function_id_t>()(function.get_id());
        res = res * 31 + std::hash<call_id_t>()(function.get_call_id());
        res = res * 31 +
              std::hash<environment_id_t>()(function.get_environment_id());
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_FUNCTION_H */