#ifndef PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H

#include "Instruction.h"
#include "scope/scope.h"
#include <sstream>

namespace instruction {

class PromiseContextJump : public Instruction {

  public:
    explicit PromiseContextJump(const promise_id_t id)
        : Instruction{}, id_{id} {}

    promise_id_t get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        scope::scope_t scope{state.exit_scope()};

        while (!std::holds_alternative<scope::PromiseScope>(scope) ||
               !std::get<scope::PromiseScope>(scope).get_id() == get_id()) {
            scope = state.exit_scope();
        }
    }

    static const opcode_t &get_opcode();

    static PromiseContextJump parse_arguments(const char *begin, char **end);

  private:
    promise_id_t id_;
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H */
