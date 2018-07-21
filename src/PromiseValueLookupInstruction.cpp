#include "PromiseValueLookupInstruction.h"

const opcode_t &PromiseValueLookupInstruction::get_opcode() {
    return Instruction::OPCODE_PROMISE_VALUE_LOOKUP;
}

PromiseValueLookupInstruction
PromiseValueLookupInstruction::parse_arguments(const char *begin, char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    sexp_type_t value_type{parse_sexp_type(*end + 1, end)};

    return PromiseValueLookupInstruction{id, value_type};
}
