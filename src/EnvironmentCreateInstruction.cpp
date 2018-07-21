#include "include/EnvironmentCreateInstruction.h"

const opcode_t &EnvironmentCreateInstruction::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_CREATE;
}

EnvironmentCreateInstruction
EnvironmentCreateInstruction::parse_arguments(const char *begin, char **end) {

    environment_id_t id{parse_environment_id(begin, end)};

    return EnvironmentCreateInstruction{id};
}
