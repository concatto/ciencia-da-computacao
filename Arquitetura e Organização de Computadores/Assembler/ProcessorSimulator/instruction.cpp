#include "instruction.h"

Instruction::Instruction()
{
}


Instruction::Instruction(unsigned int rawData, unsigned int opCode, unsigned int rs, unsigned int rt, unsigned int rd,
                         unsigned int shiftAmount, unsigned int function, unsigned int immediate16, unsigned int immediate26)
                           : rawData(rawData), opCode(opCode), rs(rs), rt(rt), rd(rd), shiftAmount(shiftAmount),
                             function(function), immediate16(immediate16), immediate26(immediate26)
{
}

Instruction Instruction::decode(unsigned int rawData)
{
    unsigned int opCode = rawData >> 26 & 0x3F;
    unsigned int rs = (rawData >> 21) & 0x1F;
    unsigned int rt = (rawData >> 16) & 0x1F;
    unsigned int rd = (rawData >> 11) & 0x1F;
    unsigned int shiftAmount = (rawData >> 6) & 0x1F;
    unsigned int function = rawData & 0x3F;
    unsigned int immediate16 = rawData & 0xFFFF;
    unsigned int immediate26 = rawData & 0x3FFFF;

    return Instruction(rawData, opCode, rs, rt, rd, shiftAmount, function, immediate16, immediate26);
}
