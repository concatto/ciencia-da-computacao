#include "instructiontranslator.h"
#include <sstream>
#include <vector>

std::unordered_map<unsigned int, std::string> InstructionTranslator::RNames({
        {0x00, "sll"},  {0x02, "srl"}, {0x08, "jr"}, {0x20, "add"},
        {0x21, "addu"}, {0x22, "sub"}, {0x24, "and"}, {0x25, "or"},
        {0x26, "xor"},  {0x27, "nor"}
});

std::unordered_map<unsigned int, std::string> InstructionTranslator::IJNames({
        {0x02, "j"},    {0x03, "jal"},   {0x04, "beq"},  {0x25, "bne"},
        {0x08, "addi"}, {0x09, "addiu"}, {0x0A, "slti"}, {0x0C, "andi"},
        {0x0D, "ori"},  {0x0E, "xori"},  {0x0F, "lui"},  {0x23, "lw"},
        {0x2B, "sw"}
});

InstructionTranslator::InstructionTranslator()
{
}

std::string InstructionTranslator::toString(const Instruction& instruction)
{
    const std::vector<std::string>& names = Processor::RegisterNames;
    std::stringstream stream;

    if (instruction.opCode == 0) { //R format
        stream << RNames[instruction.function] << " ";

        if (instruction.function <= 2) {
            //Shift
            stream << names[instruction.rd] << ", " << names[instruction.rs] << ", " << instruction.shiftAmount;
        } else if (instruction.function == 8) {
            //Jump register
            stream << names[instruction.rs];
        } else {
            //Three registers (sub, add...)
            stream << names[instruction.rd] << ", " << names[instruction.rs] << ", " << names[instruction.rt];
        }
    } else { //I or J format
        stream << IJNames[instruction.opCode] << " ";

        if (instruction.opCode <= 2) {
            //j, jal
            stream << instruction.immediate26;
        } else if (instruction.opCode <= 14) {
            //register, register, immediate
            stream << names[instruction.rs] << ", " << names[instruction.rt] << ", " << instruction.immediate16;
        } else if (instruction.opCode == 15) {
            //lui
            stream << names[instruction.rt] << ", " << instruction.immediate16;
        } else {
            //lw, sw
            stream << names[instruction.rt] << ", " << instruction.immediate16 << "(" << names[instruction.rs] << ")";
        }
    }

    return stream.str();
}

