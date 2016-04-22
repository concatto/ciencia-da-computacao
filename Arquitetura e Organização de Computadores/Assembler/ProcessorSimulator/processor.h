#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "instruction.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include <QObject>

class Processor : public QObject
{
    Q_OBJECT

private:
    using InstructionMap = std::unordered_map<unsigned int, std::function<void(Instruction)>>;

    static const unsigned int ProgramCounterOffset = 0x00400000;
    static const unsigned int MemoryOffset = 0x10010000;
    InstructionMap rInstructions;
    InstructionMap instructionSet;
    std::vector<unsigned int> registers;
    std::vector<unsigned int> memory;
    std::vector<unsigned int> program;
    unsigned int programCounter;

    void initializeInstructions();
    void executeInstruction(Instruction instruction);
    unsigned int fetchInstruction() const;
    Instruction decodeInstruction(unsigned int rawData) const;
    unsigned int getMemory(unsigned int address) const;
    void setMemory(unsigned int address, unsigned int value);
    void jump(unsigned int value);
    void jumpRelative(unsigned int offset);

    static unsigned int adjustProgramCounter(unsigned int address);
    static unsigned int adjustMemory(unsigned int address);
public:
    explicit Processor(QObject *parent = 0);
    void beginExecution();
    void loadProgram(std::vector<unsigned int> program);
    void loadMemory(std::vector<unsigned int> memory);
    void loadDefaultMemory(unsigned int size);
    const std::vector<unsigned int>& memoryReference() const;

signals:

public slots:
};

#endif // PROCESSOR_H
