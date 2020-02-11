#include "instruction/ClosureEntry.h"
#include <cstring>

namespace instruction {

const opcode_t &ClosureEntry::get_opcode() {
    return Instruction::OPCODE_CLOSURE_ENTRY;
}

ClosureEntry ClosureEntry::parse_arguments(const char *begin, char **end) {

    std::string id{parse_function_id(begin, end)};

    parse_operand_separator(*end, end);

    call_id_t call_id{parse_call_id(*end, end)};

    parse_operand_separator(*end, end);

    environment_id_t environment_id{parse_environment_id(*end, end)};

    parse_operand_separator(*end, end);

    std::string function_names{parse_function_names(*end, end)};

    parse_instruction_separator(*end, end);

    return ClosureEntry{id, call_id, environment_id, function_names};
}
} // namespace instruction
