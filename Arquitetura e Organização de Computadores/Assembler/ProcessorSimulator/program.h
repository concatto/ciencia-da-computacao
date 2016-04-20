#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include "instruction.h"

class Program
{
    std::vector<Instruction> instructions;

public:
    Program();
    Instruction fetch(unsigned int index) const;
    unsigned int getLength() const;
    static Program fromFile(std::string path);
};

#endif // PROGRAM_H
