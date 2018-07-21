#ifndef PROMISE_INTERFERENCE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_INSTRUCTION_H

#include "AbstractState.h"
#include "utilities.h"
#include <string>

class Instruction {
  public:
    static const opcode_t OPCODE_NULL;
    static const opcode_t OPCODE_FUNCTION_ENTRY;
    static const opcode_t OPCODE_FUNCTION_EXIT;
    static const opcode_t OPCODE_FUNCTION_CONTEXT_JUMP;
    static const opcode_t OPCODE_PROMISE_CREATE;
    static const opcode_t OPCODE_PROMISE_ENTRY;
    static const opcode_t OPCODE_PROMISE_EXIT;
    static const opcode_t OPCODE_PROMISE_VALUE_LOOKUP;
    static const opcode_t OPCODE_PROMISE_EXPRESSION_LOOKUP;
    static const opcode_t OPCODE_PROMISE_ENVIRONMENT_LOOKUP;
    static const opcode_t OPCODE_PROMISE_VALUE_ASSIGN;
    static const opcode_t OPCODE_PROMISE_EXPRESSION_ASSIGN;
    static const opcode_t OPCODE_PROMISE_ENVIRONMENT_ASSIGN;
    static const opcode_t OPCODE_PROMISE_CONTEXT_JUMP;
    static const opcode_t OPCODE_ENVIRONMENT_CREATE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_ASSIGN;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_REMOVE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_DEFINE;
    static const opcode_t OPCODE_ENVIRONMENT_VARIABLE_LOOKUP;
    static const size_t MINIMUM_INSTRUCTION_LENGTH;

  public:
    explicit Instruction() {}

    virtual std::string to_string() const = 0;

    virtual void interpret(AbstractState &state) const = 0;

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

        return T::parse_arguments(*end + 1, end);
    }

    template <typename T>
    static T parse_arguments(const char *begin, char **end) {
        return T::parse_arguments(begin, end);
    }
};

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_H */
