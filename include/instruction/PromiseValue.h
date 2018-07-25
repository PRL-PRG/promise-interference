#ifndef PROMISE_INTERFERENCE_PROMISE_VALUE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_VALUE_INSTRUCTION_H

#include "Instruction.h"

namespace instruction {

class PromiseValue : public Instruction {
  public:
    explicit PromiseValue(const promise_id_t id, const sexp_type_t &value_type)
        : Instruction{}, id_{id}, value_type_{value_type} {}

    const promise_id_t get_id() const { return id_; }

    const sexp_type_t &get_value_type() const { return value_type_; }

  private:
    promise_id_t id_;
    sexp_type_t value_type_;
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_VALUE_INSTRUCTION_H */
