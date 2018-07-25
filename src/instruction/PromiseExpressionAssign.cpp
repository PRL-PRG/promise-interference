#include "instruction/PromiseExpressionAssign.h"

namespace instruction {

const opcode_t &PromiseExpressionAssign::get_opcode() {
    return Instruction::OPCODE_PROMISE_EXPRESSION_ASSIGN;
}

PromiseExpressionAssign
PromiseExpressionAssign::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    expression_t expression{parse_expression(*end + 1, end)};

    return PromiseExpressionAssign{id, expression};
}
}
