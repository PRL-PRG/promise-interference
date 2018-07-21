#include "InstructionStream.h"
#include "utilities.h"

instruction_t InstructionStream::parse_instruction(const char *begin,
                                                   char **end) {

    if (Instruction::starts_with_opcode<FunctionEntryInstruction>(begin, end)) {
        return Instruction::parse_arguments<FunctionEntryInstruction>(*end + 1,
                                                                      end);
    }

    if (Instruction::starts_with_opcode<FunctionExitInstruction>(begin, end)) {
        return Instruction::parse_arguments<FunctionExitInstruction>(*end + 1,
                                                                     end);
    }

    if (Instruction::starts_with_opcode<FunctionContextJumpInstruction>(begin,
                                                                        end)) {
        return Instruction::parse_arguments<FunctionContextJumpInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableDefineInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            EnvironmentVariableDefineInstruction>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableAssignInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            EnvironmentVariableAssignInstruction>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableLookupInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            EnvironmentVariableLookupInstruction>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableRemoveInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            EnvironmentVariableRemoveInstruction>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentCreateInstruction>(begin,
                                                                      end)) {
        return Instruction::parse_arguments<EnvironmentCreateInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseCreateInstruction>(begin, end)) {
        return Instruction::parse_arguments<PromiseCreateInstruction>(*end + 1,
                                                                      end);
    }

    if (Instruction::starts_with_opcode<PromiseEntryInstruction>(begin, end)) {
        return Instruction::parse_arguments<PromiseEntryInstruction>(*end + 1,
                                                                     end);
    }

    if (Instruction::starts_with_opcode<PromiseExitInstruction>(begin, end)) {
        return Instruction::parse_arguments<PromiseExitInstruction>(*end + 1,
                                                                    end);
    }

    if (Instruction::starts_with_opcode<PromiseContextJumpInstruction>(begin,
                                                                       end)) {
        return Instruction::parse_arguments<PromiseContextJumpInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueLookupInstruction>(begin,
                                                                       end)) {
        return Instruction::parse_arguments<PromiseValueLookupInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueAssignInstruction>(begin,
                                                                       end)) {
        return Instruction::parse_arguments<PromiseValueAssignInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionLookupInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<PromiseExpressionLookupInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionAssignInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<PromiseExpressionAssignInstruction>(
            *end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentLookupInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            PromiseEnvironmentLookupInstruction>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentAssignInstruction>(
            begin, end)) {
        return Instruction::parse_arguments<
            PromiseEnvironmentAssignInstruction>(*end + 1, end);
    }

    return NullInstruction{};
}

InstructionStream
InstructionStream::parse(std::filesystem::path instruction_filepath) {
    const auto & [ data, size ] = mmap_file(instruction_filepath.c_str());
    char *current = static_cast<char *>(data);
    char *end = current + size;
    char *next;
    std::vector<instruction_t> instructions;
    instructions.reserve(size / (Instruction::MINIMUM_INSTRUCTION_LENGTH + 1));

    while (current != end) {
        instructions.push_back(parse_instruction(current, &next));
        current = next + 2;
    }

    munmap_file(data, size);

    return InstructionStream{std::move(instructions)};
}

std::ostream &operator<<(std::ostream &os, const instruction_t &instruction) {
    std::visit([&](auto const &i) { os << i.to_string(); }, instruction);
    return os;
}

std::string instruction_to_string(const instruction_t &instruction) {
    std::string instruction_string;
    std::visit([&](auto const &i) { instruction_string = i.to_string(); },
               instruction);
    return instruction_string;
}

std::ostream &operator<<(std::ostream &os,
                         const InstructionStream &instruction_stream) {
    for (const instruction_t &instruction : instruction_stream) {
        // TODO - move RECORD_SEPARATOR to end of each isntruction.
        os << instruction << RECORD_SEPARATOR << std::endl;
    }
    return os;
}
