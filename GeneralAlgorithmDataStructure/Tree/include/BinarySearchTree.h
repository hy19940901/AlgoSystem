#pragma once
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree();
    void insert(int value) override;
    void update(int oldVal, int newVal) override;

private:
    TreeNode* insertBST(TreeNode* node, int value);
    TreeNode* removeBST(TreeNode* node, int value);
    TreeNode* getMin(TreeNode* node);
};
