#include "PromiseEntryInstruction.h"

const opcode_t &PromiseEntryInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENTRY;
}

PromiseEntryInstruction
PromiseEntryInstruction::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    return PromiseEntryInstruction{id};
}
