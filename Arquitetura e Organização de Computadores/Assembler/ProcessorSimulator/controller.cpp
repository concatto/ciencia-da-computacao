#include "controller.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
    processor.beginExecution();

    std::vector<std::string> programStrings;
    for (unsigned int& ins : program) {
        programStrings.push_back(toHexString(ins));
    }

    window.setInstructions(programStrings);
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
