#include "instruction/EnvironmentVariableLookup.h"
#include <cstring>

namespace instruction {

const opcode_t &EnvironmentVariableLookup::get_opcode() {
    return Instruction::OPCODE_ENVIRONMENT_VARIABLE_LOOKUP;
}

EnvironmentVariableLookup
EnvironmentVariableLookup::parse_arguments(const char *begin, char **end) {

    environment_id_t environment_id{parse_environment_id(begin, end)};

    parse_operand_separator(*end, end);

    variable_id_t variable_id{parse_variable_id(*end, end)};

    parse_operand_separator(*end, end);

    variable_name_t variable_name{parse_variable_name(*end, end)};

    parse_operand_separator(*end, end);

    sexp_type_t value_type{parse_sexp_type(*end, end)};

    parse_instruction_separator(*end, end);

    return EnvironmentVariableLookup{
        environment_id, state::Variable{variable_id, variable_name},
        value_type};
}
}
