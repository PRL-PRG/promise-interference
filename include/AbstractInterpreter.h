#ifndef PROMISE_INTERFERENCE_ABSTRACT_INTERPRETER_H
#define PROMISE_INTERFERENCE_ABSTRACT_INTERPRETER_H

#include "AbstractState.h"
#include "InstructionStream.h"
#include <filesystem>

class AbstractInterpreter {
  public:
    static void interpret(const instruction_t &instruction,
                          AbstractState &state);
    static AbstractState interpret(const InstructionStream &instruction_stream);
    static AbstractState interpret(const std::filesystem::path trace_filepath);
};

#endif /* PROMISE_INTERFERENCE_ABSTRACT_INTERPRETER_H */
