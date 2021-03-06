#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_CREATE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_CREATE_INSTRUCTION_H

#include "Instruction.h"
#include <sstream>

namespace instruction {

class EnvironmentCreate : public Instruction {

  public:
    explicit EnvironmentCreate(environment_id_t id) : Instruction{}, id_{id} {}

    const environment_id_t &get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static bool starts_with_opcode(const char *begin, char **end);

    static EnvironmentCreate parse_arguments(const char *begin, char **end);

  private:
    environment_id_t id_;
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::EnvironmentCreate &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_CREATE_INSTRUCTION_H */
