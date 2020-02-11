#include "analysis/strictness/interpreter.h"
#include "analysis/strictness/StrictnessState.h"
#include "instruction/instruction.h"

namespace analysis::strictness {

void interpret(const instruction::ClosureEntry &i, StrictnessState &state) {
    state.enter_function(i.get_function_id(), i.get_call_id(),
                         i.get_function_names());
}

void interpret(const instruction::ClosureExit &i, StrictnessState &state) {
    state.exit_function(i.get_call_id());
}

void interpret(const instruction::BuiltinEntry &i, StrictnessState &state) {}

void interpret(const instruction::BuiltinExit &i, StrictnessState &state) {}

void interpret(const instruction::SpecialEntry &i, StrictnessState &state) {}

void interpret(const instruction::SpecialExit &i, StrictnessState &state) {}

void interpret(const instruction::ArgumentPromiseAssociate &i,
               StrictnessState &state) {
    state.associate_promise(i.get_promise_id(), i.get_call_id(),
                            i.get_formal_position(), i.get_variable_name());
}

void interpret(const instruction::EnvironmentVariableDefine &i,
               StrictnessState &state) {
    state.write_variable(i.get_variable_id(), i.get_variable_name());
}

void interpret(const instruction::EnvironmentVariableAssign &i,
               StrictnessState &state) {
    state.write_variable(i.get_variable_id(), i.get_variable_name());
}

void interpret(const instruction::EnvironmentVariableLookup &i,
               StrictnessState &state) {
    state.read_variable(i.get_variable_id(), i.get_variable_name());
}

void interpret(const instruction::EnvironmentVariableRemove &i,
               StrictnessState &state) {
    state.write_variable(i.get_variable_id(), i.get_variable_name());
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
               StrictnessState &state) {
    state.metaprogram_promise(i.get_id());
}

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

    return state;
}
} // namespace analysis::strictness
