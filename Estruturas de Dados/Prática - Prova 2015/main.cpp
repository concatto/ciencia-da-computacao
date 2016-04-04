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

StaticList<int> removeRepeated(StaticList<int> origin, StaticList<int> comparator) {
	StaticList<int> newList(origin.getSize());
	
	for (int i = 0; i < origin.getSize(); i++) {
		bool exists = false;
		for (int j = 0; j < comparator.getSize(); j++) {
			if (origin[i] == comparator[j]) {
				exists = true;
				break;
			}
		}
		
		if (!exists) {
			newList.append(origin[i]);
		}
	}
	
	return newList;
}

void listXor(StaticList<int>& a, StaticList<int>& b, StaticList<int>& c) {
	StaticList<int> aRemoved = removeRepeated(a, b);
	StaticList<int> bRemoved = removeRepeated(b, a);
	
	for (int i = 0; i < aRemoved.getSize(); i++) {
		c.append(aRemoved[i]);
	}
	for (int i = 0; i < bRemoved.getSize(); i++) {
		c.append(bRemoved[i]);
	}
}

template <class T>
void swap(DoublyLinkedList<T>& a, int j, int k) {
	DoubleNode<T>* jNav = a.initial;
	for (int i = 0; i < j; i++) {
		jNav = jNav->next;
	}
	DoubleNode<T>* kNav = a.initial;
	for (int i = 0; i < k; i++) {
		kNav = kNav->next;
	}
	
	T jValue = jNav->value;
	jNav->value = kNav->value;
	kNav->value = jValue;
}

template <class T>
void transfer(StaticList<T>& a, DoublyLinkedList<T>& b) {
	b.initial = new DoubleNode<T>(a[0]);
	b.last = b.initial;
	b.size++;
	for (int i = 1; i < a.getSize(); i++) {
		b.last->next = new DoubleNode<T>(a[i]);
		b.last->next->previous = b.last;
		b.last = b.last->next;
		b.size++;
	}
	
	a.size = 0;
}

int main() {
	StaticList<int> a(100);
	DoublyLinkedList<int> b;
	
	a.append(10);
	a.append(2);
	a.append(35);
	a.append(4);
	a.append(5);
	a.append(1);
	
	transfer(a, b);
	std::cout << a << "\n" << b << "\n";
	b.sort(SortMode::Merge);
	std::cout << b << "\n";
}