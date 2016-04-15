template <class T>
struct CircularNode {
	T data;
	CircularNode<T>* next;
	
	CircularNode() : next(NULL) {}
	CircularNode(T data) : data(data), next(NULL) {}
};

template <class T>
class CircularList {
	CircularNode<T>* reference;
	int size;
	
public:
	CircularList() : reference(NULL), size(0) {}
	
	bool insert(T data) {
		CircularNode<T>* node = new CircularNode<T>(data);
		if (node == NULL) return false;
		
		if (size == 0) {
			node->next = node;
		} else {
			node->next = reference->next;
			reference->next = node;
		}
		
		reference = node;
		size++;
		return true;
	}
	
	bool remove() {
		if (size == 0) return false;
		
		CircularNode<T>* obsolete = reference;
		
		if (size > 1) {
			CircularNode<T>* navigator = reference;
			while (navigator != reference->next) {
				navigator = navigator->next;
			}
		
			navigator->next = reference->next;
			reference = navigator->next;
		} else {
			reference = NULL;
		}
		
		delete obsolete;
		size--;
		return true;
	}
};