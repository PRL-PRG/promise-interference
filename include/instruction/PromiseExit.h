#ifndef PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
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
