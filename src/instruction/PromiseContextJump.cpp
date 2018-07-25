#include "instruction/PromiseContextJump.h"

namespace instruction {

const opcode_t &PromiseContextJump::get_opcode() {
    return Instruction::OPCODE_PROMISE_CONTEXT_JUMP;
}

PromiseContextJump PromiseContextJump::parse_arguments(const char *begin,
                                                       char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    return PromiseContextJump{id};
}
}
