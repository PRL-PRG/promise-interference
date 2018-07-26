#ifndef PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class FunctionExit : public Instruction {
  public:
    explicit FunctionExit(const call_id_t call_id, const bool jump)
        : Instruction{}, call_id_{call_id}, jump_{jump} {}

    const call_id_t get_call_id() const { return call_id_; }

    bool is_jump() const { return jump_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_call_id()
               << UNIT_SEPARATOR << is_jump() << RECORD_SEPARATOR;
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
    bool jump_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::FunctionExit &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H */
