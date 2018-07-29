#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H

#include "instruction/Stream.h"

namespace analysis::strictness {

instruction::Stream rewrite(const instruction::Stream &lazy_stream);
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_INTERPRETER_H */
