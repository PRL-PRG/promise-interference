#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_DEFINE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_DEFINE_INSTRUCTION_H

#include "EnvironmentVariableActionInstruction.h"

class EnvironmentVariableDefineInstruction
    : public EnvironmentVariableActionInstruction {

  public:
    explicit EnvironmentVariableDefineInstruction(const environment_id_t id,
                                                  const Variable &variable,
                                                  const sexp_type_t &value_type)
        : EnvironmentVariableActionInstruction{id, variable},
          value_type_(value_type) {}

    const sexp_type_t &get_value_type() const { return value_type_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_variable().get_id() << UNIT_SEPARATOR
               << get_variable().get_name() << UNIT_SEPARATOR
               << get_value_type();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {
        state.assign_variable(
            get_variable(),
            AbstractValue{state.get_current_scope(), get_value_type()});
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableDefineInstruction
    parse_arguments(const char *begin, char **end);

  private:
    sexp_type_t value_type_;
};

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_DEFINE_INSTRUCTION_H */
