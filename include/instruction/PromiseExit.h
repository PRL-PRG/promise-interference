#ifndef PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include "scope/scope.h"
#include <sstream>

namespace instruction {

class PromiseExit : public Instruction {
  public:
    explicit PromiseExit(const promise_id_t id, bool jump)
        : Instruction{}, id_{id}, jump_{jump} {}

    const promise_id_t get_id() const { return id_; }

    bool is_jump() const { return jump_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << is_jump() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        scope::scope_t scope{state.exit_scope()};

        if (std::holds_alternative<scope::PromiseScope>(scope) &&
            std::get<scope::PromiseScope>(scope).get_id() == get_id()) {
            return;
        }

        log_error("scope mismatch", "expected: ", to_string(), std::endl,
                  "obtained: ", scope::to_string(scope));
    }

    static const opcode_t &get_opcode();

    static PromiseExit parse_arguments(const char *begin, char **end);

  private:
    promise_id_t id_;
    bool jump_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::PromiseExit &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H */
