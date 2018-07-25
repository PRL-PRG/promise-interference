#ifndef PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_INSTRUCTION_H

#include "Instruction.h"

namespace instruction {

class PromiseEnvironment : public Instruction {
  public:
    explicit PromiseEnvironment(const promise_id_t id,
                                const environment_id_t environment_id)
        : Instruction{}, id_{id}, environment_id_{environment_id} {}

    const promise_id_t get_id() const { return id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    virtual ~PromiseEnvironment() {}

  private:
    promise_id_t id_;
    environment_id_t environment_id_;
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_ENVIRONMENT_INSTRUCTION_H */
