#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H

#include "Instruction.h"
#include "state/Variable.h"
#include <sstream>

namespace instruction {

class EnvironmentVariableAction : public Instruction {
  public:
    explicit EnvironmentVariableAction(const environment_id_t id,
                                       const state::Variable &variable)
        : Instruction{}, id_{id}, variable_{variable} {}

    const environment_id_t get_id() const { return id_; }

    const state::Variable &get_variable() const { return variable_; }

    virtual ~EnvironmentVariableAction() {}

  private:
    environment_id_t id_;
    state::Variable variable_;
};
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H */
