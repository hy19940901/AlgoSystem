#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

namespace binary_tree {

/**
 * @class TreeNode
 * @brief A node structure used in binary trees.
 *
 * Each TreeNode contains an integer value, and pointers to left and right children.
 * It serves as the fundamental building block for binary trees.
 */
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
/**
 * @enum SearchMethod
 * @brief Enumeration of supported search methods within the binary tree.
 *
 * It indicates the type of search to apply: recursive (DFS), BFS (breadth-first), or DFS (depth-first iterative).
 */
enum class SearchMethod {
    RECURSIVE,
    BFS,
    DFS
};

/**
 * @class BinaryTree
 * @brief Generic binary tree implementation supporting insertion, search, traversal, and structural transformations.
 *
 * This class provides methods to insert nodes, perform different types of traversals (preorder, inorder, postorder, level-order),
 * and manipulate the tree structure (mirror, invert). It also includes utilities to evaluate properties such as balance,
 * completeness, and fullness of the tree.
 */
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    virtual ~BinaryTree();
    virtual void Insert(int value);
    virtual void Update(int old_val, int new_val);
    bool Find(int value);
    void DisplayPreorder();
    void DisplayPreorderIterative();
    void DisplayInorder();
    void DisplayInorderIterative();
    void DisplayPostorder();
    void DisplayPostorderIterative();
    void DisplayLevelOrder();
    void DisplayPathSum(int target_sum);
    std::vector<std::vector<int>> PathSum(TreeNode* root_, int target_sum);
    int MaxDepth();
    int MinDepth();
    int CountNodes();
    bool IsSameTree(const BinaryTree& other);
    bool IsBalanced();
    void MirrorTree();
    bool IsFullBinaryTree();
    bool IsCompleteBinaryTree();
    void InvertTree();
    int FindMinValue();
    int FindMaxValue();
    TreeNode* GetRoot();

protected:
    void SetRootNode(TreeNode* node);

private:
    TreeNode* root_;
    void DestroyTree(TreeNode* node);
    TreeNode* CopyTree(const TreeNode* node);
    void Preorder(TreeNode* node, std::vector<int>& result);
    std::vector<int> PreorderIterative(TreeNode* node);
    void Inorder(TreeNode* node, std::vector<int>& result);
    std::vector<int> InorderIterative(TreeNode* node);
    void Postorder(TreeNode* node, std::vector<int>& result);
    std::vector<int> PostorderIterative(TreeNode* node);
    std::vector<int> LevelOrder(TreeNode* node) const;
    void DfsPaths(TreeNode* node, int target_sum, std::vector<int>& path, std::vector<std::vector<int>>& paths);
    int Depth(TreeNode* node);
    bool FindRecursive(TreeNode* node, int value);
    bool FindBFS(TreeNode* node, int value);
    bool FindDFS(TreeNode* node, int value);
    int FindMinValue(TreeNode* node);
    int FindMaxValue(TreeNode* node);
    int MaxDepth(TreeNode* node);
    int MinDepth(TreeNode* node);
    int CountNodes(TreeNode* node);
    bool IsBalanced(TreeNode* node);
    bool IsSameTree(TreeNode* p, TreeNode* queue);
    void MirrorTree(TreeNode* node);
    bool IsFullBinaryTree(TreeNode* node);
    bool IsCompleteBinaryTree(TreeNode* node, int index, int node_count);
    TreeNode* InvertTree(TreeNode* node);
};

/**
 * @class BinarySearchTree
 * @brief Specialized binary tree where elements are organized according to BST rules.
 *
 * Inherits from BinaryTree and overrides insertion and update to maintain the BST property: 
 * for any node, values in the left subtree are less, and values in the right subtree are greater.
 */
class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree();
    void Insert(int value) override;
    void Update(int old_val, int new_val) override;

private:
    TreeNode* InsertBST(TreeNode* node, int value);
    TreeNode* RemoveBST(TreeNode* node, int value);
    TreeNode* GetMin(TreeNode* node);
};

} // namespace binary_tree

#endif // BINARY_TREE_HPP
