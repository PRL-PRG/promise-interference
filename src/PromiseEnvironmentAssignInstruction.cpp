#include "include/PromiseEnvironmentAssignInstruction.h"

const opcode_t &PromiseEnvironmentAssignInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENVIRONMENT_ASSIGN;
}

PromiseEnvironmentAssignInstruction
PromiseEnvironmentAssignInstruction::parse_arguments(const char *begin,
                                                     char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    return PromiseEnvironmentAssignInstruction{id, environment_id};
}
