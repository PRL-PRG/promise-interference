#ifndef PROMISE_INTERFERENCE_PROMISE_VALUE_LOOKUP_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_VALUE_LOOKUP_INSTRUCTION_H

#include "PromiseValue.h"
#include <sstream>

namespace instruction {

class PromiseValueLookup : public PromiseValue {
  public:
    explicit PromiseValueLookup(const promise_id_t id,
                                const sexp_type_t &value_type)
        : PromiseValue{id, value_type} {}

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_value_type() << RECORD_SEPARATOR;
        return stream.str();
    }

    static const opcode_t &get_opcode();

    static PromiseValueLookup parse_arguments(const char *begin, char **end);
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::PromiseValueLookup &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_PROMISE_VALUE_LOOKUP_INSTRUCTION_H */
