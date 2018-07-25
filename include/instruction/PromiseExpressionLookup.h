#ifndef PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H

#include "PromiseExpression.h"
#include <sstream>

namespace instruction {

class PromiseExpressionLookup : public PromiseExpression {
  public:
    explicit PromiseExpressionLookup(const promise_id_t id,
                                     const expression_t &expression)
        : PromiseExpression{id, expression} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_expression() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseExpressionLookup parse_arguments(const char *begin,
                                                   char **end);
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_EXPRESSION_LOOKUP_INSTRUCTION_H */
