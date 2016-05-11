#include <iostream>
#include <functional>
#include <initializer_list>

template <class K, class V>
class TreeNode {
public:
	K key;
	V value;
	TreeNode<K, V>* left;
	TreeNode<K, V>* right;

	TreeNode(K key, V value) : key(key), value(value), left(nullptr), right(nullptr) {}
	bool isLeaf() const {
		return left == nullptr && right == nullptr;
	}
};

template <class K, class V>
class BinaryTree {
	using Node = TreeNode<K, V>;
private:
	Node* root;
	int size;

	bool insertRecursively(Node*& parent, Node* node) {
		if (parent == nullptr) { //Found a place to insert
			parent = node;
			size++;
			return true;
		} else if (node->key < parent->key) {
			return insertNode(parent->left, node);
		} else if (node->key > parent->key){
			return insertNode(parent->right, node);
		} else {
			return false; //Key exists
		}
	}

	Node*& searchRecursively(Node*& node, const K& key) const {
		if (node == nullptr) { //Does not exist
			return node;
		} else if (key < node->key) {
			return searchRecursively(node->left, key);
		} else if (key > node->key) {
			return searchRecursively(node->right, key);
		} else { //Found
			return node;
		}
	}

	void preOrder(std::function<void(Node*)> action, Node* node) const {
		if (node == nullptr) return;

		action(node);
		preOrder(action, node->left);
		preOrder(action, node->right);
	}

	void postOrder(std::function<void(Node*)> action, Node* node) const {
		if (node == nullptr) return;

		postOrder(action, node->left);
		postOrder(action, node->right);
		action(node);
	}

	void inOrder(std::function<void(Node*)> action, Node* node) const {
		if (node == nullptr) return;

		inOrder(action, node->left);
		action(node);
		inOrder(action, node->right);
	}

	void removeNode(Node*& node) {
		Node* greater = node->left;
		if (greater == nullptr) {
			Node* obsolete = node;
			node = node->right;
			delete obsolete;
		} else {
			Node* parent = nullptr;
			while (greater->right != nullptr) {
				parent = greater;
				greater = greater->right;
			}

			if (parent != nullptr) {
				parent->right = greater->left;
				greater->left = node->left;
			}

			greater->right = node->right;
			delete node;
			node = greater;
		}
	}

public:
	BinaryTree() : root(nullptr), size(0) {}
	BinaryTree(std::initializer_list<Node> list) : root(nullptr), size(0) {
		for (const Node& node : list) {
			insert(node.key, node.value);
		}
	}

	bool insert(K key, V value) {
		Node* node = new Node(key, value);
		if (root == nullptr) {
			root = node;
			size++;
			return true;
		}

		Node* it = root;
		Node* parent = nullptr;
		while (it != nullptr) {
			if (key == it->key) {
				return false; //Already exists
			}

			parent = it;
			it = (key < it->key) ? it->left : it->right;
		}

		//Ready to insert
		if (key < parent->key) {
			parent->left = node;
		} else {
			parent->right = node;
		}
		size++;
		return true;
	}

	bool insertRecursively(K key, V value) {
		Node* node = new Node(key, value);

		return insertRecursively(root, node);
	}

	Node* search(const K& key) const {
		Node* it = root;
		while (it != nullptr) {
			if (key < it->key) {
				it = it->left;
			} else if (key > it->key) {
				it = it->right;
			} else {
				return it; //Found
			}
		}

		return nullptr; //Does not exist
	}

	bool remove(const K& key) {
		Node*& node = searchRecursively(root, key);
		if (node == nullptr) {
			return false;
		} else {
			removeNode(node);
			return true;
		}
	}

	Node* searchRecursively(const K& key) const {
		return searchRecursively(root, key);
	}

	bool contains(const K& key) const {
		return search(key) != nullptr;
	}

	void traversePreOrder(std::function<void(Node*)> action) const {
		preOrder(action, root);
	}

	void traversePostOrder(std::function<void(Node*)> action) const {
		postOrder(action, root);
	}

	void traverseInOrder(std::function<void(Node*)> action) const {
		inOrder(action, root);
	}

	Node* getRoot() const {
		return root;
	}
};
