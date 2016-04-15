#ifndef STACK_H
#define STACK_H

template <class T>
struct StackNode {
    T data;
    StackNode<T>* next;

    StackNode(T data, StackNode<T>* next = NULL) : data(data), next(next) {}
};

template <class T>
class Stack {
    StackNode<T>* head;
    int size;

public:
    Stack() : size(0), head(NULL) {}

    void push(T data) {
        StackNode<T>* node = new StackNode<T>(data, head);
        node->next = head;
        head = node;
        size++;
    }

    T pop() {
        if (head == NULL) return static_cast<T>(NULL);

        StackNode<T>* obsolete = head;
        head = head->next;
		T data = obsolete->data;
		delete obsolete;
        size--;
        return data;
    }

    T peek() {
        if (head == NULL) {
            return static_cast<T>(NULL);
        } else {
            return head->data;
        }
    }

    int getSize() const {
        return size;
    }
};

#endif
