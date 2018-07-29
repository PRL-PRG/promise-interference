#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_INTERPRETER_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_INTERPRETER_H

#include "analysis/binding/BindingState.h"
#include "instruction/Stream.h"

namespace analysis::binding {

void interpret(const instruction::instruction_t &instruction,
               BindingState &state);

BindingState interpret(const instruction::Stream &stream);

BindingState interpret(const std::filesystem::path trace_filepath);
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_INTERPRETER_H */
