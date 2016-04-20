#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "program.h"
#include <vector>
#include <QObject>

class Processor : public QObject
{
    Q_OBJECT

private:
    static const unsigned int ProgramCounterOffset = 0x00400000;
    static const unsigned int MemoryOffset = 0x10010000;
    std::vector<unsigned int> registers;
    std::vector<unsigned int> memory;
    Program program;
    unsigned int programCounter;
    void executeInstruction(Instruction instruction);
    Instruction fetchInstruction() const;
    unsigned int getMemory(unsigned int address) const;
    void setMemory(unsigned int address, unsigned int value);

    static unsigned int adjustProgramCounter(unsigned int address);
    static unsigned int adjustMemory(unsigned int address);

public:
    explicit Processor(QObject *parent = 0);
    void beginExecution();
    void loadProgram(Program program);
    void loadMemory(std::vector<unsigned int> memory);

signals:

public slots:
};

#endif // PROCESSOR_H
