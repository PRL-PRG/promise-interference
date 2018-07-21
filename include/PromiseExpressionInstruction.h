#ifndef PROMISE_INTERFERENCE_PROMISE_EXPRESSION_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_EXPRESSION_INSTRUCTION_H

#include "Instruction.h"

class PromiseExpressionInstruction : public Instruction {
  public:
    explicit PromiseExpressionInstruction(const promise_id_t id,
                                          const expression_t &expression)
        : Instruction{}, id_{id}, expression_{expression} {}

    const promise_id_t get_id() const { return id_; }

    const expression_t &get_expression() const { return expression_; }

  private:
    promise_id_t id_;
    expression_t expression_;
};

#endif /* PROMISE_INTERFERENCE_PROMISE_EXPRESSION_INSTRUCTION_H */
