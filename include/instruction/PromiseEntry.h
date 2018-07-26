#ifndef PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H

#include "Instruction.h"
#include "scope/scope.h"
#include <sstream>

namespace instruction {

class PromiseEntry : public Instruction {
  public:
    explicit PromiseEntry(const promise_id_t id)

        : Instruction{}, id_{id} {}

    const promise_id_t get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        state.enter_scope(scope::PromiseScope{get_id()});
    }

    static PromiseEntry parse_arguments(const char *begin, char **end);

    static const opcode_t &get_opcode();

  private:
    promise_id_t id_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::PromiseEntry &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H */
