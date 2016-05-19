#include <initializer_list>

template <class K, class V>
class AVLNode {
public:
	K key;
	V value;
	int balancingFactor;
	AVLNode<K, V>* left;
	AVLNode<K, V>* right;
	
	AVLNode(K key, V value) : key(key), value(value), balancingFactor(0), left(nullptr), right(nullptr)  {}
	
	int calculateHeight() {
		int leftHeight = left == nullptr ? 0 : left->calculateHeight();
		int rightHeight = right == nullptr ? 0 : right->calculateHeight();
		
		int maior = leftHeight > rightHeight ? leftHeight : rightHeight;
		return 1 + maior;
	}
};

template <class K, class V>
class AVLTree {
	using Node = AVLNode<K, V>;
	
private:
	/*void discoverOrder(Node* origin, Node* destination) {
		int first, second;
		
		first = (destination->key > origin->key) ? 1 : 0;
		origin = (destination->key > origin->key) ? origin->right : origin->left;
		first = (first << 1) | ((destination->key > origin->key) ? 1 : 0);
		
		std::string names[] = {"esq esq", "esq dir", "dir esq", "dir dir"};
		std::cout << names[first] << "\n";
	}*/
	
	void rotateRight(Node* violator, Node* inserted) {
		if (inserted->key > violator->right->key) {
			//dirdir
		} else {
			//diresq
		}
	}
	
	void rotateLeft(Node* violator, Node* inserted) {
		if (inserted->key < violator->left->key) {
			//esqesq
		} else {
			//esqdir
		}
	}

	int insert(Node*& parent, Node* node) {		
		if (parent == nullptr) {
			parent = node;
			size++;
			return 1;
		} else if (node->key > parent->key) {
			int val = insert(parent->right, node);
			parent->balancingFactor += val;
			
			if (parent->balancingFactor == 0) {
				return 0;
			} else if (parent->balancingFactor > 1) {
				rotateRight(parent, node);
				return 0;
			}
			
			return val;
		} else if (node->key < parent->key) {
			int val = insert(parent->right, node);
			parent->balancingFactor -= val;
			
			if (parent->balancingFactor == 0) {
				return 0;
			} else if (parent->balancingFactor < -1) {
				rotateLeft(parent, node);
				return 0;
			}
			
			return val; //Confirmar!
		} else {
			return 0;
		}
	}
	
	
public:
	Node* root;
	int size;
	
	AVLTree() : root(nullptr), size(0) {}
	AVLTree(std::initializer_list<Node> nodes) : AVLTree<K, V>() {
		for (Node node : nodes) {
			insert(node.key, node.value);
			std::cout << "\n";
		}
	}
	
	bool insert(K key, V value) {
		if (root == nullptr) {
			root = new Node(key, value);
			return true;
		}
		return insert(root, new Node(key, value));
	}
};