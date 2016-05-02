#include "controller.h"
#include "instructiontranslator.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Controller::Controller(QObject *parent) : QObject(parent)
{
}

void Controller::execute()
{
    std::vector<unsigned int> memory;
    std::vector<unsigned int> program;

    readHexadecimalFile("ram.hex", [&](unsigned int value) { memory.push_back(value); });
    readHexadecimalFile("rom.hex", [&](unsigned int value) { program.push_back(value); });

    processor.loadMemory(memory);
    processor.loadProgram(program);

    for (unsigned int i = 0; i < program.size(); i++) {
        window.addInstruction(Utils::toHexString(Processor::ProgramCounterOffset + (i * 4)), Utils::toHexString(program[i]));
    }

    for (unsigned int i = 0; i < memory.size(); i++) {
        window.addMemoryWord(Utils::toHexString(Processor::MemoryOffset + (i * 4)), Utils::toHexString(memory[i]));
    }

    for (unsigned int i = 0; i < Processor::RegisterNames.size(); i++) {
        window.addRegister(Processor::RegisterNames[i], Utils::toHexString(0));
    }

    QObject::connect(&window, &MainWindow::executionRequested, &processor, &Processor::beginExecution);
    QObject::connect(&window, &MainWindow::stopRequested, &processor, &Processor::stopExecution);
    QObject::connect(&window, &MainWindow::advanceRequested, &processor, &Processor::executeProcessorCycle);
    QObject::connect(&window, &MainWindow::revertRequested, &processor, &Processor::resetState);

    QObject::connect(&processor, &Processor::executionTerminated, &window, &MainWindow::finishExecution);
    QObject::connect(&processor, &Processor::memoryChanged, [&](unsigned int address, unsigned int value) {
        window.setMemory(address, Utils::toHexString(value));
    });
    QObject::connect(&processor, &Processor::registerChanged, [&](unsigned int index, unsigned int value) {
        window.setRegister(index, Utils::toHexString(value));
    });
    QObject::connect(&processor, &Processor::instructionDecoded, &window, [&](Instruction instruction, unsigned int programCounter) {
        std::string str(Utils::toHexString(instruction.rawData) + " => " + InstructionTranslator::toString(instruction));
        window.setInstructionLabel(str);
        window.highlightInstructionRow(programCounter);
    });

    window.show();
}

void Controller::readHexadecimalFile(std::string path, std::function<void (unsigned int)> callback)
{
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            callback(std::stoul(line, nullptr, 16));
        }

        file.close();
    }
}
