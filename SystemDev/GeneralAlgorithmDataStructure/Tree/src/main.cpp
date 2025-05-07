#include "../include/BinaryTree.h"
#include "../include/BinarySearchTree.h"
#include <iostream>

using namespace std;

BinaryTree createCopy(const BinaryTree &original) {
    return BinaryTree(original); // Assuming the BinaryTree class has a copy constructor
}

void displayOrders(const BinaryTree &tree) {
    BinaryTree copy = createCopy(tree);

    cout << "\nTree Traversal Orders:\n";
    cout << "----------------------------\n";

    cout << "Preorder: ";
    copy.displayPreorder();

    cout << "Preorder Interative: ";
    copy.displayPreorderIterative();

    cout << "\nInorder: ";
    copy.displayInorder();

    cout << "Inorder Interative: ";
    copy.displayInorderIterative();

    cout << "Postorder: ";
    copy.displayPostorder();

    cout << "Postorder Interative: ";
    copy.displayPostorderIterative();

    cout << "LevelOrder: ";
    copy.displayLevelOrder();

    cout << "----------------------------\n\n";
}

void findData(const BinaryTree &tree, int value) {
    BinaryTree copy = createCopy(tree);
    cout << "\nFind " << value << ": " << (copy.find(value) ? "Found" : "Not Found") << endl;
}

void updateData(const BinaryTree &tree, int oldVal, int newVal) {
    BinaryTree copy = createCopy(tree);
    copy.update(oldVal, newVal);
    cout << "\nAfter update " << oldVal << " to " << newVal << ", LevelOrder: ";
    copy.displayLevelOrder();
    cout << endl;
}

void displayTreeInformation(const BinaryTree &tree) {
    BinaryTree copy = createCopy(tree);
    cout << "\nTree Information:\n";
    cout << "----------------------------\n";
    cout << "Maximum depth: " << copy.maxDepth() << endl;
    cout << "Minimum depth: " << copy.minDepth() << endl;
    cout << "Total number of nodes: " << copy.countNodes() << endl;
    cout << "Maximum value: " << copy.findMaxValue() << endl;
    cout << "Minimum value: " << copy.findMinValue() << endl;
    cout << "----------------------------\n\n";
}

void displayTreeProperties(const BinaryTree &tree) {
    // Create a copy of the original tree to ensure that operations like mirror and invert 
    // do not modify the original tree structure.
    BinaryTree copy = createCopy(tree);

    cout << "\nTree Properties:\n";
    cout << "----------------------------\n";

    // Check if the tree is the same as another tree (for demonstration, comparing it with itself).
    cout << "Is the tree the same as another tree? (comparing with itself): " 
         << (copy.isSameTree(tree) ? "Yes" : "No") << endl;

    // Check if the tree is balanced (returns true if it is balanced).
    cout << "Is the tree balanced? " 
         << (copy.isBalanced() ? "Yes" : "No") << endl;

    // Check if the tree is a full binary tree.
    cout << "Is the tree a full binary tree? " 
         << (copy.isFullBinaryTree() ? "Yes" : "No") << endl;

    // Check if the tree is a complete binary tree.
    cout << "Is the tree a complete binary tree? " 
         << (copy.isCompleteBinaryTree() ? "Yes" : "No") << endl;

    // Perform mirror operation on the copy of the tree. This will not affect the original tree.
    cout << "Mirroring the tree and inverting its structure...\n";
    copy.mirrorTree();
    cout << "Tree has been mirrored (this does not affect the original tree).\n";

    // Perform the invert operation on the copy of the tree. This will not affect the original tree.
    cout << "Inverting the tree...\n";
    copy.invertTree();
    cout << "Tree has been inverted (this does not affect the original tree).\n";

    cout << "----------------------------\n";
}

void displayPathSum(const BinaryTree &tree, int targetSum) {
    BinaryTree copy = createCopy(tree);
    cout << "\nPaths sum: ";
    copy.displayPathSum(targetSum);
    cout << endl;
}

void testBinaryTree() {
    cout << "======= Testing BinaryTree =======\n";
    BinaryTree tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(1);

    displayOrders(tree);
    findData(tree, 4);
    findData(tree, 8);
    updateData(tree, 4, 40);
    displayPathSum(tree, 8);
    displayTreeInformation(tree);
    displayTreeProperties(tree);
}

void testBinarySearchTree() {
    cout << "======= Testing BinarySearchTree =======\n";
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    displayOrders(bst);
    findData(bst, 40);
    findData(bst, 10);
    updateData(bst, 40, 45);
    displayPathSum(bst, 100);
    displayTreeInformation(bst);
    displayTreeProperties(bst);
}

int main() {
    testBinaryTree();
    testBinarySearchTree();
    return 0;
}
