#include "instruction/FunctionEntry.h"
#include <cstring>

namespace instruction {

const opcode_t &FunctionEntry::get_opcode() {
    return Instruction::OPCODE_FUNCTION_ENTRY;
}

FunctionEntry FunctionEntry::parse_arguments(const char *begin, char **end) {
    std::string type{parse_sexp_type(begin, end)};

    std::string id{parse_function_id(*end + 1, end)};

    call_id_t call_id{parse_call_id(*end + 1, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    return FunctionEntry{type, id, call_id, environment_id};
}
}
