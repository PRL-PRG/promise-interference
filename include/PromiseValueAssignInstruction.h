#ifndef PROMISE_INTERFERENCE_PROMISE_VALUE_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_VALUE_ASSIGN_INSTRUCTION_H

#include "PromiseValueInstruction.h"
#include <sstream>

class PromiseValueAssignInstruction : public PromiseValueInstruction {
  public:
    explicit PromiseValueAssignInstruction(const promise_id_t id,
                                           const sexp_type_t &value_type)
        : PromiseValueInstruction{id, value_type} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_value_type();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseValueAssignInstruction parse_arguments(const char *begin,
                                                         char **end);
};

#endif /* PROMISE_INTERFERENCE_PROMISE_VALUE_ASSIGN_INSTRUCTION_H */
