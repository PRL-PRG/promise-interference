#include "NullInstruction.h"

const opcode_t &NullInstruction::get_opcode() {
    return Instruction::OPCODE_NULL;
}

NullInstruction NullInstruction::parse_arguments(const char *begin,
                                                 char **end) {
    return NullInstruction{};
}
