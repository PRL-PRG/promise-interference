#ifndef PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class FunctionExit : public Instruction {
  public:
    explicit FunctionExit(const call_id_t call_id, const bool jump)
        : Instruction{}, call_id_{call_id}, jump_{jump} {}

    virtual ~FunctionExit() {}

    const call_id_t get_call_id() const { return call_id_; }

    bool is_jump() const { return jump_; }

  private:
    call_id_t call_id_;
    bool jump_;
};
} // namespace instruction

#endif /* PROMISE_INTERFERENCE_FUNCTION_EXIT_INSTRUCTION_H */
