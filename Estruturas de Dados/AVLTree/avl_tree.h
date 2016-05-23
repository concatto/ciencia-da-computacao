#include <initializer_list>
#include <iostream>

template <class K, class V>
class AVLNode {
public:
	K key;
	V value;
	int balancingFactor;
	AVLNode<K, V>* left;
	AVLNode<K, V>* right;

	AVLNode(K key, V value = V()) : key(key), value(value), balancingFactor(0), left(nullptr), right(nullptr)  {}

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

	void rotateLeft(Node*& node) {
		std::cout << "rotating " << node->key << " to the left\n";
		Node* newRoot = node->right;
		std::cout << "new root is " << newRoot->key << " with factor " << newRoot->balancingFactor << "\n";
		node->right = newRoot->left;
		newRoot->left = node;

		if (node->balancingFactor == newRoot->balancingFactor) {
			node->balancingFactor = -1;
			newRoot->balancingFactor = -1;
		} else {
			newRoot->balancingFactor = node->balancingFactor == 1 ? (newRoot->balancingFactor - 1) : 0;
			node->balancingFactor = 0;
		}
		node = newRoot;
	}

	void rotateRight(Node*& node) {
		Node* newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;

		node->balancingFactor += (1 - newRoot->balancingFactor);
		newRoot->balancingFactor = 0;
		node = newRoot;
	}

	void balanceRight(Node*& violator, K key) {
		std::cout << "Violation at " << violator->key << "\n";
		//print();
		if (key > violator->right->key) {
			//Direita-direita
			rotateLeft(violator);
		} else {
			//Direita-esquerda
			rotateRight(violator->right);
			rotateLeft(violator);
		}
		//std::cout << "Afterwards:\n";
		//print();
	}

	void balanceLeft(Node*& violator, K key) {
		std::cout << "Violation at " << violator->key << "\n";
		//print();
		if (key < violator->left->key) {
			//Esquerda-esquerda
			rotateRight(violator);
		} else {
			//Esquerda-direita
			rotateLeft(violator->left);
			rotateRight(violator);
		}
		//std::cout << "Afterwards:\n";
		//print();
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
				balanceRight(parent, node->key);
				return 0;
			}

			return val;
		} else if (node->key < parent->key) {
			int val = insert(parent->left, node);
			parent->balancingFactor -= val;

			if (parent->balancingFactor == 0) {
				return 0;
			} else if (parent->balancingFactor < -1) {
				balanceLeft(parent, node->key);
				return 0;
			}

			return val;
		} else {
			return 0;
		}
	}

	void printRecursively(Node* node) {
		if (node == nullptr) return;

		std::cout << "(" << node->key << ", " << node->value << "); f = " << node->balancingFactor << "\n";
		printRecursively(node->left);
		printRecursively(node->right);
	}

public:
	Node* root;
	int size;

	AVLTree() : root(nullptr), size(0) {}
	AVLTree(std::initializer_list<Node> nodes) : AVLTree<K, V>() {
		for (Node node : nodes) {
			insert(node.key, node.value);
		}
	}

	bool insert(K key, V value) {
		if (root == nullptr) {
			root = new Node(key, value);
			size++;
			return true;
		}
		return insert(root, new Node(key, value));
	}

	void print() {
		printRecursively(root);
		std::cout << "\n";
	}
};
