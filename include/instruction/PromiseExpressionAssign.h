#ifndef PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H

#include "PromiseExpression.h"
#include <sstream>

namespace instruction {

class PromiseExpressionAssign : public PromiseExpression {
  public:
    explicit PromiseExpressionAssign(const promise_id_t id,
                                     const expression_t &expression)
        : PromiseExpression{id, expression} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_expression() << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static PromiseExpressionAssign parse_arguments(const char *begin,
                                                   char **end);
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::PromiseExpressionAssign &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_PROMISE_EXPRESSION_ASSIGN_INSTRUCTION_H */
