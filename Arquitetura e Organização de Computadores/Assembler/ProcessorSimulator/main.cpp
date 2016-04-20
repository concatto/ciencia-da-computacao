#include "processor.h"
#include "program.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<unsigned int> readMemoryFile(std::string path) {
    std::vector<unsigned int> memory;

    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        memory.push_back(std::stoul(line, nullptr, 16));
    }

    file.close();
    return memory;
}


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    std::vector<unsigned int> memory = readMemoryFile("ram.hex");
    Program program = Program::fromFile("rom.hex");

    Processor mips;
    mips.loadMemory(memory);
    mips.loadProgram(program);
    mips.beginExecution();

    mips.printMemory(16);

//    return a.exec();
}
