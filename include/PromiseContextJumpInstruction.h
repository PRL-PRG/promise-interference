#ifndef PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H

#include "Instruction.h"
#include "scope.h"
#include <sstream>

class PromiseContextJumpInstruction : public Instruction {

  public:
    explicit PromiseContextJumpInstruction(const promise_id_t id)
        : Instruction{}, id_{id} {}

    promise_id_t get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(AbstractState &state) const override {
        scope_t scope{state.exit_scope()};

        while (!std::holds_alternative<PromiseScope>(scope) ||
               !std::get<PromiseScope>(scope).get_id() == get_id()) {
            scope = state.exit_scope();
        }
    }

    static const opcode_t &get_opcode();

    static PromiseContextJumpInstruction parse_arguments(const char *begin,
                                                         char **end);

  private:
    promise_id_t id_;
};

#endif /* PROMISE_INTERFERENCE_PROMISE_CONTEXT_JUMP_INSTRUCTION_H */
