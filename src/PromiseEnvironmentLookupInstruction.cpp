#include "include/PromiseEnvironmentLookupInstruction.h"

const opcode_t &PromiseEnvironmentLookupInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENVIRONMENT_LOOKUP;
}

PromiseEnvironmentLookupInstruction
PromiseEnvironmentLookupInstruction::parse_arguments(const char *begin,
                                                     char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    return PromiseEnvironmentLookupInstruction{id, environment_id};
}
