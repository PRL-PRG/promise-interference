#ifndef PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H

#include "PromiseExpressionInstruction.h"
#include <sstream>

class PromiseExpressionLookupInstruction : public PromiseExpressionInstruction {
  public:
    explicit PromiseExpressionLookupInstruction(const promise_id_t id,
                                                const expression_t &expression)
        : PromiseExpressionInstruction{id, expression} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_expression();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseExpressionLookupInstruction parse_arguments(const char *begin,
                                                              char **end);
};

#endif /* PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H */
