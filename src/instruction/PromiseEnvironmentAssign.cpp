#include "instruction/PromiseEnvironmentAssign.h"

namespace instruction {

const opcode_t &PromiseEnvironmentAssign::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENVIRONMENT_ASSIGN;
}

PromiseEnvironmentAssign
PromiseEnvironmentAssign::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    return PromiseEnvironmentAssign{id, environment_id};
}
}
