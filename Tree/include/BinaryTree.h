#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val);
};

/**
 * @brief Enum representing search method.
 */
enum class SearchMethod {
    RECURSIVE,
    BFS,
    DFS
};

class BinaryTree {
private:
    void destroyTree(TreeNode* node);
    TreeNode* root;
    TreeNode* copyTree(const TreeNode* node);
    void preorder(TreeNode* node, vector<int>& ret);
    vector<int> preorderIterative(TreeNode* node);
    void inorder(TreeNode* node, vector<int>& ret);
    vector<int> inorderIterative(TreeNode* node);
    void postorder(TreeNode* node, vector<int>& ret);
    vector<int> postorderIterative(TreeNode* node);
    vector<int> levelOrder(TreeNode* node) const;

    void dfsPaths(TreeNode* node, int targetSum, vector<int>& path, vector<vector<int>>& paths);

    int depth(TreeNode* node);

    /**
     * @brief Recursive helper function to find a value in the binary tree.
     */
    bool findRecursive(TreeNode* node, int value);

    /**
     * @brief Iterative BFS helper function to find a value in the binary tree.
     */
    bool findBFS(TreeNode* node, int value);

    /**
     * @brief Iterative DFS helper function to find a value in the binary tree.
     */
    bool findDFS(TreeNode* node, int value);

    int findMinValue(TreeNode* node);
    int findMaxValue(TreeNode* node);

    int maxDepth(TreeNode* node);
    int minDepth(TreeNode* node);
    int countNodes(TreeNode* node);

    bool isBalanced(TreeNode* node);
    bool isSameTree(TreeNode* p, TreeNode* q);
    void mirrorTree(TreeNode* node);

    /**
     * @brief Helper function to check if a tree is a full binary tree.
     * A full binary tree is a tree in which every node has either 0 or 2 children.
     *
     * @param node The root node of the binary tree.
     * @return True if the tree is a full binary tree, false otherwise.
     */
    bool isFullBinaryTree(TreeNode* node);

    /**
     * @brief Recursive helper function to check if a tree is a complete binary tree.
     * A complete binary tree is a binary tree in which every level is completely filled
     * except for possibly the last level, which is filled from left to right.
     *
     * @param node The root node of the binary tree.
     * @param index The index of the current node in a level-order traversal.
     * @param nodeCount The total number of nodes in the binary tree.
     * @return True if the tree is a complete binary tree, false otherwise.
     */
    bool isCompleteBinaryTree(TreeNode* node, int index, int nodeCount);

    TreeNode* invertTree(TreeNode* node);

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    virtual ~BinaryTree();
    virtual void insert(int value);

    /**
     * @brief Main find function that executes all three search methods and returns a bool.
     */
    bool find(int value);
    virtual void update(int oldVal, int newVal);
    void displayPreorder();
    void displayPreorderIterative();
    void displayInorder();
    void displayInorderIterative();
    void displayPostorder();
    void displayPostorderIterative();
    void displayLevelOrder();

    void displayPathSum(int targetSum);
    //Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum.
    vector<vector<int>> pathSum(TreeNode* root, int targetSum);

    int maxDepth();
    int minDepth();
    int countNodes();

    bool isSameTree(const BinaryTree& other);
    bool isBalanced();
    void mirrorTree();

    /**
     * @brief Public function to check if the binary tree is a full binary tree.
     *
     * @return True if the tree is a full binary tree, false otherwise.
     */
    bool isFullBinaryTree();

    /**
     * @brief Public function to check if the binary tree is a complete binary tree.
     *
     * @return True if the tree is a complete binary tree, false otherwise.
     */
    bool isCompleteBinaryTree();

    void invertTree();

    int findMinValue();
    int findMaxValue();

    TreeNode* getRoot();
protected:
    void setRootNode(TreeNode* node) { root = node; }
};
