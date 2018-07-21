#ifndef PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H

#include "PromiseExpressionInstruction.h"
#include <sstream>

class PromiseExpressionAssignInstruction : public PromiseExpressionInstruction {
  public:
    explicit PromiseExpressionAssignInstruction(const promise_id_t id,
                                                const expression_t &expression)
        : PromiseExpressionInstruction{id, expression} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_expression() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseExpressionAssignInstruction parse_arguments(const char *begin,
                                                              char **end);
};

#endif /* PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H */
