#include <iostream>
#include "avl_tree.h"

int main() {
	AVLTree<int, int> tree{
		1, 2, 3, 5, 0, 77, 100, 150
	};

	tree.print();

	/*AVLTree<int, int> tree{
		81, 40, 41, 23, 45, 72, 101, -3, -48, 99, 1, 2, 0
	};

	tree.print();
	/*AVLTree<int, int> tree{41, 72, 23, 45, 80, -3, 40, 77, -9, 1, 0};

	tree.print();*/
}
