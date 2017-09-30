#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Token.h"
#include "SemanticError.h"
#include <stack>
#include <unordered_map>

class Semantico
{
public:
    void executeAction(int action, const Token *token) throw (SemanticError );
    void printSymbols();
private:
    std::stack<float> stack;
    std::stack<std::string> attribStack;
    std::unordered_map<std::string, float> symbols;
};

#endif
