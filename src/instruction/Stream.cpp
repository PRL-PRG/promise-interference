#include "instruction/Stream.h"
#include "utilities.h"

namespace instruction {

instruction_t Stream::parse_instruction(const char *begin, char **end) {

    if (Instruction::starts_with_opcode<FunctionEntry>(begin, end)) {
        return Instruction::parse_arguments<FunctionEntry>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<FunctionExit>(begin, end)) {
        return Instruction::parse_arguments<FunctionExit>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableDefine>(begin,
                                                                   end)) {
        return Instruction::parse_arguments<EnvironmentVariableDefine>(*end + 1,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableAssign>(begin,
                                                                   end)) {
        return Instruction::parse_arguments<EnvironmentVariableAssign>(*end + 1,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableLookup>(begin,
                                                                   end)) {
        return Instruction::parse_arguments<EnvironmentVariableLookup>(*end + 1,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableRemove>(begin,
                                                                   end)) {
        return Instruction::parse_arguments<EnvironmentVariableRemove>(*end + 1,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentCreate>(begin, end)) {
        return Instruction::parse_arguments<EnvironmentCreate>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseCreate>(begin, end)) {
        return Instruction::parse_arguments<PromiseCreate>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseEntry>(begin, end)) {
        return Instruction::parse_arguments<PromiseEntry>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseExit>(begin, end)) {
        return Instruction::parse_arguments<PromiseExit>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueLookup>(begin, end)) {
        return Instruction::parse_arguments<PromiseValueLookup>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueAssign>(begin, end)) {
        return Instruction::parse_arguments<PromiseValueAssign>(*end + 1, end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionLookup>(begin, end)) {
        return Instruction::parse_arguments<PromiseExpressionLookup>(*end + 1,
                                                                     end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionAssign>(begin, end)) {
        return Instruction::parse_arguments<PromiseExpressionAssign>(*end + 1,
                                                                     end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentLookup>(begin, end)) {
        return Instruction::parse_arguments<PromiseEnvironmentLookup>(*end + 1,
                                                                      end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentAssign>(begin, end)) {
        return Instruction::parse_arguments<PromiseEnvironmentAssign>(*end + 1,
                                                                      end);
    }
}

Stream Stream::parse(std::filesystem::path instruction_filepath) {
    const auto & [ data, size ] = mmap_file(instruction_filepath.c_str());
    char *current = static_cast<char *>(data);
    char *end = current + size;
    char *next;
    std::vector<instruction_t> instructions;
    std::size_t instruction_count{count_instructions(current, end)};
    instructions.reserve(instruction_count);
    std::size_t line_number = 0;

    while (current != end) {
        instruction_t instruction{parse_instruction(current, &next)};
        set_line_number(instruction, line_number);
        instructions.push_back(instruction);
        ++line_number;
        current = next + 1;
    }

    munmap_file(data, size);

    return Stream{std::move(instructions)};
}
}

std::ostream &operator<<(std::ostream &os, const instruction::Stream &stream) {
    for (const auto &instruction : stream) {
        os << instruction << std::endl;
    }
    return os;
}
