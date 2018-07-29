#ifndef PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_BASE_H
#define PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_BASE_H

#include "utilities.h"
#include <limits>
#include <string>
#include <optional>

namespace instruction {

class Instruction {
  public:
    static const opcode_t OPCODE_FUNCTION_ENTRY;
    static const opcode_t OPCODE_FUNCTION_EXIT;
    static const opcode_t OPCODE_ARGUMENT_PROMISE_ASSOCIATE;
    static const opcode_t OPCODE_PROMISE_CREATE;
    static const opcode_t OPCODE_PROMISE_ENTRY;
    static const opcode_t OPCODE_PROMISE_EXIT;
    static const opcode_t OPCODE_PROMISE_VALUE_LOOKUP;
    static const opcode_t OPCODE_PROMISE_EXPRESSION_LOOKUP;
    static const opcode_t OPCODE_PROMISE_ENVIRONMENT_LOOKUP;
    static const opcode_t OPCODE_PROMISE_VALUE_ASSIGN;
    static const opcode_t OPCODE_PROMISE_EXPRESSION_ASSIGN;
    static const opcode_t OPCODE_PROMISE_ENVIRONMENT_ASSIGN;
    static const opcode_t OPCODE_ENVIRONMENT_CREATE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_ASSIGN;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_REMOVE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_DEFINE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_LOOKUP;

  public:
    explicit Instruction()
        : line_number_{std::numeric_limits<std::size_t>::max()} {}

    virtual std::string to_string() const = 0;

    void set_line_number(line_number_t line_number) {
        line_number_ = line_number;
    }

    line_number_t get_line_number() const { return line_number_; }

    virtual ~Instruction() {}

    template <typename T>
    static bool starts_with_opcode(const char *begin, char **end) {
        if (!starts_with(begin, T::get_opcode()))
            return false;

        *end = const_cast<char *>(begin) + T::get_opcode().size();

        return true;
    }

    template <typename T>
    static std::optional<T> parse(const char *begin, char **end) {
        if (!starts_with_opcode<T>(begin, end))
            return {};

        parse_operand_separator(*end, end);

        return T::parse_arguments(*end, end);
    }

    template <typename T>
    static T parse_arguments(const char *begin, char **end) {
        return T::parse_arguments(begin, end);
    }

  private:
    line_number_t line_number_;
};
}

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_BASE_H */
