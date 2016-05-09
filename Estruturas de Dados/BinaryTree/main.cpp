#include "binary_tree.h"
#include <iostream>

template <class K, class V>
TreeNode<K, V>* dfs(TreeNode<K, V>* root, V value) {
	if (root == nullptr) return nullptr;
	if (root->value == value) return root;

	TreeNode<K, V>* leftResult = dfs(root->left, value);
	if (leftResult != nullptr && leftResult->value == value) {
		return leftResult;
	}

	TreeNode<K, V>* rightResult = dfs(root->right, value);
	if (rightResult != nullptr && rightResult->value == value) {
		return rightResult;
	}
	return nullptr;
}

int main() {
	BinaryTree<int, int> tree;

	std::cout << tree.insert(10, 100) << "\n";
	std::cout << tree.insert(11, 999) << "\n";
	std::cout << tree.insert(9, 2) << "\n";
	std::cout << tree.insert(12, 999) << "\n";


	TreeNode<int, int>* a = dfs(tree.getRoot(), 999);
	std::cout << a->key << "\n";
}
