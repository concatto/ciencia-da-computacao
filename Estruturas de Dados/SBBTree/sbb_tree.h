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
	Orientation leftOrientation;
	Orientation rightOrientation;
	
	SBBNode(K key, V value = V()) : key(key), value(value), left(nullptr), right(nullptr), leftOrientation(Horizontal), rightOrientation(Horizontal) {}
	
	bool isLeftHorizontal() const {
		return left != nullptr && leftOrientation == Horizontal;
	}
	
	bool isRightHorizontal() const {
		return right != nullptr && rightOrientation == Horizontal;
	}
};

template <class K, class V>
class SBBTree {
	using Node = SBBNode<K, V>;
	enum InsertionResult {
		Failed, Succeeded, Balanced
	};
	
private:
	Node* root;
	int size;
	
	void rotateLeft(Node*& node) {
		Node* newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;
		newRoot->leftOrientation = Node::Vertical;
		newRoot->rightOrientation = Node::Vertical;

		node = newRoot;
	}

	void rotateRight(Node*& node) {
		Node* newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;
		newRoot->leftOrientation = Node::Vertical;
		newRoot->rightOrientation = Node::Vertical;
		
		node = newRoot;
	}
	
	InsertionResult insert(Node*& parent, Node* node) {
		if (parent == nullptr) {
			parent = node;
			size++;
			return Succeeded;
		} else if (node->key > parent->key) {
			InsertionResult result = insert(parent->right, node);
			if (result == Balanced) {
				parent->rightOrientation = Node::Horizontal;
			}
			
			if ((result == Succeeded || result == Balanced) && parent->rightOrientation == Node::Horizontal) {
				if (parent->right->isRightHorizontal()) {
					std::cout << "Direita-direita !\n";
					rotateLeft(parent);
					return Balanced;
				} else if (parent->right->isLeftHorizontal()) {
					std::cout << "Direita-esquerda!\n";
					rotateRight(parent->right);
					rotateLeft(parent);
					return Balanced;
				}
			}
			
			return result;
		} else if (node->key < parent->key) {
			InsertionResult result = insert(parent->left, node);
			if (result == Balanced) {
				parent->leftOrientation = Node::Horizontal;
			}
			
			if ((result == Succeeded || result == Balanced) && parent->leftOrientation == Node::Horizontal) {
				if (parent->left->isLeftHorizontal()) {
					std::cout << "Esquerda-esquerda!\n";
					rotateRight(parent);
					return Balanced;
				} else if (parent->left->isRightHorizontal()) {
					std::cout << "Esquerda-direita!\n";
				}
			}
			
			return result;
		} else {
			return Failed;
		}
	}
	
	void printRecursively(Node* node) {
		if (node == nullptr) return;

		std::cout << "(" << node->key << ", " << node->value << "); left = " << node->leftOrientation << "; right = " << node->rightOrientation << "\n";
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
