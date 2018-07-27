#include "instruction/FunctionExit.h"
#include <cstring>

namespace instruction {

const opcode_t &FunctionExit::get_opcode() {
    return Instruction::OPCODE_FUNCTION_EXIT;
}

FunctionExit FunctionExit::parse_arguments(const char *begin, char **end) {

    call_id_t call_id{parse_call_id(begin, end)};

    parse_operand_separator(*end, end);

    bool jump{parse_boolean(*end, end)};

    parse_instruction_separator(*end, end);

    return FunctionExit{call_id, jump};
}
}
