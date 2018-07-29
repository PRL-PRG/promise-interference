#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H

#include "EnvironmentVariableAction.h"

namespace instruction {

class EnvironmentVariableRemove : public EnvironmentVariableAction {

  public:
    explicit EnvironmentVariableRemove(const environment_id_t id,
                                       const variable_id_t variable_id,
                                       const variable_name_t &variable_name)
        : EnvironmentVariableAction{id, variable_id, variable_name} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_variable_id() << UNIT_SEPARATOR << get_variable_name()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableRemove parse_arguments(const char *begin,
                                                     char **end);
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::EnvironmentVariableRemove &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H */
