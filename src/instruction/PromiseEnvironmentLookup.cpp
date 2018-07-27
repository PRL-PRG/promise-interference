#include "instruction/PromiseEnvironmentLookup.h"

namespace instruction {

const opcode_t &PromiseEnvironmentLookup::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENVIRONMENT_LOOKUP;
}

PromiseEnvironmentLookup
PromiseEnvironmentLookup::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    parse_operand_separator(*end, end);

    environment_id_t environment_id{parse_environment_id(*end, end)};

    parse_instruction_separator(*end, end);

    return PromiseEnvironmentLookup{id, environment_id};
}
}
