#ifndef PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class FunctionExit : public Instruction {
  public:
    explicit FunctionExit(const sexp_type_t &type, const function_id_t id,
                          const call_id_t call_id,
                          const environment_id_t environment_id)
        : Instruction{}, type_{type}, id_{id}, call_id_{call_id},
          environment_id_{environment_id} {}

    const sexp_type_t &get_type() const { return type_; }

    const function_id_t get_id() const { return id_; }

    const call_id_t get_call_id() const { return call_id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_type() << UNIT_SEPARATOR
               << get_id() << UNIT_SEPARATOR << get_call_id() << UNIT_SEPARATOR
               << get_environment_id() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        scope::scope_t scope{state.exit_scope()};

        if (std::holds_alternative<scope::FunctionScope>(scope) &&
            std::get<scope::FunctionScope>(scope).get_call_id() ==
                get_call_id()) {
            return;
        }

        std::cerr << "scope mismatch" << std::endl;
        std::cerr << "expected: " << to_string() << std::endl;
        std::cerr << "obtained: " << scope::to_string(scope) << std::endl;
        exit(EXIT_FAILURE);
    }

    static const opcode_t &get_opcode();

    static FunctionExit parse_arguments(const char *begin, char **end);

  private:
    sexp_type_t type_;
    function_id_t id_;
    call_id_t call_id_;
    environment_id_t environment_id_;
};
}

#endif /* PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H */
