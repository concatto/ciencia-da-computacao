#include "program.h"
#include <fstream>
#include <iostream>

Program::Program()
{

}

Instruction Program::fetch(unsigned int index) const
{
    return instructions[index];
}

unsigned int Program::getLength() const
{
    return instructions.size();
}

Program Program::fromFile(std::string path)
{
    Program program;

    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        unsigned int data = std::stoul(line, nullptr, 16);
        program.instructions.push_back(Instruction::decode(data));
    }

    file.close();
    return program;
}
