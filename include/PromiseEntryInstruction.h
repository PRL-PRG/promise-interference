#ifndef PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H

#include "Instruction.h"
#include "scope.h"
#include <sstream>

class PromiseEntryInstruction : public Instruction {
  public:
    explicit PromiseEntryInstruction(const promise_id_t id)

        : Instruction{}, id_{id} {}

    const promise_id_t get_id() const { return id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {
        state.enter_scope(PromiseScope{get_id()});
    }

    static PromiseEntryInstruction parse_arguments(const char *begin,
                                                   char **end);

    static const opcode_t &get_opcode();

  private:
    promise_id_t id_;
};

#endif /* PROMISE_INTERFERENCE_PROMISE_ENTRY_INSTRUCTION_H */
