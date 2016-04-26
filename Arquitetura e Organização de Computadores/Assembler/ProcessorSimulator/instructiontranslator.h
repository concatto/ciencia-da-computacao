#ifndef INSTRUCTIONTRANSLATOR_H
#define INSTRUCTIONTRANSLATOR_H

#include "instruction.h"
#include "processor.h"
#include <string>
#include <unordered_map>

class InstructionTranslator
{
private:
    static std::unordered_map<unsigned int, std::string> RNames;
    static std::unordered_map<unsigned int, std::string> IJNames;

public:
    InstructionTranslator();

    static std::string toString(const Instruction& instruction);
};

#endif // INSTRUCTIONTRANSLATOR_H
