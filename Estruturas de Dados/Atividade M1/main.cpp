#include <cstdlib>
#include <ctime>
#include <iostream>
#include "linked_list.h"
#include "static_list.h"
#include "doubly_linked_list.h"

enum Naipe {Copas, Ouro, Paus, Espadas};
struct Carta {
    int numero;
    Naipe naipe;

    Carta() {}
    Carta(int numero, Naipe naipe) : numero(numero), naipe(naipe) {}
};

std::ostream& operator<<(std::ostream& out, Carta& carta) {
    out << carta.numero << " de ";
    switch (carta.naipe) {
    case Copas:
        out << "Copas"; break;
    case Ouro:
        out << "Ouro"; break;
    case Paus:
        out << "Paus"; break;
    case Espadas:
        out << "Espadas"; break;
    }

    return out;
}

template <class L>
void test() {
    L list;

    for (int i = 0; i < 7; i++) {
        list.append(i);
    }

    std::cout << list << "\n";

    //Início
    list.prepend(17);
    list.removeFirst();
    list.prepend(12);
    std::cout << list << "\n";

    //Meio
    list.insert(55, 3);
    list.remove(3);
    list.insert(1337, 3);
    std::cout << list << "\n";

    //Fim
    list.append(666);
    list.removeLast();
    list.append(667);
	std::cout << list << "\n";

    list.shuffle();
    std::cout << list << "\n";

    list.sort(SortMode::Merge);
	std::cout << list << "\n";

    list.shuffle();
    std::cout << list << "\n";

    list.sort(SortMode::Bubble);
	std::cout << list << "\n\n";
}

int main() {
    test<LinkedList<int>>();
    test<StaticList<int>>();
    test<DoublyLinkedList<int>>();
}
