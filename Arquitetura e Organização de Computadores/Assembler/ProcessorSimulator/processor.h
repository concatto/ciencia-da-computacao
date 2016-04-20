#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "program.h"
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
    Program program;
    unsigned int programCounter;

    void initializeInstructions();
    void executeInstruction(Instruction instruction);
    Instruction fetchInstruction() const;
    unsigned int getMemory(unsigned int address) const;
    void setMemory(unsigned int address, unsigned int value);
    void jump(unsigned int value);
    void jumpRelative(unsigned int offset);

    static unsigned int adjustProgramCounter(unsigned int address);
    static unsigned int adjustMemory(unsigned int address);
    static void printWord(unsigned int word);

public:
    explicit Processor(QObject *parent = 0);
    void beginExecution();
    void loadProgram(Program program);
    void loadMemory(std::vector<unsigned int> memory);
    void printMemory(unsigned int amount) const;

signals:

public slots:
};

#endif // PROCESSOR_H
