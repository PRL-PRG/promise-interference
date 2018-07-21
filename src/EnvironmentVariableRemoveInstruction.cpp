#include "EnvironmentVariableRemoveInstruction.h"
#include <cstring>

const opcode_t &EnvironmentVariableRemoveInstruction::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_VARIABLE_REMOVE;
}

EnvironmentVariableRemoveInstruction
EnvironmentVariableRemoveInstruction::parse_arguments(const char *begin,
                                                      char **end) {
    environment_id_t environment_id{parse_environment_id(begin, end)};

    variable_id_t variable_id{parse_variable_id(*end + 1, end)};

    variable_name_t variable_name{parse_variable_name(*end + 1, end)};

    return EnvironmentVariableRemoveInstruction{
        environment_id, Variable{variable_id, variable_name}};
}
