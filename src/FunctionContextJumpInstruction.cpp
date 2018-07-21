#include "include/FunctionContextJumpInstruction.h"
#include <cstring>

const opcode_t &FunctionContextJumpInstruction::get_opcode() {
    return Instruction::OPCODE_FUNCTION_CONTEXT_JUMP;
}

FunctionContextJumpInstruction
FunctionContextJumpInstruction::parse_arguments(const char *begin, char **end) {
    call_id_t call_id{strtoul(begin, end, 10)};

    return FunctionContextJumpInstruction{call_id};
}
