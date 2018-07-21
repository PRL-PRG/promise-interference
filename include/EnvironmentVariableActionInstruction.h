#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H

#include "Instruction.h"
#include "Variable.h"
#include <sstream>

class EnvironmentVariableActionInstruction : public Instruction {
  public:
    explicit EnvironmentVariableActionInstruction(const environment_id_t id,
                                                  const Variable &variable)
        : Instruction{}, id_{id}, variable_{variable} {}

    const environment_id_t get_id() const { return id_; }

    const Variable &get_variable() const { return variable_; }

    virtual ~EnvironmentVariableActionInstruction() {}

  private:
    environment_id_t id_;
    Variable variable_;
};

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H */
