#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stack.h"

int main() {
    std::srand(std::time(NULL));
    Stack<int> stack;

    for (int i = 0; i < 25; i++) {
        stack.push(std::rand() % 100);
    }

    StackNode<int>* node;
    while ((node = stack.pop()) != NULL) {
        std::cout << node->data << "\n";
    }
}
