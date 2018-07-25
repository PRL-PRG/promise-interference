#ifndef PROMISE_INTERFERENCE_INTERPRETER_INTERPRETER_H
#define PROMISE_INTERFERENCE_INTERPRETER_INTERPRETER_H

#include "instruction/Stream.h"
#include "instruction/instruction.h"
#include "state/AbstractState.h"
#include <filesystem>

namespace interpreter {

void interpret(const instruction::instruction_t &instruction,
               state::AbstractState &state);

state::AbstractState interpret(const instruction::Stream &stream);

state::AbstractState interpret(const std::filesystem::path trace_filepath);
}

#endif /* PROMISE_INTERFERENCE_INTERPRETER_INTERPRETER_H */
