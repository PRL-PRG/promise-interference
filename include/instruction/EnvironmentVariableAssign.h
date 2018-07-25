#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H

#include "EnvironmentVariableAction.h"

namespace instruction {

class EnvironmentVariableAssign : public EnvironmentVariableAction {

  public:
    explicit EnvironmentVariableAssign(const environment_id_t id,
                                       const state::Variable &variable,
                                       const sexp_type_t &value_type)
        : EnvironmentVariableAction{id, variable}, value_type_(value_type) {}

    const sexp_type_t &get_value_type() const { return value_type_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_variable().get_id() << UNIT_SEPARATOR
               << get_variable().get_name() << UNIT_SEPARATOR
               << get_value_type() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        state.assign_variable(
            get_variable(),
            state::AbstractValue{state.get_current_scope(), get_value_type()});
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableAssign parse_arguments(const char *begin,
                                                     char **end);

  private:
    sexp_type_t value_type_;
};
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H */
