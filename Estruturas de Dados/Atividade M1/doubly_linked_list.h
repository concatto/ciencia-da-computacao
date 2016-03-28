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

        //Evitar a utilização do membro iterator para prevenir possíveis conflitos
        DoubleNode<T>* navigator;
        if (position > (size / 2)) {
            navigator = initial;
            for (int i = 0; i < position; i++) {
                navigator = navigator->next;
            }
        } else {
            navigator = last;
            for (int i = 0; i < size - position - 1; i++) {
                navigator = navigator->previous;
            }
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

        for (int i = 0; i < left.size + right.size; i++) {
            if (!left.hasMoreElements()) {
                combined.append(right.next());
            } else if (!right.hasMoreElements()) {
                combined.append(left.next());
            } else if (left.iterator->value > right.iterator->value) {
                combined.append(right.next());
            } else {
                combined.append(left.next());
            }
        }

        left.begin();
        combined.begin();
        for (int i = 0; i < combined.size; i++) {
            left.nextNode()->value = combined.next();
        }
    }

    void mergeSort() {
        if (size > 1) {
            int middle = size / 2;
            DoubleNode<T>* middleNode = getNode(middle);

            DoublyLinkedList<T> left(initial, middleNode->previous, middle);
            DoublyLinkedList<T> right(middleNode, last, size - middle);

            left.mergeSort();
            right.mergeSort();

            combine(left, right);
        }
    }

public:
    DoublyLinkedList(DoubleNode<T>* initial = NULL, DoubleNode<T>* last = NULL, int size = 0)
        : initial(initial), last(last), size(size) {}

	void sort(SortMode::Type mode = SortMode::Merge) {
        if (mode == SortMode::Bubble) {
            bubbleSort();
        } else if (mode == SortMode::Merge) {
            mergeSort();
        }
	}

    void shuffle() {
        DoubleNode<T>* navigator = initial;

        for (int i = 0; i < size - 1; i++) {
            int index = RandomNumberGenerator::generate(0, size - i - 1);
            std::swap(navigator->value, getNode(i + index)->value);
            navigator = navigator->next;
        }
    }

	bool remove(int position) {
		if (position >= size) return false;

        DoubleNode<T>* obsolete;

        if (size == 1) {
            obsolete = initial;
            initial = NULL;
            last = NULL;
        } else if (position == 0) { //Caso especial para remoção no início
            obsolete = initial;
			initial = obsolete->next;
			initial->previous = NULL;
		} else if (position == size - 1) { //Caso especial para remoção no final
            obsolete = last;
            last = obsolete->previous;
            last->next = NULL;
        } else {
            DoubleNode<T>* obsolete = getNode(position);
			obsolete->previous->next = obsolete->next;
            obsolete->next->previous = obsolete->previous;
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
		if (element == NULL) { //Falha na alocação
			return false;
		}

        if (size == 0) {
            initial = element;
            last = element;
        } else if (position == 0) {
            element->next = initial;
            initial->previous = element;
            initial = element;
        } else if (position == size) {
            element->previous = last;
            last->next = element;
            last = element;
        } else {
            DoubleNode<T>* node = getNode(position);

            element->previous = node->previous;
            element->next = node;

            node->previous->next = element;
            node->previous = element;
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

    void end() {
        iterator = last;
    }

    bool hasMoreElements() {
        return iterator != last->next && iterator != initial->previous;
    }

    T next() {
        T value = iterator->value;
        iterator = iterator->next;
        return value;
    }

    T previous() {
        T value = iterator->value;
        iterator = iterator->previous;
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
std::ostream& operator<<(std::ostream& out, DoublyLinkedList<T>& list) {
    out << "{";
    list.begin();
    while (list.hasMoreElements()) {
        out << list.next();

        if (list.hasMoreElements()) {
			out << ", ";
		}
    }
    out << "}";
    return out;
}

#endif
