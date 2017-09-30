#include <iostream>
#include "grammar/Sintatico.h"
#include "grammar/Semantico.h"
#include "grammar/Lexico.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string program = "a <- 10 + 5;";
    Lexico lexico(program.c_str());
    Semantico semantico;
    Sintatico sintatico;
    sintatico.parse(&lexico, &semantico);

    semantico.printSymbols();
    return 0;
}
