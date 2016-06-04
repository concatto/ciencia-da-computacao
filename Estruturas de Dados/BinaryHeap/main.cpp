#include <iostream>
#include "binary_heap.h"

int main() {
    BinaryHeap<int, int> heap(10, {4, 10, 3, 5, 2, 1, 9});

    while (heap.getSize() > 0) {
        std::cout << heap.getMinimum().key << "\n";
        heap.removeMinimum();
    }
}
