#include "instruction/PromiseEntry.h"

namespace instruction {

const opcode_t &PromiseEntry::get_opcode() {
    return Instruction::OPCODE_PROMISE_ENTRY;
}

PromiseEntry PromiseEntry::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    parse_instruction_separator(*end, end);

    return PromiseEntry{id};
}
}
