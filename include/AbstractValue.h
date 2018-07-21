#ifndef PROMISE_INTERFERENCE_ABSTRACT_VALUE_H
#define PROMISE_INTERFERENCE_ABSTRACT_VALUE_H

#include "scope.h"
#include "utilities.h"

class AbstractValue {
  public:
    AbstractValue(const scope_t &scope, const sexp_type_t &type)
        : scope_(scope), type_(type) {}

    const scope_t &get_scope() const { return scope_; }

    const sexp_type_t &get_type() const { return type_; }

    bool operator==(const AbstractValue &rhs) const {
        return (get_scope() == rhs.get_scope() && get_type() == rhs.get_type());
    }

    bool operator!=(const AbstractValue &rhs) const {
        return !(operator==(rhs));
    }

    const std::string to_string() const {
        std::stringstream stream;
        stream << "AbstractValue(" << get_scope() << ", " << get_type() << ")";
        return stream.str();
    }

  private:
    scope_t scope_;
    sexp_type_t type_;
};

std::ostream &operator<<(std::ostream &os, const AbstractValue &abstract_value);

#endif /* PROMISE_INTERFERENCE_ABSTRACT_VALUE_H */
