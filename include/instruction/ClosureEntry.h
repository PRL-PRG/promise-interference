#ifndef PROMISE_INTERFERENCE_CLOSURE_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_CLOSURE_ENTRY_INSTRUCTION_H

#include "FunctionEntry.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class ClosureEntry : public FunctionEntry {
  public:
    explicit ClosureEntry(const function_id_t id, const call_id_t call_id,
                          const environment_id_t environment_id)
        : FunctionEntry{id, call_id, environment_id} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_call_id() << UNIT_SEPARATOR << get_environment_id()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static ClosureEntry parse_arguments(const char *begin, char **end);
};
} // namespace instruction

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::ClosureEntry &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_CLOSURE_ENTRY_INSTRUCTION_H */
