#include "Instruction.h"

const opcode_t Instruction::OPCODE_NULL = "nul";
const opcode_t Instruction::OPCODE_FUNCTION_ENTRY = "fnb";
const opcode_t Instruction::OPCODE_FUNCTION_EXIT = "fnf";
const opcode_t Instruction::OPCODE_FUNCTION_CONTEXT_JUMP = "fnj";
const opcode_t Instruction::OPCODE_PROMISE_CREATE = "prc";
const opcode_t Instruction::OPCODE_PROMISE_ENTRY = "prb";
const opcode_t Instruction::OPCODE_PROMISE_EXIT = "prf";
const opcode_t Instruction::OPCODE_PROMISE_VALUE_LOOKUP = "pvl";
const opcode_t Instruction::OPCODE_PROMISE_EXPRESSION_LOOKUP = "pel";
const opcode_t Instruction::OPCODE_PROMISE_ENVIRONMENT_LOOKUP = "prl";
const opcode_t Instruction::OPCODE_PROMISE_VALUE_ASSIGN = "pva";
const opcode_t Instruction::OPCODE_PROMISE_EXPRESSION_ASSIGN = "pea";
const opcode_t Instruction::OPCODE_PROMISE_ENVIRONMENT_ASSIGN = "pra";
const opcode_t Instruction::OPCODE_PROMISE_CONTEXT_JUMP = "prj";
const opcode_t Instruction::OPCODE_ENVIRONMENT_CREATE = "enc";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_ASSIGN = "ena";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_REMOVE = "enr";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_DEFINE = "end";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_LOOKUP = "enl";
const std::size_t Instruction::MINIMUM_INSTRUCTION_LENGTH = 6;
