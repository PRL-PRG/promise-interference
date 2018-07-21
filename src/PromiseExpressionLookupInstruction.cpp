#include "PromiseExpressionLookupInstruction.h"

const opcode_t &PromiseExpressionLookupInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_EXPRESSION_LOOKUP;
}

PromiseExpressionLookupInstruction
PromiseExpressionLookupInstruction::parse_arguments(const char *begin,
                                                    char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    expression_t expression{parse_expression(*end + 1, end)};

    return PromiseExpressionLookupInstruction{id, expression};
}
