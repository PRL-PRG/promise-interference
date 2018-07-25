#ifndef PROMISE_INTERFERENCE_PROMISE_CREATE_INSTRUCTION_H
#define PROMISE_INTERFERENCE_PROMISE_CREATE_INSTRUCTION_H

#include "Instruction.h"
#include <sstream>

namespace instruction {

class PromiseCreate : public Instruction {
  public:
    explicit PromiseCreate(const promise_id_t id,
                           const environment_id_t environment_id,
                           const expression_t &expression)
        : Instruction{}, id_{id}, environment_id_{environment_id},
          expression_{expression} {}

    const promise_id_t get_id() const { return id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    const expression_t &get_expression() const { return expression_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_id() << UNIT_SEPARATOR
               << get_environment_id() << UNIT_SEPARATOR << get_expression()
               << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {}

    static const opcode_t &get_opcode();

    static PromiseCreate parse_arguments(const char *begin, char **end);

  private:
    promise_id_t id_;
    environment_id_t environment_id_;
    expression_t expression_;
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_CREATE_INSTRUCTION_H */
