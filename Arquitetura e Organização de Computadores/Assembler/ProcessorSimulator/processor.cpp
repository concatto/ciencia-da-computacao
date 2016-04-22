#include "processor.h"
#include <algorithm>
#include <iostream>

Processor::Processor(QObject *parent) : QObject(parent), registers(32, 0)
{
    initializeInstructions();
}

void Processor::beginExecution()
{
    std::fill(registers.begin(), registers.end(), 0); //Set registers to 0
    programCounter = Processor::ProgramCounterOffset; //Initialize program counter

    while (adjustProgramCounter(programCounter) < program.size()) {
        unsigned int data = fetchInstruction();
        Instruction instruction = decodeInstruction(data);
        executeInstruction(instruction);
    }
}

void Processor::initializeInstructions()
{
    //Begin black magicks

    instructionSet[0x0] = [&](Instruction instruction) {
        InstructionMap::iterator funcIt = rInstructions.find(instruction.function);
        if (funcIt != rInstructions.end()) {
            funcIt->second(instruction);
        } else {
            std::cout << "Instruction " << std::hex << instruction.opCode << std::dec << " not found." << std::endl;
        }
    };

    //R format
    rInstructions[0x00] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rt] << ins.shiftAmount; }; //sll
    rInstructions[0x02] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rt] >> ins.shiftAmount; }; //srl
    rInstructions[0x08] = [&](Instruction ins) { programCounter = registers[ins.rs]; }; //jr
    rInstructions[0x20] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rs] + registers[ins.rt]; }; //add
    rInstructions[0x22] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rs] - registers[ins.rt]; }; //sub
    rInstructions[0x24] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rs] & registers[ins.rt]; }; //and
    rInstructions[0x25] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rs] | registers[ins.rt]; }; //or
    rInstructions[0x26] = [&](Instruction ins) { registers[ins.rd] = registers[ins.rs] ^ registers[ins.rt]; }; //xor
    rInstructions[0x27] = [&](Instruction ins) { registers[ins.rd] = ~(registers[ins.rs] | registers[ins.rt]); }; //nor

    //J format
    instructionSet[0x02] = [&](Instruction ins) { jump(ins.immediate26); }; //j
    instructionSet[0x03] = [&](Instruction ins) { registers[31] = programCounter; jump(ins.immediate26); }; //jal

    //I format
    instructionSet[0x04] = [&](Instruction ins) { if (registers[ins.rs] == registers[ins.rt]) jumpRelative(ins.immediate16); }; //beq
    instructionSet[0x05] = [&](Instruction ins) { if (registers[ins.rs] != registers[ins.rt]) jumpRelative(ins.immediate16); }; //bne
    instructionSet[0x08] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] + static_cast<int>(ins.immediate16); }; //addi
    instructionSet[0x09] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] + ins.immediate16; }; //addiu
    instructionSet[0x0A] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] < ins.immediate16 ? 1 : 0; }; //slti
    instructionSet[0x0C] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] & ins.immediate16; }; //andi
    instructionSet[0x0D] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] | ins.immediate16; }; //ori
    instructionSet[0x0E] = [&](Instruction ins) { registers[ins.rt] = registers[ins.rs] ^ ins.immediate16; }; //xori
    instructionSet[0x0F] = [&](Instruction ins) { registers[ins.rt] = ins.immediate16 << 16; }; //lui
    instructionSet[0x23] = [&](Instruction ins) { registers[ins.rt] = getMemory(registers[ins.rs] + ins.immediate16); }; //lw
    instructionSet[0x2B] = [&](Instruction ins) { setMemory(registers[ins.rs] + ins.immediate16, registers[ins.rt]); }; //sw

    //End black magicks
}

void Processor::executeInstruction(Instruction instruction)
{
    InstructionMap::iterator func = instructionSet.find(instruction.opCode);

    if (func != instructionSet.end()) {
        func->second(instruction);
    } else {
        std::cout << "Instruction " << std::hex << instruction.opCode << std::dec << " not found." << std::endl;
    }

    programCounter += 4;
}

void Processor::loadProgram(std::vector<unsigned int> program)
{
    this->program = program;
}

void Processor::loadMemory(std::vector<unsigned int> memory)
{
    this->memory = memory;
}

void Processor::loadDefaultMemory(unsigned int size)
{
    std::vector<unsigned int> mem(size, 0);
    loadMemory(mem);
}

const std::vector<unsigned int>&Processor::memoryReference() const
{
    return memory;
}

unsigned int Processor::fetchInstruction() const
{
    return program[(adjustProgramCounter(programCounter))];
}

Instruction Processor::decodeInstruction(unsigned int rawData) const
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

unsigned int Processor::getMemory(unsigned int address) const
{
    return memory[adjustMemory(address)];
}

void Processor::setMemory(unsigned int address, unsigned int value)
{
    memory[adjustMemory(address)] = value;
}

void Processor::jump(unsigned int value)
{
    programCounter = ((programCounter & 0xFFF00000) | (value << 2)) - 4;
}

void Processor::jumpRelative(unsigned int offset)
{
    programCounter += static_cast<int>(offset) * 4;
}

unsigned int Processor::adjustProgramCounter(unsigned int address)
{
    return (address - Processor::ProgramCounterOffset) / 4;
}

unsigned int Processor::adjustMemory(unsigned int address)
{
    return (address - Processor::MemoryOffset) / 4;
}
