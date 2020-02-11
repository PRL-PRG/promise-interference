#ifndef PROMISE_INTERFERENCE_SPECIAL_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_SPECIAL_ENTRY_INSTRUCTION_H

#include "FunctionEntry.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class SpecialEntry : public FunctionEntry {
  public:
    explicit SpecialEntry(const function_id_t id, const call_id_t call_id,
                          const environment_id_t environment_id,
                          const std::string &function_names)
        : FunctionEntry{id, call_id, environment_id, function_names} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_function_id()
               << UNIT_SEPARATOR << get_call_id() << UNIT_SEPARATOR
               << get_environment_id() << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static SpecialEntry parse_arguments(const char *begin, char **end);
};
} // namespace instruction

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::SpecialEntry &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_SPECIAL_ENTRY_INSTRUCTION_H */
