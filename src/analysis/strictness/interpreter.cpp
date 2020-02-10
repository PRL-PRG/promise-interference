#include "analysis/strictness/interpreter.h"
#include "analysis/strictness/StrictnessState.h"
#include "instruction/instruction.h"

namespace analysis::strictness {

void interpret(const instruction::FunctionEntry &i, StrictnessState &state) {}

void interpret(const instruction::FunctionExit &i, StrictnessState &state) {}

void interpret(const instruction::ArgumentPromiseAssociate &i,
               StrictnessState &state) {}

void interpret(const instruction::EnvironmentVariableDefine &i,
               StrictnessState &state) {
    state.define_variable(i.get_variable_id());
}

void interpret(const instruction::EnvironmentVariableAssign &i,
               StrictnessState &state) {
    state.assign_variable(i.get_variable_id());
}

void interpret(const instruction::EnvironmentVariableLookup &i,
               StrictnessState &state) {
    state.lookup_variable(i.get_variable_id());
}

void interpret(const instruction::EnvironmentVariableRemove &i,
               StrictnessState &state) {
    state.remove_variable(i.get_variable_id());
}

void interpret(const instruction::EnvironmentCreate &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseCreate &i, StrictnessState &state) {
    state.create_promise(i.get_id());
}

void interpret(const instruction::PromiseEntry &i, StrictnessState &state) {
    state.enter_promise(i.get_id());
}

void interpret(const instruction::PromiseExit &i, StrictnessState &state) {
    state.exit_promise(i.get_id());
}

void interpret(const instruction::PromiseValueLookup &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseValueAssign &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseEnvironmentLookup &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseEnvironmentAssign &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseExpressionLookup &i,
               StrictnessState &state) {}

void interpret(const instruction::PromiseExpressionAssign &i,
               StrictnessState &state) {}

void interpret(const instruction::instruction_t &instruction,
               StrictnessState &state) {
    std::visit([&](auto const &i) { interpret(i, state); }, instruction);
}

StrictnessState interpret(const instruction::Stream &stream) {
    StrictnessState state{};
    std::size_t i = 0;
    for (const auto &instruction : stream) {
        // std::cerr << i << " : " << instruction << std::endl;
        interpret(instruction, state);
        ++i;
    }

    std::cerr << state;

    return state;
}
}
