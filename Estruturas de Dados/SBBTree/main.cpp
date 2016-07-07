#include "sbb_tree.h"
#include <iostream>

int main() {
	//SBBTree<int, int> arvore({1, 2, 3, 4, 5, 6, 10, 8, 9, 23, 15});
	SBBTree<int, int> arvore({38, 39, 20, 23, 19, 24, 5, 21, 22, 7});

	arvore.print();
}
