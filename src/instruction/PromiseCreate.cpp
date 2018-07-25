#include "instruction/PromiseCreate.h"

namespace instruction {

const opcode_t &PromiseCreate::get_opcode() {
    return Instruction::OPCODE_PROMISE_CREATE;
}

PromiseCreate PromiseCreate::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    environment_id_t environment_id{parse_environment_id(*end + 1, end)};

    expression_t expression{parse_expression(*end + 1, end)};

    return PromiseCreate{id, environment_id, expression};
}
}
