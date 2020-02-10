#include "instruction/Stream.h"
#include "utilities.h"

namespace instruction {

instruction_t Stream::parse_instruction(const char *begin, char **end) {

    if (Instruction::starts_with_opcode<ClosureEntry>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<ClosureEntry>(*end, end);
    }

    if (Instruction::starts_with_opcode<ClosureExit>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<ClosureExit>(*end, end);
    }

    if (Instruction::starts_with_opcode<BuiltinEntry>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<BuiltinEntry>(*end, end);
    }

    if (Instruction::starts_with_opcode<BuiltinExit>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<BuiltinExit>(*end, end);
    }

    if (Instruction::starts_with_opcode<SpecialEntry>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<SpecialEntry>(*end, end);
    }

    if (Instruction::starts_with_opcode<SpecialExit>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<SpecialExit>(*end, end);
    }

    if (Instruction::starts_with_opcode<ArgumentPromiseAssociate>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<ArgumentPromiseAssociate>(*end,
                                                                      end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableDefine>(begin,
                                                                   end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<EnvironmentVariableDefine>(*end,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableAssign>(begin,
                                                                   end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<EnvironmentVariableAssign>(*end,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableLookup>(begin,
                                                                   end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<EnvironmentVariableLookup>(*end,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentVariableRemove>(begin,
                                                                   end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<EnvironmentVariableRemove>(*end,
                                                                       end);
    }

    if (Instruction::starts_with_opcode<EnvironmentCreate>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<EnvironmentCreate>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseCreate>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseCreate>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseEntry>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseEntry>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseExit>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseExit>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueLookup>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseValueLookup>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseValueAssign>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseValueAssign>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionLookup>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseExpressionLookup>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseExpressionAssign>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseExpressionAssign>(*end, end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentLookup>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseEnvironmentLookup>(*end,
                                                                      end);
    }

    if (Instruction::starts_with_opcode<PromiseEnvironmentAssign>(begin, end)) {
        parse_operand_separator(*end, end);
        return Instruction::parse_arguments<PromiseEnvironmentAssign>(*end,
                                                                      end);
    }
}

Stream Stream::parse(std::filesystem::path instruction_filepath) {
    const auto &[data, size] = mmap_file(instruction_filepath.c_str());
    char *current = static_cast<char *>(data);
    char *end = current + size;
    char *next;
    std::vector<instruction_t> instructions;
    std::size_t instruction_count{count_instructions(current, end)};
    instructions.reserve(instruction_count);
    line_number_t line_number = 0;

    while (current != end) {
        instruction_t instruction{parse_instruction(current, &next)};
        std::cerr << instruction << std::endl;
        set_line_number(instruction, line_number);
        instructions.push_back(instruction);
        ++line_number;
        current = next + 1;
    }

    munmap_file(data, size);

    return Stream{std::move(instructions)};
}
} // namespace instruction
