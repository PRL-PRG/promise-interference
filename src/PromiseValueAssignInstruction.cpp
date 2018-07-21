#include "PromiseValueAssignInstruction.h"

const opcode_t &PromiseValueAssignInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_VALUE_ASSIGN;
}

PromiseValueAssignInstruction
PromiseValueAssignInstruction::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    sexp_type_t value_type{parse_sexp_type(*end + 1, end)};

    return PromiseValueAssignInstruction{id, value_type};
}
