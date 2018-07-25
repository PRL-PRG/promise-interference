#include "instruction/Null.h"

namespace instruction {

const opcode_t &Null::get_opcode() { return Instruction::OPCODE_NULL; }

Null Null::parse_arguments(const char *begin, char **end) { return Null{}; }
}
