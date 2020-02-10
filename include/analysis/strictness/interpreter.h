#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H

#include "analysis/strictness/StrictnessState.h"
#include "instruction/Stream.h"

namespace analysis::strictness {

instruction::Stream rewrite(const instruction::Stream &lazy_stream);

void interpret(const instruction::instruction_t &instruction,
               StrictnessState &state);

StrictnessState interpret(const instruction::Stream &stream);

StrictnessState interpret(const std::filesystem::path trace_filepath);
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H */
