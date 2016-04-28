#include "binary_tree.h"
#include <iostream>

int main() {
	BinaryTree<int, int> tree;
	
	std::cout << tree.insert(10, 100) << "\n";
	std::cout << tree.insert(11, 999) << "\n";
	std::cout << tree.insert(9, 2) << "\n";
	
	std::cout << tree.search(11)->value << "\n";
}
