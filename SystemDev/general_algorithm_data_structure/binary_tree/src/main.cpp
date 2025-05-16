#include "../include/binary_tree.hpp"
#include <iostream>

using namespace std;
using namespace binary_tree;

BinaryTree CreateCopy(const BinaryTree &original) {
    return BinaryTree(original); // Assuming the BinaryTree class has a copy constructor
}

void DisplayOrders(const BinaryTree &tree) {
    BinaryTree copy = CreateCopy(tree);

    cout << "\nTree Traversal Orders:\n";
    cout << "----------------------------\n";

    cout << "Preorder: ";
    copy.DisplayPreorder();

    cout << "Preorder Interative: ";
    copy.DisplayPreorderIterative();

    cout << "\nInorder: ";
    copy.DisplayInorder();

    cout << "Inorder Interative: ";
    copy.DisplayInorderIterative();

    cout << "Postorder: ";
    copy.DisplayPostorder();

    cout << "Postorder Interative: ";
    copy.DisplayPostorderIterative();

    cout << "LevelOrder: ";
    copy.DisplayLevelOrder();

    cout << "----------------------------\n\n";
}

void FindData(const BinaryTree &tree, int value) {
    BinaryTree copy = CreateCopy(tree);
    cout << "\nFind " << value << ": " << (copy.Find(value) ? "Found" : "Not Found") << endl;
}

void UpdateData(const BinaryTree &tree, int old_val, int new_val) {
    BinaryTree copy = CreateCopy(tree);
    copy.Update(old_val, new_val);
    cout << "\nAfter update " << old_val << " to " << new_val << ", LevelOrder: ";
    copy.DisplayLevelOrder();
    cout << endl;
}

void DisplayTreeInformation(const BinaryTree &tree) {
    BinaryTree copy = CreateCopy(tree);
    cout << "\nTree Information:\n";
    cout << "----------------------------\n";
    cout << "Maximum depth: " << copy.MaxDepth() << endl;
    cout << "Minimum depth: " << copy.MinDepth() << endl;
    cout << "Total number of nodes: " << copy.CountNodes() << endl;
    cout << "Maximum value: " << copy.FindMaxValue() << endl;
    cout << "Minimum value: " << copy.FindMinValue() << endl;
    cout << "----------------------------\n\n";
}

void DisplayTreeProperties(const BinaryTree &tree) {
    // Create a copy of the original tree to ensure that operations like mirror and invert 
    // do not modify the original tree structure.
    BinaryTree copy = CreateCopy(tree);

    cout << "\nTree Properties:\n";
    cout << "----------------------------\n";

    // Check if the tree is the same as another tree (for demonstration, comparing it with itself).
    cout << "Is the tree the same as another tree? (comparing with itself): " 
         << (copy.IsSameTree(tree) ? "Yes" : "No") << endl;

    // Check if the tree is balanced (returns true if it is balanced).
    cout << "Is the tree balanced? " 
         << (copy.IsBalanced() ? "Yes" : "No") << endl;

    // Check if the tree is a full binary tree.
    cout << "Is the tree a full binary tree? " 
         << (copy.IsFullBinaryTree() ? "Yes" : "No") << endl;

    // Check if the tree is a complete binary tree.
    cout << "Is the tree a complete binary tree? " 
         << (copy.IsCompleteBinaryTree() ? "Yes" : "No") << endl;

    // Perform mirror operation on the copy of the tree. This will not affect the original tree.
    cout << "Mirroring the tree and inverting its structure...\n";
    copy.MirrorTree();
    cout << "Tree has been mirrored (this does not affect the original tree).\n";

    // Perform the invert operation on the copy of the tree. This will not affect the original tree.
    cout << "Inverting the tree...\n";
    copy.InvertTree();
    cout << "Tree has been inverted (this does not affect the original tree).\n";

    cout << "----------------------------\n";
}

void DisplayPathSum(const BinaryTree &tree, int target_sum) {
    BinaryTree copy = CreateCopy(tree);
    cout << "\nPaths sum: ";
    copy.DisplayPathSum(target_sum);
    cout << endl;
}

void TestBinaryTree() {
    cout << "======= Testing BinaryTree =======\n";
    BinaryTree tree;

    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(1);

    DisplayOrders(tree);
    FindData(tree, 4);
    FindData(tree, 8);
    UpdateData(tree, 4, 40);
    DisplayPathSum(tree, 8);
    DisplayTreeInformation(tree);
    DisplayTreeProperties(tree);
}

void TestBinarySearchTree() {
    cout << "======= Testing BinarySearchTree =======\n";
    BinarySearchTree bst;

    bst.Insert(50);
    bst.Insert(30);
    bst.Insert(70);
    bst.Insert(20);
    bst.Insert(40);
    bst.Insert(60);
    bst.Insert(80);

    DisplayOrders(bst);
    FindData(bst, 40);
    FindData(bst, 10);
    UpdateData(bst, 40, 45);
    DisplayPathSum(bst, 100);
    DisplayTreeInformation(bst);
    DisplayTreeProperties(bst);
}

int main() {
    TestBinaryTree();
    TestBinarySearchTree();
    return 0;
}
