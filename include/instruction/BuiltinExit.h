#ifndef PROMISE_INTERFERENCE_BUILTIN_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_BUILTIN_EXIT_INSTRUCTION_H

#include "FunctionExit.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class BuiltinExit : public FunctionExit {
  public:
    explicit BuiltinExit(const call_id_t call_id, const bool jump)
        : FunctionExit{call_id, jump} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_call_id()
               << UNIT_SEPARATOR << is_jump() << RECORD_SEPARATOR;
        return stream.str();
    }
    
    static const opcode_t &get_opcode();

    static BuiltinExit parse_arguments(const char *begin, char **end);
};
} // namespace instruction

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::BuiltinExit &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_BUILTIN_EXIT_INSTRUCTION_H */
