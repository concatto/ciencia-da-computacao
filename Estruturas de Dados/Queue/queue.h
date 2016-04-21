#include <initializer_list>

template <class T>
struct QueueNode {
	T value;
	QueueNode<T>* next;
	
	QueueNode(T value) : value(value), next(nullptr) {}
};

//first in ... ... last in
//head     ... ... tail
template <class T>
class Queue {
public:
	QueueNode<T>* head;
	QueueNode<T>* tail;
	int size;
	

	Queue() : head(nullptr), tail(nullptr), size(0) {}
	Queue(std::initializer_list<T> init) : Queue<T>() {
		for (T value : init) {
			enqueue(value);
		}
	}
	
	void enqueue(T value) {
		QueueNode<T>* node = new QueueNode<T>(value);
		
		if (size == 0) {
			head = node;
		} else {
			tail->next = node;
		}
		
		tail = node;
		size++;
	}
	
	T dequeue() {
		if (size == 0) return T();
		
		T value = head->value;
		QueueNode<T>* obsolete = head;
		head = head->next;
		if (size == 1) {
			tail = nullptr;
		}
		delete obsolete;
		size--;
		return value;
	}
	
	int getSize() const {
		return size;
	}
};