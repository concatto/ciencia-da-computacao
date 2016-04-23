#include "queue.h"
#include <utility>
#include <iostream>

int main() {
	Queue<int> queue({1, 2, 3, 4});
	
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
}