#include "stack.h"
#include <iostream>

int main() {
    std::string s = "1 aba 9 asdlkjvohoau 5 sn casi 9 dfha 5 oibjhvakcbab 1 oiasoi ";
    Stack<int> stack;
    for (int i = 0; i < s.length(); i++) {
        int valor = s[i] - '0';
        if (valor < 0 || valor > 9) continue;
        if (stack.getSize() == 0) {
            stack.push(valor);
        } else {
            if (stack.peek() == valor) {
                stack.pop();
            } else {
                stack.push(valor);
            }
        }
    }

    std::cout << "Values:\n";
    for (int i = 0; i < stack.getSize(); i++) {
        std::cout << stack.pop() << "\n";
    }
}
