#include "AbstractInterpreter.h"

void AbstractInterpreter::interpret(const instruction_t &instruction,
                                    AbstractState &state) {
    std::visit([&](auto const &i) { i.interpret(state); }, instruction);
}

AbstractState
AbstractInterpreter::interpret(const InstructionStream &instruction_stream) {
    AbstractState state{};

    std::size_t instruction_number = 0;
    try {
        for (const auto &instruction : instruction_stream) {
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

AbstractState
AbstractInterpreter::interpret(const std::filesystem::path trace_filepath) {
    return interpret(InstructionStream::parse(trace_filepath));
}
