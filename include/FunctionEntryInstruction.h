#ifndef PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H
#define PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

class FunctionEntryInstruction : public Instruction {
  public:
    explicit FunctionEntryInstruction(const sexp_type_t &type,
                                      const function_id_t id,
                                      const call_id_t call_id,
                                      const environment_id_t environment_id)
        : Instruction{}, type_{type}, id_{id}, call_id_{call_id},
          environment_id_{environment_id} {}

    const sexp_type_t &get_type() const { return type_; }

    const function_id_t get_id() const { return id_; }

    const call_id_t get_call_id() const { return call_id_; }

    const environment_id_t get_environment_id() const {
        return environment_id_;
    }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_type() << UNIT_SEPARATOR
               << get_id() << UNIT_SEPARATOR << get_call_id() << UNIT_SEPARATOR
               << get_environment_id();
        return stream.str();
    }

    void interpret(AbstractState &state) const override {
        state.enter_scope(FunctionScope{get_type(), get_id(), get_call_id(),
                                        get_environment_id()});
    }

    static const opcode_t &get_opcode();

    static FunctionEntryInstruction parse_arguments(const char *begin,
                                                    char **end);

  private:
    sexp_type_t type_;
    function_id_t id_;
    call_id_t call_id_;
    environment_id_t environment_id_;
};

#endif /* PROMISE_INTERFERENCE_FUNCTION_ENTRY_INSTRUCTION_H */
