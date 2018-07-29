#ifndef PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H

#include "ArgumentPromiseAssociate.h"
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
#include <variant>

namespace instruction {

using instruction_t =
    std::variant<FunctionEntry, FunctionExit, PromiseCreate, PromiseEntry,
                 PromiseExit, ArgumentPromiseAssociate, PromiseValueLookup,
                 PromiseValueAssign, PromiseEnvironmentLookup,
                 PromiseEnvironmentAssign, PromiseExpressionLookup,
                 PromiseExpressionAssign, EnvironmentCreate,
                 EnvironmentVariableAssign, EnvironmentVariableRemove,
                 EnvironmentVariableDefine, EnvironmentVariableLookup>;

inline std::string to_string(const instruction_t &instruction) {
    std::string instruction_string;
    std::visit([&](auto const &i) { instruction_string = i.to_string(); },
               instruction);
    return instruction_string;
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::instruction_t &instruction) {
    std::visit([&](const auto &i) { os << i.to_string(); }, instruction);
    return os;
}

inline void set_line_number(instruction_t &instruction,
                            line_number_t line_number) {
    std::visit([&](auto &i) { i.set_line_number(line_number); }, instruction);
}

inline line_number_t get_line_number(const instruction_t &instruction) {
    line_number_t line_number;
    std::visit([&](const auto &i) { line_number = i.get_line_number(); },
               instruction);
    return line_number;
}
}

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_INSTRUCTION_H */
