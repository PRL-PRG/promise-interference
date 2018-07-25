#include "instruction/EnvironmentVariableAssign.h"
#include "utilities.h"
#include <cstring>

namespace instruction {

const opcode_t &EnvironmentVariableAssign::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_VARIABLE_ASSIGN;
}

EnvironmentVariableAssign
EnvironmentVariableAssign::parse_arguments(const char *begin, char **end) {
    environment_id_t environment_id{parse_environment_id(begin, end)};

    variable_id_t variable_id{parse_variable_id(*end + 1, end)};

    variable_name_t variable_name{parse_variable_name(*end + 1, end)};

    sexp_type_t value_type{parse_sexp_type(*end + 1, end)};

    parse_record_separator(begin, end);

    return EnvironmentVariableAssign{
        environment_id, state::Variable{variable_id, variable_name},
        value_type};
}
}
