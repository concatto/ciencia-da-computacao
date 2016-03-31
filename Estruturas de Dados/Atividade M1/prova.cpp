#include <iostream>
#include "static_list.h"

template <class T>
StaticList<T> removerIguais(StaticList<T>& origem, StaticList<T>& comparadora) {
	StaticList<T> nova(origem.getSize());
	
	for (int i = 0; i < origem.getSize(); i++) {
		bool exists = false;
		for (int j = 0; j < comparadora.getSize(); j++) {
			if (origem[i] == comparadora[j]) {
				exists = true;
				break;
			}
		}
		
		if (!exists) {
			nova.append(origem[i]);
		}
	}
}

template <class T>
void dois(StaticList<T> &a, StaticList<T> &b) {
	StaticList<T> aNova = removerIguais(a, b);
	StaticList<T> bNova = removerIguais(b, a);
	
	std::cout << aNova << "\n" << bNova << "\n";
}

int main() {
	StaticList<int> a(5);
	StaticList<int> b(6);
	
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(4);
	a.append(5);
	
	b.append(0);
	b.append(1);
	b.append(2);
	b.append(5);
	b.append(9);
	b.append(10);
	
	dois(a, b);
}