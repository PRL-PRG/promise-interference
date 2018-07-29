#include "analysis/binding/interpreter.h"

namespace analysis::binding {

void interpret(const instruction::FunctionEntry &i, BindingState &state) {
    state.enter_scope(Function{i.get_type(), i.get_id(), i.get_call_id(),
                               i.get_environment_id()});
}

void interpret(const instruction::FunctionExit &i, BindingState &state) {
    scope_t scope{state.exit_scope()};

    if (std::holds_alternative<Function>(scope) &&
        std::get<Function>(scope).get_call_id() == i.get_call_id()) {
        return;
    }

    std::cerr << "scope mismatch" << std::endl;
    std::cerr << "expected: " << i.to_string() << std::endl;
    std::cerr << "obtained: " << to_string(scope) << std::endl;
    exit(EXIT_FAILURE);
}

void interpret(const instruction::ArgumentPromiseAssociate &i,
               BindingState &state) {
    // TODO
}

void interpret(const instruction::EnvironmentCreate &i, BindingState &state) {
    // TODO
}

void interpret(const instruction::EnvironmentVariableDefine &i,
               BindingState &state) {
    state.assign_variable(
        Variable{i.get_variable_id(), i.get_variable_name()},
        AbstractValue{state.get_current_scope(), i.get_value_type()});
}

void interpret(const instruction::EnvironmentVariableAssign &i,
               BindingState &state) {
    state.assign_variable(
        Variable{i.get_variable_id(), i.get_variable_name()},
        AbstractValue{state.get_current_scope(), i.get_value_type()});
}

void interpret(const instruction::EnvironmentVariableLookup &i,
               BindingState &state) {
    Variable variable{i.get_variable_id(), i.get_variable_name()};
    auto optional_value{state.lookup_variable(variable)};

    if (optional_value) {
        if (optional_value->get_type() != i.get_value_type()) {
            std::cerr << "type mismatch" << std::endl;
            std::cerr << "variable: " << variable << std::endl;
            std::cerr << "value: " << *optional_value << std::endl;
            std::cerr << "expected: " << i.get_value_type() << std::endl;
            std::cerr << "obtained: " << optional_value->get_type()
                      << std::endl;
            // exit(EXIT_FAILURE);
        } else {
            state.associate_lookup(variable, *optional_value);
        }
    } else if (!optional_value && (i.get_value_type() == "Special" ||
                                   i.get_value_type() == "Builtin" ||
                                   i.get_value_type() == "Closure" ||
                                   i.get_value_type() == "Promise")) {
        state.assign_variable(variable,
                              AbstractValue{TopLevel{}, i.get_value_type()});
    } else {
        state.add_free_variable(variable);
    }
}

void interpret(const instruction::EnvironmentVariableRemove &i,
               BindingState &state) {
    state.remove_variable(Variable{i.get_variable_id(), i.get_variable_name()});
}

void interpret(const instruction::PromiseCreate &i, BindingState &state) {
    /* TODO */
}

void interpret(const instruction::PromiseEntry &i, BindingState &state) {
    state.enter_scope(Promise{i.get_id()});
}

void interpret(const instruction::PromiseExit &i, BindingState &state) {
    scope_t scope{state.exit_scope()};

    if (std::holds_alternative<Promise>(scope) &&
        std::get<Promise>(scope).get_id() == i.get_id()) {
        return;
    }

    log_error("scope mismatch", "expected: ", to_string(), std::endl,
              "obtained: ", to_string(scope));
}

void interpret(const instruction::PromiseValueLookup &i, BindingState &state) {
    // TODO
}

void interpret(const instruction::PromiseValueAssign &i, BindingState &state) {
    // TODO
}

void interpret(const instruction::PromiseEnvironmentLookup &i,
               BindingState &state) {
    // TODO
}

void interpret(const instruction::PromiseEnvironmentAssign &i,
               BindingState &state) {
    // TODO
}

void interpret(const instruction::PromiseExpressionLookup &i,
               BindingState &state) {
    // TODO
}

void interpret(const instruction::PromiseExpressionAssign &i,
               BindingState &state) {
    // TODO
}

void interpret(const instruction::instruction_t &instruction,
               BindingState &state) {
    std::visit([&](auto const &i) { interpret(i, state); }, instruction);
}

BindingState interpret(const instruction::Stream &stream) {
    BindingState state{};

    for (const auto &instruction : stream) {
        interpret(instruction, state);
    }

    return state;
}

BindingState interpret(const std::filesystem::path trace_filepath) {
    return interpret(instruction::Stream::parse(trace_filepath));
}
}
