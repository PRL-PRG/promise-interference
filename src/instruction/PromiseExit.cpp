#include "instruction/PromiseExit.h"

namespace instruction {

const opcode_t &PromiseExit::get_opcode() {
    return Instruction::OPCODE_PROMISE_EXIT;
}

PromiseExit PromiseExit::parse_arguments(const char *begin, char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    bool jump{parse_boolean(*end + 1, end)};

    parse_record_separator(begin, end);

    return PromiseExit{id, jump};
}
}
