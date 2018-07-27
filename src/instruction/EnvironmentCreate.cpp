#include "instruction/EnvironmentCreate.h"

namespace instruction {

const opcode_t &EnvironmentCreate::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_CREATE;
}

EnvironmentCreate EnvironmentCreate::parse_arguments(const char *begin,
                                                     char **end) {

    environment_id_t id{parse_environment_id(begin, end)};

    parse_instruction_separator(*end, end);

    return EnvironmentCreate{id};
}
}
