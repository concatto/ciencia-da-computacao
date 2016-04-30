#include <iostream>
#include <functional>

template <class K, class V>
class TreeNode {
public:
	K key;
	V value;
	TreeNode<K, V>* left;
	TreeNode<K, V>* right;
	
	TreeNode(K key, V value) : key(key), value(value), left(nullptr), right(nullptr) {}
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
	
	Node* searchRecursively(Node* node, const K& key) const {
		if (node == nullptr) {
			return nullptr; //Does not exist
		} else if (key < node->key) {
			return search(node->left, key);
		} else if (key > node->key) {
			return search(node->right, key);
		} else {
			return node; //Found
		}
	}
	
	void depthFirstSearch(std::function<void(Node*)> action, Node* node) const {
		if (node == nullptr) return;
		
		action(node);
		depthFirstSearch(action, node->left);
		depthFirstSearch(action, node->right);
	}
	
public:
	BinaryTree() : root(nullptr), size(0) {}
	
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
	
	Node* searchRecursively(const K& key) const {
		return searchRecursively(root, key);
	}
	
	bool contains(const K& key) const {
		return search(key) != nullptr;
	}
	
	void depthFirstSearch(std::function<void(Node*)> action) const {
		depthFirstSearch(action, root);
	}
};