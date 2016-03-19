#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "base.h"
#include <iostream>
#include <algorithm>

template <class T>
struct DoubleNode {
    T value;
    DoubleNode<T>* next;
	DoubleNode<T>* previous;

    DoubleNode() : next(NULL), previous(NULL) {}
    DoubleNode(T value) : value(value), next(NULL), previous(NULL) {}
};

template <class T>
class DoublyLinkedList {
private:
    DoubleNode<T>* initial;
	DoubleNode<T>* last;
    DoubleNode<T>* iterator;
    int size;

    DoubleNode<T>* nextNode() {
		DoubleNode<T>* value = iterator;
		iterator = iterator->next;
		return value;
	}

    DoubleNode<T>* getNode(int position) {
		if (position > size) return NULL;

        DoubleNode<T>* navigator = initial;
        for (int i = 0; i < position; i++) {
            navigator = navigator->next;
        }

        return navigator;
    }

    void bubbleSort() {
        bool moved;
        do {
            moved = false;
            begin();
            for (int i = 0; i < size - 1; i++) {
                DoubleNode<T>* node = nextNode();
                if (node->value > node->next->value) {
                    std::swap(node->value, node->next->value);
                    moved = true;
                }
            }
        } while (moved);
    }

    void combine(DoublyLinkedList<T>& left, DoublyLinkedList<T>& right) {
        DoublyLinkedList<T> combined;

        left.begin();
        right.begin();

        int leftIndex = 0;
        int rightIndex = 0;
        for (int i = 0; i < left.size + right.size; i++) {
            if (leftIndex == left.size) {
                //Não resta nada na esquerda, então adicionamos os elementos da direita
                combined.append(right.next());
                rightIndex++;
            } else if (rightIndex == right.size) {
                //Não resta nada na direita, então os elementos da esquerda são adicionados
                combined.append(left.next());
                leftIndex++;
            } else if (left.iterator->value > right.iterator->value) {
                //Elemento da esquerda é maior que elemento da direita, então adicionamos o elemento da direita
                combined.append(right.next());
                rightIndex++;
            } else {
                //Caso nenhuma condição seja verdadeira, o elemento da direita é maior, então adiciona-se o elemento da esquerda
                combined.append(left.next());
                leftIndex++;
            }
        }

        //Por fim, copiamos os valores ordenados para os elementos originais
        //Como o último elemento da esquerda aponta para o primeiro da direita, podemos tratar como uma lista contínua
        left.begin();
        combined.begin();
        for (int i = 0; i < combined.size; i++) {
            left.nextNode()->value = combined.next();
        }
    }

    void mergeSort() {
        if (size > 1) {
            int middle = size / 2;
            LinkedList<T> left(initial, middle);
            LinkedList<T> right(getNode(middle), size - middle);

            left.mergeSort();
            right.mergeSort();

            combine(left, right);
        }
    }

public:
    DoublyLinkedList(DoubleNode<T>* initial = NULL, int size = 0) : initial(initial), size(size) {}

	void sort(SortMode::Type mode = SortMode::Merge) {
        if (mode == SortMode::Bubble) {
            bubbleSort();
        } else if (mode == SortMode::Merge) {
            mergeSort();
        }
	}

	bool remove(int position) {
		if (position >= size) return false;

        DoubleNode<T>* obsolete;

		if (position == 0) { //Caso especial para remoção no início
            obsolete = initial;
			initial = obsolete->next; //O primeiro se torna o segundo
			initial->previous = NULL;
		} else {
            DoubleNode<T>* obsolete = getNode(position);
			obsolete->previous->next = obsolete->next;
		}

		delete obsolete;
		size--;
		return true;
	}

	bool removeFirst() {
		return remove(0);
	}

	bool removeLast() {
		return remove(size - 1);
	}

    bool insert(T value, int position) {
		if (position > size) return false;

        DoubleNode<T>* element = new DoubleNode<T>(value);
		if (element == NULL) { //Sem memória
			return false;
		}

        if (position == 0) { //Inserção no início requer caso especial
            element->next = initial;
            initial = element;
        } else {
            DoubleNode<T>* previous = getNode(position - 1);

            element->next = previous->next;
            previous->next = element;
        }

        size++;
		return true;
    }

    bool append(T value) {
        return insert(value, size);
    }

    bool prepend(T value) {
        return insert(value, 0);
    }

    void begin() {
        iterator = initial;
    }

    bool hasNext() {
        return iterator != NULL;
    }

    T next() {
        T value = iterator->value;
        iterator = iterator->next;
        return value;
    }

    int getSize() {
        return size;
    }

    T get(int position) {
        return getNode(position)->value;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list) {
    out << "{";
    list.begin();
    while (list.hasNext()) {
        out << list.next();

        if (list.hasNext()) {
			out << ", ";
		}
    }
    out << "}";
    return out;
}

#endif