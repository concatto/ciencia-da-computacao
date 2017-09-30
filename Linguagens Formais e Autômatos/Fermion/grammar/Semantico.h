#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Token.h"
#include "SemanticError.h"
#include <stack>
#include <map>

class Semantico
{
private:
    std::stack<float> stack;
    std::stack<std::string> attribStack;
    std::map<std::string, float> symbols;

public:
    void executeAction(int action, const Token *token) throw (SemanticError );
    void printSymbols();
};

#endif
