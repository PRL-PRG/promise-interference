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

std::string instruction_to_string(const instruction_t &instruction);

std::ostream &operator<<(std::ostream &os, const instruction_t &instruction);

class InstructionStream {
  public:
    using iterator = std::vector<instruction_t>::iterator;
    using const_iterator = std::vector<instruction_t>::const_iterator;
    using reverse_iterator = std::vector<instruction_t>::reverse_iterator;
    using const_reverse_iterator =
        std::vector<instruction_t>::const_reverse_iterator;
    using size_type = std::vector<instruction_t>::size_type;

    explicit InstructionStream(std::vector<instruction_t> instructions)
        : instructions_{std::move(instructions)} {}

    instruction_t &at(size_type pos) { return instructions_.at(pos); }

    const instruction_t &at(size_type pos) const {
        return instructions_.at(pos);
    }

    instruction_t &operator[](size_type pos) { return instructions_[pos]; }

    const instruction_t &operator[](size_type pos) const {
        return instructions_[pos];
    }

    size_t size() const { return instructions_.size(); }

    iterator begin() { return instructions_.begin(); }

    const_iterator begin() const { return instructions_.begin(); }

    const_iterator cbegin() const { return instructions_.cbegin(); }

    iterator end() { return instructions_.end(); }

    const_iterator end() const { return instructions_.end(); }

    const_iterator cend() const { return instructions_.cend(); }

    static InstructionStream parse(std::filesystem::path trace_file);

    static instruction_t parse_instruction(const char *begin, char **end);

  private:
    InstructionStream(const InstructionStream &);

    InstructionStream &operator=(const InstructionStream &);

    std::vector<instruction_t> instructions_;
};

std::ostream &operator<<(std::ostream &os,
                         const InstructionStream &instruction_stream);

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H */
