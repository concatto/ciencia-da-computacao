#include <iostream>
#include "binary_heap.h"

int main() {
    BinaryHeap<int, int> heap(10, {4, 10, 3, 5, 2, 1, 9});

    for (int i = 0; i < heap.getSize(); i++) {
        std::cout << heap.getData()[i].key << " ";
    }

    std::cout << "\n";
    heap.changeKey(2, 0);

    for (int i = 0; i < heap.getSize(); i++) {
        std::cout << heap.getData()[i].key << " ";
    }
}
