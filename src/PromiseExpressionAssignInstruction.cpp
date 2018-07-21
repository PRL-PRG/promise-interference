#include "include/PromiseExpressionAssignInstruction.h"

const opcode_t &PromiseExpressionAssignInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_EXPRESSION_ASSIGN;
}

PromiseExpressionAssignInstruction
PromiseExpressionAssignInstruction::parse_arguments(const char *begin,
                                                    char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    expression_t expression{parse_expression(*end + 1, end)};

    return PromiseExpressionAssignInstruction{id, expression};
}
