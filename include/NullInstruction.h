#ifndef PROMISE_INTERFERENCE_NULL_INSTRUCTION_H
#define PROMISE_INTERFERENCE_NULL_INSTRUCTION_H

#include "Instruction.h"
#include <sstream>

class NullInstruction : Instruction {

  public:
    explicit NullInstruction() : Instruction{} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << RECORD_SEPARATOR;
        return stream.str();
    };

    void interpret(AbstractState &state) const {};

    static const opcode_t &get_opcode();

    static NullInstruction parse_arguments(const char *begin, char **end);
};

#endif /* PROMISE_INTERFERENCE_NULL_INSTRUCTION_H */
