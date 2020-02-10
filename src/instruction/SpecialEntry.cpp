#include "instruction/SpecialEntry.h"
#include <cstring>

namespace instruction {

const opcode_t &SpecialEntry::get_opcode() {
    return Instruction::OPCODE_SPECIAL_ENTRY;
}

SpecialEntry SpecialEntry::parse_arguments(const char *begin, char **end) {

    std::string id{parse_function_id(begin, end)};

    parse_operand_separator(*end, end);

    call_id_t call_id{parse_call_id(*end, end)};

    parse_operand_separator(*end, end);

    environment_id_t environment_id{parse_environment_id(*end, end)};

    parse_instruction_separator(*end, end);

    return SpecialEntry{type, id, call_id, environment_id};
}
} // namespace instruction
