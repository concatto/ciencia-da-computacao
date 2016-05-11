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
	BinaryTree<int, int> tree{{10, 1}, {7, 1}, {8, 1}, {18, 1}, {1, 1}, {12, 1}, {18, 1}, {-1, 1}, {0, 1}, {11, 1}};

	tree.remove(1);
	tree.remove(18);
	tree.remove(8);
	tree.traversePreOrder([&](TreeNode<int, int>* node) {
		std::cout << node->key << "\n";
	});
}
