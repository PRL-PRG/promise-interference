#include "instruction/FunctionContextJump.h"
#include <cstring>

namespace instruction {

const opcode_t &FunctionContextJump::get_opcode() {
    return Instruction::OPCODE_FUNCTION_CONTEXT_JUMP;
}

FunctionContextJump FunctionContextJump::parse_arguments(const char *begin,
                                                         char **end) {
    call_id_t call_id{strtoul(begin, end, 10)};

    return FunctionContextJump{call_id};
}
}
