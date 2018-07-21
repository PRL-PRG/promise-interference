#ifndef PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_LOOKUP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_LOOKUP_INSTRUCTION_H

#include "PromiseEnvironmentInstruction.h"
#include <sstream>

class PromiseEnvironmentLookupInstruction
    : public PromiseEnvironmentInstruction {
  public:
    explicit PromiseEnvironmentLookupInstruction(
        const promise_id_t id, const environment_id_t environment_id)
        : PromiseEnvironmentInstruction{id, environment_id} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_environment_id();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseEnvironmentLookupInstruction
    parse_arguments(const char *begin, char **end);
};

#endif /* PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_LOOKUP_INSTRUCTION_H */
