#include "interpreter/interpreter.h"

namespace interpreter {

void interpret(const instruction::instruction_t &instruction,
               state::AbstractState &state) {
    std::visit([&](auto const &i) { i.interpret(state); }, instruction);
}

state::AbstractState interpret(const instruction::Stream &stream) {
    state::AbstractState state{};

    std::size_t instruction_number = 0;
    try {
        for (const auto &instruction : stream) {
            interpret(instruction, state);
            instruction_number++;
        }
    } catch (const std::exception &e) {

        std::cerr << std::endl
                  << "Instruction number: " << instruction_number << std::endl;
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    return state;
}

state::AbstractState interpret(const std::filesystem::path trace_filepath) {
    return interpret(instruction::Stream::parse(trace_filepath));
}
}
