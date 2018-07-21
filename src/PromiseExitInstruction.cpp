#include "PromiseExitInstruction.h"

const opcode_t &PromiseExitInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_EXIT;
}

PromiseExitInstruction
PromiseExitInstruction::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    return PromiseExitInstruction{id};
}
