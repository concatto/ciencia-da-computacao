#include <iostream>
#include "static_list.h"
#include "doubly_linked_list.h"
#include "linked_list.h"

template <class T>
StaticList<T> removerIguais(StaticList<T>& origem, StaticList<T>& comparadora) {
	StaticList<T> nova(origem.getSize());
	
	for (int i = 0; i < origem.getSize(); i++) {
		bool existe = false;
		for (int j = 0; j < comparadora.getSize(); j++) {
			if (origem[i] == comparadora[j]) {
				existe = true;
				break;
			}
		}
		
		if (!existe) nova.append(origem[i]);
	}
	
	return nova;
}

template <class T>
void dois(StaticList<T> &a, StaticList<T> &b) {
	StaticList<T> aNova = removerIguais(a, b);
	StaticList<T> bNova = removerIguais(b, a);
	
	a = aNova;
	b = bNova;
}

template <class T>
void tres(DoublyLinkedList<T>& lista) {
	DoubleNode<T>* nav = lista.initial->next;
	delete lista.initial;
	lista.initial = nav;
	
	while (nav != NULL) {
		DoubleNode<T>* old = nav->next;
		
		if (nav->next == NULL) {
			lista.last = nav;
		} else {
			nav->next = nav->next->next;
			if (nav->next != NULL) {
				nav->next->previous = nav;
			} else {
				lista.last = nav;
			}
			delete old;
		}
		
		nav = nav->next;
	}
}



void doisTeste() {
	StaticList<int> a(100);
	StaticList<int> b(100);
	
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(11);
	a.append(4);
	a.append(5);
	
	b.append(0);
	b.append(1);
	b.append(2);
	b.append(3);
	b.append(4);
	b.append(5);
	b.append(9);
	b.append(10);
	b.append(3);
	
	dois(a, b);
	
	std::cout << a << "\n" << b << "\n";
}

void tresTeste() {
	DoublyLinkedList<int> a;
	
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(5);
	a.append(6);
	
	tres(a);
	
	std::cout << a << "\n";
}

template <class T>
void quatro(LinkedList<T>& a, LinkedList<T>& b, LinkedList<T>& c, int k) {
	Node<T>* nav = a.initial;
	for (int i = 0; i < k - 1; i++) {
		nav = nav->next;
	}
		
	b.initial = a.initial;
	b.size = k;
	
	c.initial = nav->next;
	c.size = a.size - k;
	
	a.initial = NULL;
	a.size = 0;
	
	nav->next = NULL;
}

void quatroTeste() {
	LinkedList<int> a;
	LinkedList<int> b;
	LinkedList<int> c;
	
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(11);
	a.append(4);
	a.append(5);
	
	quatro(a, b, c, 4);
	
	std::cout << a << "\n" << b << "\n" << c << "\n";
}

int main() {
	tresTeste();
}