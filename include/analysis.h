#ifndef PROMISE_INTERFERENCE_ANALYSIS_H
#define PROMISE_INTERFERENCE_ANALYSIS_H

#include "InstructionStream.h"

namespace analysis::strictness {
InstructionStream rewrite(const InstructionStream &lazy_stream);
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_H */
