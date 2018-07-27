#ifndef PROMISE_INTERFERENCE_INSTRUCTION_ARGUMENT_PROMISE_ASSOCIATE_H
#define PROMISE_INTERFERENCE_INSTRUCTION_ARGUMENT_PROMISE_ASSOCIATE_H

#include "Instruction.h"
#include "logger.h"
#include <sstream>

namespace instruction {

class ArgumentPromiseAssociate : public Instruction {
  public:
    explicit ArgumentPromiseAssociate(const function_id_t &function_id,
                                      const call_id_t call_id,
                                      const position_t formal_position,
                                      const variable_id_t variable_id,
                                      const variable_name_t &variable_name,
                                      const promise_id_t promise_id)
        : Instruction{}, function_id_{function_id}, call_id_{call_id},
          formal_position_{formal_position}, variable_id_{variable_id},
          variable_name_{variable_name}, promise_id_{promise_id} {}

    const function_id_t &get_function_id() const { return function_id_; }

    const call_id_t get_call_id() const { return call_id_; }

    const position_t get_formal_position() const { return formal_position_; }

    const variable_id_t get_variable_id() const { return variable_id_; }

    const variable_name_t &get_variable_name() const { return variable_name_; }

    const promise_id_t get_promise_id() const { return promise_id_; }

    std::string to_string() const override {
        std::stringstream stream;
        stream << get_opcode() << UNIT_SEPARATOR << get_function_id()
               << UNIT_SEPARATOR << get_call_id() << UNIT_SEPARATOR
               << get_formal_position() << UNIT_SEPARATOR << get_variable_id()
               << UNIT_SEPARATOR << get_variable_name() << UNIT_SEPARATOR
               << get_promise_id() << RECORD_SEPARATOR;
        return stream.str();
    }

    void interpret(state::AbstractState &state) const override {
        // TODO
        // state.enter_scope(scope::FunctionScope{
        //     get_type(), get_id(), get_call_id(), get_environment_id()});
    }

    static const opcode_t &get_opcode();

    static ArgumentPromiseAssociate parse_arguments(const char *begin,
                                                    char **end);

  private:
    function_id_t function_id_;
    call_id_t call_id_;
    position_t formal_position_;
    variable_id_t variable_id_;
    variable_name_t variable_name_;
    promise_id_t promise_id_;
};
}

inline std::ostream &
operator<<(std::ostream &os,
           const instruction::ArgumentPromiseAssociate &instruction) {
    return os << instruction.to_string();
}

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_ARGUMENT_PROMISE_ASSOCIATE_H */
