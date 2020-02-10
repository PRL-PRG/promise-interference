#include "instruction/Instruction.h"

namespace instruction {

const opcode_t Instruction::OPCODE_CLOSURE_ENTRY = "clb";
const opcode_t Instruction::OPCODE_CLOSURE_EXIT = "clf";
const opcode_t Instruction::OPCODE_SPECIAL_ENTRY = "spb";
const opcode_t Instruction::OPCODE_SPECIAL_EXIT = "spf";
const opcode_t Instruction::OPCODE_BUILTIN_ENTRY = "bub";
const opcode_t Instruction::OPCODE_BUILTIN_EXIT = "buf";
const opcode_t Instruction::OPCODE_ARGUMENT_PROMISE_ASSOCIATE = "apa";
const opcode_t Instruction::OPCODE_PROMISE_CREATE = "prc";
const opcode_t Instruction::OPCODE_PROMISE_ENTRY = "prb";
const opcode_t Instruction::OPCODE_PROMISE_EXIT = "prf";
const opcode_t Instruction::OPCODE_PROMISE_VALUE_LOOKUP = "pvl";
const opcode_t Instruction::OPCODE_PROMISE_EXPRESSION_LOOKUP = "pel";
const opcode_t Instruction::OPCODE_PROMISE_ENVIRONMENT_LOOKUP = "prl";
const opcode_t Instruction::OPCODE_PROMISE_VALUE_ASSIGN = "pva";
const opcode_t Instruction::OPCODE_PROMISE_EXPRESSION_ASSIGN = "pea";
const opcode_t Instruction::OPCODE_PROMISE_ENVIRONMENT_ASSIGN = "pra";
const opcode_t Instruction::OPCODE_ENVIRONMENT_CREATE = "enc";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_ASSIGN = "ena";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_REMOVE = "enr";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_DEFINE = "end";
const opcode_t Instruction::OPCODE_ENVIRONMENT_VARIABLE_LOOKUP = "enl";
}
