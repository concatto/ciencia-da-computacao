#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stack.h"

bool isOpeningBracket(char c) {
    return c == '{' || c == '[' || c == '(';
}

bool isClosingBracket(char c) {
    return c == '}' || c == ']' || c == ')';
}

bool bracketMatches(char open, char close) {
    if (open == '{') return close == '}';
    else if (open == '[') return close == ']';
    else if (open == '(') return close == ')';
    else return false;
}

bool testBrackets(std::string expression) {
    Stack<char> stack;
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (isOpeningBracket(c)) {
            stack.push(c);
        } else if (isClosingBracket(c)) {
            if (stack.getSize() == 0) {
                std::cout << "Expressao invalida: nao existem caracteres a serem fechados\n";
                return false;
            }
            
            char lastOpening = stack.pop();
            if (!bracketMatches(lastOpening, c)) {
                std::cout << "Expressao invalida: " << c << " tentou fechar " << lastOpening << "\n";
                return false;
            }
        }
    }
    
    if (stack.getSize() > 0) {
        std::cout << "Expressao invalida: caractere nao fechado (\"" << stack.pop() << "\")\n";
        return false;
    }
    
    std::cout << "Expressao valida!\n";
    return true;
}

int main() {
    std::string expression = "{3 - [4 + 7 * (1] - 1) - 3 / 4}";
    testBrackets(expression);

    do {
        getline(std::cin, expression);
        if (!expression.empty()) testBrackets(expression);
    } while (!expression.empty());
}
