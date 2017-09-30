#include "Semantico.h"
#include "Constants.h"

#include <iostream>

void Semantico::executeAction(int action, const Token *token) throw (SemanticError)
{
//    std::cout << action << "\n";
    switch (action) {
    case 0:
        stack.push(std::stof(token->getLexeme()));
        break;
    case 1:
        attribStack.push("");
        break;
    case 2:
        attribStack.top() = token->getLexeme();
        break;
    case 3:
        const std::string& var = attribStack.top();
        symbols[var] = stack.top();
        stack.pop();
        attribStack.pop();
        break;
    }
}

void Semantico::printSymbols()
{
    for (const std::pair<std::string, float> symbol : symbols) {
        std::cout << symbol.first << " := " << symbol.second << "\n";
    }
}

