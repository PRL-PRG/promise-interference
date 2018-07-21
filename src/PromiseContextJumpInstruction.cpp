#include "include/PromiseContextJumpInstruction.h"

const opcode_t &PromiseContextJumpInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_CONTEXT_JUMP;
}

PromiseContextJumpInstruction
PromiseContextJumpInstruction::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    return PromiseContextJumpInstruction{id};
}
