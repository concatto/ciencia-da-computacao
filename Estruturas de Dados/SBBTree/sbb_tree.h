#ifndef SBB_TREE
#define SBB_TREE

#include <iostream>
#include <initializer_list>

template <class K, class V>
class SBBNode {
public:
	enum Orientation {
		Horizontal, Vertical
	};

	K key;
	V value;
	SBBNode<K, V>* left;
	SBBNode<K, V>* right;
	Orientation orientation;

	SBBNode(K key, V value = V()) : key(key), value(value), left(nullptr), right(nullptr), orientation(Horizontal) {}

	bool isLeftHorizontal() const {
		return left != nullptr && left->orientation == Horizontal;
	}

	bool isRightHorizontal() const {
		return right != nullptr && right->orientation == Horizontal;
	}
};

template <class K, class V>
class SBBTree {
	using Node = SBBNode<K, V>;
	enum BalancingMode {
		RightRight, RightLeft, LeftLeft, LeftRight
	};

private:
	Node* root;
	int size;

	void rotateLeft(Node*& node) {
		Node* newRoot = node->right;
		node->right = newRoot->left;
		if (node->right != nullptr) { //Adotado
			node->right->orientation = Node::Vertical;
		}
		newRoot->left = node;

		node = newRoot;
	}

	void rotateRight(Node*& node) {
		Node* newRoot = node->left;
		node->left = newRoot->right;
		if (node->left != nullptr) { //Adotado
			node->left->orientation = Node::Vertical;
		}
		newRoot->right = node;

		node = newRoot;
	}

	void balance(Node*& violator, BalancingMode mode) {
		if (mode == RightRight) {
			rotateLeft(violator);
		} else if (mode == RightLeft) {
			rotateRight(violator->right);
			rotateLeft(violator);
		} else if (mode == LeftLeft) {
			rotateRight(violator);
		} else if (mode == LeftRight) {
			rotateLeft(violator->left);
			rotateRight(violator);
		}

		violator->orientation = Node::Horizontal;
		violator->left->orientation = violator->right->orientation = Node::Vertical;
	}

	bool insert(Node*& parent, Node* node) {
		if (parent == nullptr) {
			parent = node;
			size++;
			return true;
		} else if (node->key > parent->key) {
			bool success = insert(parent->right, node);

			if (success && parent->right->orientation == Node::Horizontal) {
				if (parent->right->isRightHorizontal()) {
					balance(parent, BalancingMode::RightRight);
				} else if (parent->right->isLeftHorizontal()) {
					balance(parent, BalancingMode::RightLeft);
				}
			}

			return success;
		} else if (node->key < parent->key) {
			bool success = insert(parent->left, node);

			if (success && parent->left->orientation == Node::Horizontal) {
				if (parent->left->isLeftHorizontal()) {
					balance(parent, BalancingMode::LeftLeft);
				} else if (parent->left->isRightHorizontal()) {
					balance(parent, BalancingMode::LeftRight);
				}
			}

			return success;
		} else {
			return false;
		}
	}

	void printRecursively(Node* node) {
		if (node == nullptr) return;

		std::cout << "(" << node->key << ", " << node->value << "); orientation = " << node->orientation << "\n";
		printRecursively(node->left);
		printRecursively(node->right);
	}

public:
	SBBTree() : root(nullptr), size(0) {}
	SBBTree(std::initializer_list<Node> nodes) : SBBTree<K, V>() {
		for (Node node : nodes) {
			insert(node.key, node.value);
		}
	}

	bool insert(K key, V value) {
		std::cout << "inserting " << key << "\n";
		return insert(root, new Node(key, value));
	}

	void print() {
		printRecursively(root);
	}
};

#endif
