#ifndef PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H

#include "Instruction.h"
#include <sstream>

namespace instruction {

class EnvironmentVariableAction : public Instruction {
  public:
    explicit EnvironmentVariableAction(const environment_id_t id,
                                       const variable_id_t variable_id,
                                       const variable_name_t &variable_name)
        : Instruction{}, id_{id}, variable_id_{variable_id},
          variable_name_{variable_name} {}

    const environment_id_t get_id() const { return id_; }

    const variable_id_t get_variable_id() const { return variable_id_; }

    const variable_name_t &get_variable_name() const { return variable_name_; }

    virtual ~EnvironmentVariableAction() {}

  private:
    environment_id_t id_;
    variable_id_t variable_id_;
    variable_name_t variable_name_;
};
}

#endif /* PROMISE_INTERFERENCE_ENVIRONMENT_VARIABLE_ACTION_INSTRUCTION_H */
