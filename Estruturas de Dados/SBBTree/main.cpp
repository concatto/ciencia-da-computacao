#include "sbb_tree.h"
#include <iostream>

int main() {
	SBBTree<int, int> arvore({1, 2, 3, 4, 5, 6, 10});
	
	arvore.print();
}