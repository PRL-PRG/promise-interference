#ifndef PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H
#define PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H

#include "EnvironmentCreateInstruction.h"
#include "EnvironmentVariableAssignInstruction.h"
#include "EnvironmentVariableDefineInstruction.h"
#include "EnvironmentVariableLookupInstruction.h"
#include "EnvironmentVariableRemoveInstruction.h"
#include "FunctionContextJumpInstruction.h"
#include "FunctionEntryInstruction.h"
#include "FunctionExitInstruction.h"
#include "NullInstruction.h"
#include "PromiseContextJumpInstruction.h"
#include "PromiseCreateInstruction.h"
#include "PromiseEntryInstruction.h"
#include "PromiseEnvironmentAssignInstruction.h"
#include "PromiseEnvironmentLookupInstruction.h"
#include "PromiseExitInstruction.h"
#include "PromiseExpressionAssignInstruction.h"
#include "PromiseExpressionLookupInstruction.h"
#include "PromiseValueAssignInstruction.h"
#include "PromiseValueLookupInstruction.h"
#include <filesystem>
#include <iostream>
#include <variant>
#include <vector>

using instruction_t = std::variant<
    NullInstruction, FunctionEntryInstruction, FunctionExitInstruction,
    FunctionContextJumpInstruction, PromiseCreateInstruction,
    PromiseEntryInstruction, PromiseExitInstruction,
    PromiseValueLookupInstruction, PromiseValueAssignInstruction,
    PromiseEnvironmentLookupInstruction, PromiseEnvironmentAssignInstruction,
    PromiseExpressionLookupInstruction, PromiseExpressionAssignInstruction,
    PromiseContextJumpInstruction, EnvironmentCreateInstruction,
    EnvironmentVariableAssignInstruction, EnvironmentVariableRemoveInstruction,
    EnvironmentVariableDefineInstruction, EnvironmentVariableLookupInstruction>;

inline std::string instruction_to_string(const instruction_t &instruction) {
    std::string instruction_string;
    std::visit([&](auto const &i) { instruction_string = i.to_string(); },
               instruction);
    return instruction_string;
}

inline void set_line_number(instruction_t &instruction,
                            std::size_t line_number) {
    std::visit([&](auto &i) { i.set_line_number(line_number); }, instruction);
}

inline std::size_t get_line_number(const instruction_t &instruction) {
    std::size_t line_number;
    std::visit([&](const auto &i) { line_number = i.get_line_number(); },
               instruction);
    return line_number;
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction_t &instruction) {
    std::visit([&](auto const &i) { os << i.to_string(); }, instruction);
    return os;
}

class InstructionStream {
  public:
    using iterator = std::vector<instruction_t>::iterator;
    using const_iterator = std::vector<instruction_t>::const_iterator;
    using reverse_iterator = std::vector<instruction_t>::reverse_iterator;
    using const_reverse_iterator =
        std::vector<instruction_t>::const_reverse_iterator;
    using size_type = std::vector<instruction_t>::size_type;

    explicit InstructionStream(size_type capacity) : instructions_{} {
        instructions_.reserve(capacity);
    }

    explicit InstructionStream(std::vector<instruction_t> instructions)
        : instructions_{std::move(instructions)} {}

    void reserve(size_type new_capacity) {
        instructions_.reserve(new_capacity);
    }

    size_type capacity() const noexcept { return instructions_.capacity(); }

    instruction_t &at(size_type pos) { return instructions_.at(pos); }

    const instruction_t &at(size_type pos) const {
        return instructions_.at(pos);
    }

    instruction_t &operator[](size_type pos) { return instructions_[pos]; }

    const instruction_t &operator[](size_type pos) const {
        return instructions_[pos];
    }

    size_type size() const { return instructions_.size(); }

    iterator begin() { return instructions_.begin(); }

    const_iterator begin() const { return instructions_.begin(); }

    const_iterator cbegin() const { return instructions_.cbegin(); }

    iterator end() { return instructions_.end(); }

    const_iterator end() const { return instructions_.end(); }

    const_iterator cend() const { return instructions_.cend(); }

    void push_back(const instruction_t &instruction) {
        instructions_.push_back(instruction);
    }

    static InstructionStream parse(std::filesystem::path trace_file);

    static instruction_t parse_instruction(const char *begin, char **end);

  private:

    std::vector<instruction_t> instructions_;
};

std::ostream &operator<<(std::ostream &os,
                         const InstructionStream &instruction_stream);

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H */
