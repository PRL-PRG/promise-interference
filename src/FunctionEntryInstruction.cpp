#include "include/FunctionEntryInstruction.h"
#include <cstring>

const opcode_t &FunctionEntryInstruction::get_opcode() {
    return Instruction::OPCODE_FUNCTION_ENTRY;
}

FunctionEntryInstruction
FunctionEntryInstruction::parse_arguments(const char *begin, char **end) {
    std::string type{parse_sexp_type(begin, end)};

    std::string id{parse_function_id(*end + 1, end)};

    call_id_t call_id{parse_call_id(*end + 1, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    return FunctionEntryInstruction{type, id, call_id, environment_id};
}
