#include "instruction/ArgumentPromiseAssociate.h"

namespace instruction {

const opcode_t &ArgumentPromiseAssociate::get_opcode() {
    return Instruction::OPCODE_ARGUMENT_PROMISE_ASSOCIATE;
}

ArgumentPromiseAssociate
ArgumentPromiseAssociate::parse_arguments(const char *begin, char **end) {

    function_id_t function_id{parse_function_id(begin, end)};

    parse_operand_separator(*end, end);

    call_id_t call_id{parse_call_id(*end, end)};

    parse_operand_separator(*end, end);

    position_t formal_position{parse_position(*end, end)};

    parse_operand_separator(*end, end);

    variable_id_t variable_id{parse_variable_id(*end, end)};

    parse_operand_separator(*end, end);

    variable_name_t variable_name{parse_variable_name(*end, end)};

    parse_operand_separator(*end, end);

    promise_id_t promise_id{parse_promise_id(*end, end)};

    parse_instruction_separator(*end, end);

    return ArgumentPromiseAssociate{function_id, call_id, formal_position,
                                    variable_id, variable_name, promise_id};
}
}
