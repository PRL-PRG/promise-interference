#include "instruction/PromiseValueAssign.h"

namespace instruction {

const opcode_t &PromiseValueAssign::get_opcode() {
    return Instruction::OPCODE_PROMISE_VALUE_ASSIGN;
}

PromiseValueAssign PromiseValueAssign::parse_arguments(const char *begin,
                                                       char **end) {

    promise_id_t id{parse_promise_id(begin, end)};

    parse_operand_separator(*end, end);

    sexp_type_t value_type{parse_sexp_type(*end, end)};

    parse_instruction_separator(*end, end);

    return PromiseValueAssign{id, value_type};
}
}
