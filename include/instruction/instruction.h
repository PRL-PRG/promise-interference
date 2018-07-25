#ifndef PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H

#include "EnvironmentCreate.h"
#include "EnvironmentVariableAssign.h"
#include "EnvironmentVariableDefine.h"
#include "EnvironmentVariableLookup.h"
#include "EnvironmentVariableRemove.h"
#include "FunctionEntry.h"
#include "FunctionExit.h"
#include "PromiseCreate.h"
#include "PromiseEntry.h"
#include "PromiseEnvironmentAssign.h"
#include "PromiseEnvironmentLookup.h"
#include "PromiseExit.h"
#include "PromiseExpressionAssign.h"
#include "PromiseExpressionLookup.h"
#include "PromiseValueAssign.h"
#include "PromiseValueLookup.h"

namespace instruction {

using instruction_t = std::variant<
    FunctionEntry, FunctionExit, PromiseCreate, PromiseEntry, PromiseExit,
    PromiseValueLookup, PromiseValueAssign, PromiseEnvironmentLookup,
    PromiseEnvironmentAssign, PromiseExpressionLookup, PromiseExpressionAssign,
    EnvironmentCreate, EnvironmentVariableAssign, EnvironmentVariableRemove,
    EnvironmentVariableDefine, EnvironmentVariableLookup>;

inline std::string to_string(const instruction_t &instruction) {
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
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::instruction_t &instruction) {
    std::visit([&](auto const &i) { os << i.to_string(); }, instruction);
    return os;
}

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H */
