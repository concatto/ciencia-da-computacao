#include "processor.h"
#include <algorithm>
#include <iostream>

Processor::Processor(QObject *parent) : QObject(parent), registers(32, 0)
{

}

void Processor::beginExecution()
{
    std::fill(registers.begin(), registers.end(), 0); //Set registers to 0
    programCounter = Processor::ProgramCounterOffset; //Initialize program counter

    while (adjustProgramCounter(programCounter) < program.getLength()) {
        Instruction instruction = fetchInstruction();
        executeInstruction(instruction);
    }
}

void Processor::executeInstruction(Instruction instruction)
{
    std::cout << instruction.opCode << std::endl;
    //Do stuff
    programCounter += 4;
}

void Processor::loadProgram(Program program)
{
    this->program = program;
}

void Processor::loadMemory(std::vector<unsigned int> memory)
{
    this->memory = memory;
}

Instruction Processor::fetchInstruction() const
{
    return program.fetch(adjustProgramCounter(programCounter));
}

unsigned int Processor::getMemory(unsigned int address) const
{
    return memory[adjustMemory(address)];
}

void Processor::setMemory(unsigned int address, unsigned int value)
{
    memory[adjustMemory(address)] = value;
}

unsigned int Processor::adjustProgramCounter(unsigned int address)
{
    return (address - Processor::ProgramCounterOffset) / 4;
}

unsigned int Processor::adjustMemory(unsigned int address)
{
    return (address - Processor::MemoryOffset) / 4;
}
