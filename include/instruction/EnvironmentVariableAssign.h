#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H

#include "EnvironmentVariableAction.h"

namespace instruction {

class EnvironmentVariableAssign : public EnvironmentVariableAction {

  public:
    explicit EnvironmentVariableAssign(const environment_id_t id,
                                       const variable_id_t variable_id,
                                       const variable_name_t &variable_name,
                                       const sexp_type_t &value_type)
        : EnvironmentVariableAction{id, variable_id, variable_name},
          value_type_(value_type) {}

    const sexp_type_t &get_value_type() const { return value_type_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_variable_id() << UNIT_SEPARATOR << get_variable_name()
               << UNIT_SEPARATOR << get_value_type() << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static EnvironmentVariableAssign parse_arguments(const char *begin,
                                                     char **end);

  private:
    sexp_type_t value_type_;
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::EnvironmentVariableAssign &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ASSIGN_INSTRUCTION_H */
