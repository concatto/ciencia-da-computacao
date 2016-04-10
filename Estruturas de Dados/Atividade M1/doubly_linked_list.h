#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "list.h"

template <class T>
struct DoubleNode {
    T value;
    DoubleNode<T>* next;
	DoubleNode<T>* previous;

    DoubleNode() : next(NULL), previous(NULL) {}
    DoubleNode(T value) : value(value), next(NULL), previous(NULL) {}
};

template <class T>
class DoublyLinkedList : public List<T> {
private:
    using List<T>::size;
    DoubleNode<T>* initial;
	DoubleNode<T>* last;
    DoubleNode<T>* iterator;

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

public:
    DoublyLinkedList(DoubleNode<T>* initial = NULL, DoubleNode<T>* last = NULL, int size = 0)
        : List<T>(size), initial(initial), last(last) {}

	bool remove(int position) override {
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

    bool insert(T value, int position) override {
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

    void begin() override {
        iterator = initial;
    }

    void end() {
        iterator = last;
    }

    bool hasNext() override {
        return iterator != last->next && iterator != initial->previous;
    }

    T& next() override {
        T& value = iterator->value;
        iterator = iterator->next;
        return value;
    }

    T& peek() override {
        return iterator->value;
    }

    T& previous() {
        T& value = iterator->value;
        iterator = iterator->previous;
        return value;
    }

    T& get(int position) override {
        return getNode(position)->value;
    }

    List<T>* subList(int begin, int length) override {
        return new DoublyLinkedList<T>(getNode(begin), getNode(begin + length - 1), length);
    }
};

#endif
