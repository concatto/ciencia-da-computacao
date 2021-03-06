#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "instruction.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include <QObject>
#include <QTimer>

class Processor : public QObject
{
    Q_OBJECT

private:
    using InstructionMap = std::unordered_map<unsigned int, std::function<void(Instruction)>>;

    InstructionMap rInstructions;
    InstructionMap instructionSet;
    std::vector<unsigned int> registers;
    std::vector<unsigned int> memory;
    std::vector<unsigned int> program;
    unsigned int programCounter;
    QTimer timer;

    void initializeInstructions();
    void executeInstruction(Instruction instruction);
    unsigned int fetchInstruction();
    Instruction decodeInstruction(unsigned int rawData);
    unsigned int getMemory(unsigned int address) const;
    void setMemory(unsigned int address, unsigned int value);
    void setRegister(unsigned int index, unsigned int value);
    void jump(unsigned int value);
    void jumpRelative(unsigned int offset);

    static unsigned int adjustProgramCounter(unsigned int address);
    static unsigned int adjustMemory(unsigned int address);
    static int extendSign(int value);
public:
    static const unsigned int ProgramCounterOffset = 0x00400000;
    static const unsigned int MemoryOffset = 0x10010000;
    static const std::vector<std::string> RegisterNames;

    explicit Processor(QObject *parent = 0);
    void loadProgram(std::vector<unsigned int> program);
    void loadMemory(std::vector<unsigned int> memory);
    void loadDefaultMemory(unsigned int size);
    const std::vector<unsigned int>& memoryReference() const;

signals:
    void instructionDecoded(Instruction instruction, unsigned int programCounter);
    void memoryChanged(unsigned int address, unsigned int newValue);
    void registerChanged(unsigned int index, unsigned int newValue);
    void executionTerminated();
    void instructionNotFound(unsigned int instruction);

public slots:
    void beginExecution();
    void executeProcessorCycle();
    void stopExecution();
    void resetState();
};

#endif // PROCESSOR_H
