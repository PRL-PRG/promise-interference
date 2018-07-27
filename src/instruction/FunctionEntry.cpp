#include "instruction/FunctionEntry.h"
#include <cstring>

namespace instruction {

const opcode_t &FunctionEntry::get_opcode() {
    return Instruction::OPCODE_FUNCTION_ENTRY;
}

FunctionEntry FunctionEntry::parse_arguments(const char *begin, char **end) {

    std::string type{parse_sexp_type(begin, end)};

    parse_operand_separator(*end, end);

    std::string id{parse_function_id(*end, end)};

    parse_operand_separator(*end, end);

    call_id_t call_id{parse_call_id(*end, end)};

    parse_operand_separator(*end, end);

    environment_id_t environment_id{parse_environment_id(*end, end)};

    parse_instruction_separator(*end, end);

    return FunctionEntry{type, id, call_id, environment_id};
}
}
