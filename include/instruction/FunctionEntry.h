#ifndef PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class FunctionEntry : public Instruction {
  public:
    explicit FunctionEntry(const function_id_t id, const call_id_t call_id,
                           const environment_id_t environment_id)
        : Instruction{}, id_{id}, call_id_{call_id}, environment_id_{
                                                         environment_id} {}

    virtual ~FunctionEntry() {}

    const function_id_t get_id() const { return id_; }

    const call_id_t get_call_id() const { return call_id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

private:
    function_id_t id_;
    call_id_t call_id_;
    environment_id_t environment_id_;
};
} // namespace instruction

#endif /* PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H */
