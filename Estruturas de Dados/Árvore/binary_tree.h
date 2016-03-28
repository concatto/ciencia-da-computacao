#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template <class T>
struct TreeNode {
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T data) : data(data), left(NULL), right(NULL) {}
};

template <class T>
class BinaryTree {
private:
    TreeNode<T>* root;

    void print(TreeNode<T>* node) {
        if (node == NULL) return;

        std::cout << node->data << "\n";
        print(node->left);
        print(node->right);
    }

    void insert(T data, TreeNode<T>* parent) {
        if (data < parent->data) {
            if (parent->left == NULL) {
                parent->left = new TreeNode<T>(data);
            } else {
                insert(data, parent->left);
            }
        } else {
            if (parent->right == NULL) {
                parent->right = new TreeNode<T>(data);
            } else {
                insert(data, parent->right);
            }
        }
    }

    TreeNode<T>* search(T key, TreeNode<T>* node) {
        std::cout << "instr\n";
        if (node == NULL) {
            return NULL;
        } else if (key == node->data) {
            return node;
        } else if (key < node->data) {
            return search(key, node->left);
        } else {
            return search(key, node->right);
        }
    }

public:
    BinaryTree() : root(NULL) {}

    void insert(T data) {
        if (root == NULL) {
            root = new TreeNode<T>(data);
        } else {
            insert(data, root);
        }
    }

    void print() {
        print(root);
    }

    TreeNode<T>* search(T key) {
        return search(key, root);
    }
};

#endif
