#ifndef PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class FunctionEntry : public Instruction {
  public:
    explicit FunctionEntry(const function_id_t function_id,
                           const call_id_t call_id,
                           const environment_id_t environment_id,
                           const std::string &function_names)
        : Instruction{}, function_id_{function_id}, call_id_{call_id},
          environment_id_{environment_id}, function_names_{function_names} {}

    virtual ~FunctionEntry() {}

    const function_id_t get_function_id() const { return function_id_; }

    const call_id_t get_call_id() const { return call_id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    const std::string &get_function_names() const { return function_names_; }

  private:
    function_id_t function_id_;
    call_id_t call_id_;
    environment_id_t environment_id_;
    std::string function_names_;
};
} // namespace instruction

#endif /* PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H */
