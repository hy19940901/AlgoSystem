#include "../include/BinarySearchTree.h"

// BinarySearchTree member functions

BinarySearchTree::BinarySearchTree() : BinaryTree() {}

void BinarySearchTree::insert(int value) {
    setRootNode(insertBST(getRoot(), value));
}

TreeNode* BinarySearchTree::insertBST(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->value) {
        node->left = insertBST(node->left, value);
    } else if (value > node->value) {
        node->right = insertBST(node->right, value);
    }
    return node;
}

void BinarySearchTree::update(int oldVal, int newVal) {
    // In BST, update is typically a combination of removal and insertion
    setRootNode(removeBST(getRoot(), oldVal));
    insert(newVal);
}

TreeNode* BinarySearchTree::removeBST(TreeNode* node, int value) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeBST(node->left, value);
    } else if (value > node->value) {
        node->right = removeBST(node->right, value);
    } else {
        if (!node->left) {
            TreeNode* rightChild = node->right;
            delete node;
            return rightChild;
        }
        if (!node->right) {
            TreeNode* leftChild = node->left;
            delete node;
            return leftChild;
        }
        TreeNode* minNode = getMin(node->right);
        node->value = minNode->value;
        node->right = removeBST(node->right, minNode->value);
    }
    return node;
}

TreeNode* BinarySearchTree::getMin(TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}
