#include <iostream>

struct Test {
	int arr[10];
};

void g(Test& t) {
	Test n;
	n.arr[0] = 555;
	t = n;
}

int main() {
	Test t;
	t.arr[0] = 22;
	g(t);
	std::cout << t.arr[0] << std::endl;
	
	return 0;
}