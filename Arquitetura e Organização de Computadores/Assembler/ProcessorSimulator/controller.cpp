#include "controller.h"
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
        window.addInstruction(toHexString(Processor::ProgramCounterOffset + (i * 4)), toHexString(program[i]));
    }

    for (unsigned int i = 0; i < memory.size(); i++) {
        window.addMemoryWord(toHexString(Processor::MemoryOffset + (i * 4)), toHexString(memory[i]));
    }

    for (unsigned int i = 0; i < Processor::RegisterNames.size(); i++) {
        window.addRegister(Processor::RegisterNames[i], toHexString(0));
    }

    QObject::connect(&window, &MainWindow::executionRequested, &processor, &Processor::beginExecution);
    QObject::connect(&processor, &Processor::programCounterChanged, &window, &MainWindow::highlightInstructionRow);
    QObject::connect(&processor, &Processor::memoryChanged, [&](unsigned int address, unsigned int value) {
        window.setMemory(address, toHexString(value));
    });

    QObject::connect(&processor, &Processor::registerChanged, [&](unsigned int index, unsigned int value) {
        window.setRegister(index, toHexString(value));
    });

    window.show();
}

std::string Controller::toHexString(unsigned int word)
{
    std::stringstream stream;
    stream << "0x";
    for (int i = 1; i <= 8; i++) {
        stream << std::hex << ((word >> (32 - (i * 4))) & 0xF);
    }
    return stream.str();
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
