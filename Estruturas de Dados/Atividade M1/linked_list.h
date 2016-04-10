#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template <class T>
struct Node {
    T value;
    Node<T>* next;

    Node() : next(NULL) {}
    Node(T value) : value(value), next(NULL) {}
};

template <class T>
class LinkedList : public List<T> {
private:
    using List<T>::size;
    Node<T>* initial;
    Node<T>* iterator;

    Node<T>* getNode(int position) {
		if (position > size) return NULL;

        Node<T>* navigator = initial;
        for (int i = 0; i < position; i++) {
            navigator = navigator->next;
        }

        return navigator;
    }

public:
    LinkedList(Node<T>* initial = NULL, int size = 0) : List<T>(size), initial(initial) {}

	bool remove(int position) override {
		if (position >= size) return false;

        Node<T>* obsolete;

		if (position == 0) { //Caso especial para remoção no início
            obsolete = initial;
			initial = obsolete->next; //O primeiro se torna o segundo
		} else {
            Node<T>* previous = getNode(position - 1);
            obsolete = previous->next;
			previous->next = obsolete->next; //O próximo do anterior se torna o próximo do atual
		}

		delete obsolete;
		size--;
		return true;
	}

    bool insert(T value, int position) override {
		if (position > size) return false;

        Node<T>* element = new Node<T>(value);
		if (element == NULL) { //Sem memória
			return false;
		}

        if (position == 0) { //Inserção no início requer caso especial
            element->next = initial;
            initial = element;
        } else {
            Node<T>* previous = getNode(position - 1);

            element->next = previous->next;
            previous->next = element;
        }

        size++;
		return true;
    }

    void begin() override {
        iterator = initial;
    }

    bool hasNext() override {
        return iterator != NULL;
    }

    T& next() override {
        T& value = iterator->value;
        iterator = iterator->next;
        return value;
    }

    T& peek() override {
        return iterator->value;
    }

    T& get(int position) override {
        return getNode(position)->value;
    }

    List<T>* subList(int begin, int length) override {
        return new LinkedList<T>(getNode(begin), length);
    }
};

#endif
