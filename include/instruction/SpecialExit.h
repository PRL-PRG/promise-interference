#ifndef PROMISE_INTERFERENCE_SPECIAL_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_SPECIAL_EXIT_INSTRUCTION_H

#include "FunctionExit.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class SpecialExit : public FunctionExit {
  public:
    explicit SpecialExit(const call_id_t call_id, const bool jump)
        : FunctionExit{call_id, jump} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_call_id()
               << UNIT_SEPARATOR << is_jump() << RECORD_SEPARATOR;
        return stream.str();
    }
    
    static const opcode_t &get_opcode();

    static SpecialExit parse_arguments(const char *begin, char **end);
};
} // namespace instruction

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::SpecialExit &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_SPECIAL_EXIT_INSTRUCTION_H */
