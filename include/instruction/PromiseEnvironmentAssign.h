#ifndef PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_ASSIGN_INSTRUCTION_H

#include "PromiseEnvironment.h"
#include <sstream>

namespace instruction {

class PromiseEnvironmentAssign : public PromiseEnvironment {
  public:
    explicit PromiseEnvironmentAssign(const promise_id_t id,
                                      const environment_id_t environment_id)
        : PromiseEnvironment{id, environment_id} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_environment_id() << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static PromiseEnvironmentAssign parse_arguments(const char *begin,
                                                    char **end);
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::PromiseEnvironmentAssign &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_ASSIGN_INSTRUCTION_H */
