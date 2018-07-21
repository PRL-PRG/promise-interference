#ifndef PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include "scope.h"
#include <sstream>

class PromiseExitInstruction : public Instruction {
  public:
    explicit PromiseExitInstruction(const promise_id_t id)
        : Instruction{}, id_{id} {}

    const promise_id_t get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {
        scope_t scope{state.exit_scope()};

        if (std::holds_alternative<PromiseScope>(scope) &&
            std::get<PromiseScope>(scope).get_id() == get_id()) {
            return;
        }

        log_error("scope mismatch", "expected: ", to_string(), std::endl,
                  "obtained: ", scope_to_string(scope));
    }

    static const opcode_t &get_opcode();

    static PromiseExitInstruction parse_arguments(const char *begin,
                                                  char **end);

  private:
    promise_id_t id_;
};

#endif /* PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H */
