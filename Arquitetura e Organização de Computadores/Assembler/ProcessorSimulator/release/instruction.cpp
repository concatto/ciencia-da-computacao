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
