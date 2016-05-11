#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Instruction
{
public:
    unsigned int rawData;
    unsigned int opCode;
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    unsigned int shiftAmount;
    unsigned int function;
    unsigned int immediate16;
    unsigned int immediate26;

    Instruction();
    Instruction(unsigned int rawData, unsigned int opCode, unsigned int rs, unsigned int rt, unsigned int rd,
                unsigned int shiftAmount, unsigned int function, unsigned int immediate16, unsigned int immediate26);
};

#endif // INSTRUCTION_H
