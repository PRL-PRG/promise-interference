#ifndef PROMISE_INTERFERENCE_FUNCTION_CONTEXT_JUMP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_CONTEXT_JUMP_INSTRUCTION_H

#include "Instruction.h"
#include "state/AbstractState.h"
#include <sstream>

namespace instruction {

class FunctionContextJump : public Instruction {

  public:
    explicit FunctionContextJump(call_id_t call_id)
        : Instruction{}, call_id_{call_id} {}

    promise_id_t get_call_id() const { return call_id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_call_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        scope::scope_t scope{state.exit_scope()};

        while (!std::holds_alternative<scope::FunctionScope>(scope) ||
               !std::get<scope::FunctionScope>(scope).get_call_id() ==
                   get_call_id()) {
            scope = state.exit_scope();
        }
    }

    static const opcode_t &get_opcode();

    static FunctionContextJump parse_arguments(const char *begin, char **end);

  private:
    call_id_t call_id_;
};
}

#endif /* PROMISE_INTERFERENCE_FUNCTION_CONTEXT_JUMP_INSTRUCTION_H */
