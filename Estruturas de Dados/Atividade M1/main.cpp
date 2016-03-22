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

int main() {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(20);
    list.append(1);
    list.append(40);
    list.append(2);
    list.append(10);
    list.append(30);
    list.append(3);

    list.insert(27, 6);
    list.insert(17, 0);

    list.remove(0);
    list.insert(17, 0);
    list.removeLast();
    list.append(666);

	std::cout << list << "\n";
    list.sort(SortMode::Merge);
	std::cout << list << "\n";
    return 0;
}
