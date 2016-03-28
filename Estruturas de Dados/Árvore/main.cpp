#include <iostream>
#include "binary_tree.h"

int main() {
    BinaryTree<int> tree;
    for (int i = 16; i < 32; i++) {
        tree.insert((i + 2) * 2);
    }

    for (int i = 0; i < 16; i++) {
        tree.insert((i + 2) * 2);
    }

    tree.print();

    std::cout << tree.search(64);
}
