#include "EnvironmentVariableAssignInstruction.h"
#include "utilities.h"
#include <cstring>

const opcode_t &EnvironmentVariableAssignInstruction::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_VARIABLE_ASSIGN;
}

EnvironmentVariableAssignInstruction
EnvironmentVariableAssignInstruction::parse_arguments(const char *begin,
                                                      char **end) {
    environment_id_t environment_id{parse_environment_id(begin, end)};

    variable_id_t variable_id{parse_variable_id(*end + 1, end)};

    variable_name_t variable_name{parse_variable_name(*end + 1, end)};

    sexp_type_t value_type{parse_sexp_type(*end + 1, end)};

    return EnvironmentVariableAssignInstruction{
        environment_id, Variable{variable_id, variable_name}, value_type};
}
