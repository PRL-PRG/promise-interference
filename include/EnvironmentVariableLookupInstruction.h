#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_LOOKUP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_LOOKUP_INSTRUCTION_H

#include "EnvironmentVariableActionInstruction.h"

class EnvironmentVariableLookupInstruction
    : public EnvironmentVariableActionInstruction {

  public:
    explicit EnvironmentVariableLookupInstruction(const environment_id_t id,
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
               << get_value_type() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(AbstractState &state) const override {

        auto optional_value{state.lookup_variable(get_variable())};

        if (optional_value) {
            if (optional_value->get_type() != get_value_type()) {
                std::cerr << "type mismatch" << std::endl;
                std::cerr << "variable: " << get_variable() << std::endl;
                std::cerr << "value: " << *optional_value << std::endl;
                std::cerr << "expected: " << get_value_type() << std::endl;
                std::cerr << "obtained: " << optional_value->get_type()
                          << std::endl;
                // exit(EXIT_FAILURE);
            } else {
                state.associate_lookup(get_variable(), *optional_value);
            }
        } else if (!optional_value && (get_value_type() == "Special" ||
                                       get_value_type() == "Builtin" ||
                                       get_value_type() == "Closure" ||
                                       get_value_type() == "Promise")) {
            state.assign_variable(
                get_variable(),
                AbstractValue{TopLevelScope{}, get_value_type()});
        } else {
            state.add_free_variable(get_variable());
        }
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableLookupInstruction
    parse_arguments(const char *begin, char **end);

  private:
    sexp_type_t value_type_;
};

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_LOOKUP_INSTRUCTION_H */
