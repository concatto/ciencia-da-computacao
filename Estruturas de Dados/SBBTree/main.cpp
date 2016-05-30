#include "sbb_tree.h"
#include <iostream>

int main() {
	//SBBTree<int, int> arvore({1, 2, 3, 4, 5, 6, 10, 8, 9, 23, 15});
	SBBTree<int, int> arvore({17, 41, 91, 13, 100, 50, 75, 25, 37, 1});

	arvore.print();
}
