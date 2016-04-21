#include "controller.h"
#include <iostream>
#include <fstream>

Controller::Controller(QObject *parent) : QObject(parent)
{
}

void Controller::execute()
{
    std::vector<unsigned int> memory = Controller::readMemoryFile("ram.hex");
    Program program = Program::fromFile("rom.hex");
    processor.loadMemory(memory);
    processor.loadProgram(program);
    processor.beginExecution();

    window.setInstructions({"0xcafe", "0xface"});
    window.show();
}

std::vector<unsigned int> Controller::readMemoryFile(std::string path) {
    std::vector<unsigned int> memory;

    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            memory.push_back(std::stoul(line, nullptr, 16));
        }

        file.close();
    }
    return memory;
}
