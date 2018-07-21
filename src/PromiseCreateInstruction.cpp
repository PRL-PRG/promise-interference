#include "PromiseCreateInstruction.h"

const opcode_t &PromiseCreateInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_CREATE;
}

PromiseCreateInstruction
PromiseCreateInstruction::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    expression_t expression{parse_expression(*end + 1, end)};

    return PromiseCreateInstruction{id, environment_id, expression};
}
