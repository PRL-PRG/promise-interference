#ifndef PROMISE_INTERFERENCE_NULL_INSTRUCTION_H
#define PROMISE_INTERFERENCE_NULL_INSTRUCTION_H

#include "Instruction.h"
#include <sstream>

namespace instruction {

class Null : public Instruction {

  public:
    explicit Null() : Instruction{} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << RECORD_SEPARATOR;
        return stream.str();
    };

    void interpret(state::AbstractState &state) const override {
        std::cerr << "Null instruction encountered" << std::endl;
        exit(EXIT_FAILURE);
    };

    static const opcode_t &get_opcode();

    static Null parse_arguments(const char *begin, char **end);
};
}

#endif /* PROMISE_INTERFERENCE_NULL_INSTRUCTION_H */
