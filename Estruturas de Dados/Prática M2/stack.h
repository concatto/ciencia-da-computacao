#ifndef STACK_H
#define STACK_H

#include <initializer_list>

template <class T>
struct StackNode {
    T data;
    StackNode<T>* next;

    StackNode(T data, StackNode<T>* next = nullptr) : data(data), next(next) {}
};

template <class T>
class Stack {
    StackNode<T>* head;
    int size;

public:
    Stack() : size(0), head(nullptr) {}
	Stack(std::initializer_list<T> list) : size(0), head(nullptr) {
		for (T value : list) {
			push(value);
		}
	}

    void push(T data) {
        StackNode<T>* node = new StackNode<T>(data, head);
        node->next = head;
        head = node;
        size++;
    }

    T pop() {
        if (head == nullptr) return T();

        StackNode<T>* obsolete = head;
        head = head->next;
		T data = obsolete->data;
		delete obsolete;
        size--;
        return data;
    }

    T peek() {
        if (head == nullptr) {
            return T();
        } else {
            return head->data;
        }
    }

    int getSize() const {
        return size;
    }
};

#endif
