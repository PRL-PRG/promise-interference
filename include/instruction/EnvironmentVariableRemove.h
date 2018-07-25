#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H

#include "EnvironmentVariableAction.h"

namespace instruction {

class EnvironmentVariableRemove : public EnvironmentVariableAction {

  public:
    explicit EnvironmentVariableRemove(const environment_id_t id,
                                       const state::Variable &variable)
        : EnvironmentVariableAction{id, variable} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_variable().get_id() << UNIT_SEPARATOR
               << get_variable().get_name() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        state.remove_variable(get_variable());
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableRemove parse_arguments(const char *begin,
                                                     char **end);
};
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_REMOVE_INSTRUCTION_H */
