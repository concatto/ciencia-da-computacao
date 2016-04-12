#include <iostream>
#include "linked_list.h"
#include "static_list.h"
#include "doubly_linked_list.h"

void test(List<int>& list) {
    for (int i = 0; i < 7; i++) {
        list.append(i);
    }

    std::cout << "Original:\t" << list << "\n";

    //Início
    list.prepend(17);
    list.removeFirst();
    list.prepend(12);
    std::cout << "No inicio:\t" << list << "\n";

    //Meio
    list.insert(55, 3);
    list.remove(3);
    list.insert(1337, 3);
    std::cout << "Na posicao:\t" << list << "\n";

    //Fim
    list.append(666);
    list.removeLast();
    list.append(667);
	std::cout << "No final:\t" << list << "\n";

    list.shuffle();
    std::cout << "Embaralhar:\t" << list << "\n";

    list.sort(SortMode::Merge);
	std::cout << "Merge sort:\t" << list << "\n";

    list.shuffle();
    std::cout << "Embaralhar:\t" << list << "\n";

    list.sort(SortMode::Bubble);
	std::cout << "Bubble sort:\t" << list << "\n";
	
	list.prepend(111);
	list.append(999);
	std::cout << "Pos ordenacao:\t" << list << "\n\n";
}

int main() {
	StaticList<int> sl(20);
	LinkedList<int> ll;
	DoublyLinkedList<int> dll;
	
    std::cout << "Static List:\n";
    test(sl);
	std::cout << "\nLinked List:\n";
    test(ll);
    std::cout << "\nDoubly Linked List:\n";
    test(dll);
}
