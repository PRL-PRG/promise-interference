#include "instruction/PromiseValueLookup.h"

namespace instruction {

const opcode_t &PromiseValueLookup::get_opcode() {
    return Instruction::OPCODE_PROMISE_VALUE_LOOKUP;
}

PromiseValueLookup PromiseValueLookup::parse_arguments(const char *begin,
                                                       char **end) {
    promise_id_t id{parse_promise_id(begin, end)};

    sexp_type_t value_type{parse_sexp_type(*end + 1, end)};

    parse_record_separator(begin, end);

    return PromiseValueLookup{id, value_type};
}
}
