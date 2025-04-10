#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <climits> 
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Problem 1: Binary Tree Preorder, Inorder, PostOrder Traversal (LC 144, 94, 145)
 * Description:
 * Given the root of a binary tree, perform and return the result of its
 * preorder, inorder, and postorder traversals.
 *
 * - Preorder Traversal: Traverse the tree in the order: Root -> Left -> Right.
 * - Inorder Traversal: Traverse the tree in the order: Left -> Root -> Right.
 * - Postorder Traversal: Traverse the tree in the order: Left -> Right -> Root.
 *
 * Example:
 * Input: root = [1, 2, 3]
 * Output for Preorder: [1, 2, 3]
 * Output for Inorder: [2, 1, 3]
 * Output for Postorder: [2, 3, 1]
 */

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* curr = s.top();
        s.pop();
        result.push_back(curr->val);
        if (curr->right) s.push(curr->right);  // Push right first
        if (curr->left) s.push(curr->left);   // Push left next
    }
    return result;
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    return result;
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> s;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;

    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        if (!curr->right || curr->right == lastVisited) {
            result.push_back(curr->val);
            s.pop();
            lastVisited = curr;
            curr = nullptr;
        } else {
            curr = curr->right;
        }
    }
    return result;
}

/**
 * Problem 2: Binary Tree Level Order Traversal (LC 102)
 * Description:
 * Given the root of a binary tree, return the level order traversal of its nodes' values.
 * (i.e., from left to right, level by level).
 * Example:
 * Input: root = [3, 9, 20, null, null, 15, 7]
 * Output: [[3], [9, 20], [15, 7]]
 */
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

/**
 * Problem 3: Maximum Depth of Binary Tree (LC 104)
 * Description:
 * Given the root of a binary tree, return its maximum depth.
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 * Example:
 * Input: root = [3, 9, 20, null, null, 15, 7]
 * Output: 3
 */
// Post Order
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

/**
 * Problem 4: Same Tree (LC 100)
 * Description:
 * Given the roots of two binary trees, check if they are the same or not.
 * Two binary trees are considered the same if they are structurally identical
 * and the nodes have the same value.
 * Example:
 * Input: p = [1, 2, 3], q = [1, 2, 3]
 * Output: true
 */
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/**
 * Problem 5: Symmetric Tree (LC 101)
 * Description:
 * Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
 * Example:
 * Input: root = [1, 2, 2, 3, 4, 4, 3]
 * Output: true
 */
bool isSubtreeSymmetric(TreeNode* l, TreeNode* r) {
        if (!l && !r) return true;
        else if (!l || !r) return false;
        else if (l->val != r->val) return false;
        return isSubtreeSymmetric(l->left, r->right) && isSubtreeSymmetric(l->right, r->left);
    }
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isSubtreeSymmetric(root->left, root->right);
}

/**
 * Problem 6: Binary Tree Right Side View (LC 199)
 * Description:
 * Given the root of a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 * Example:
 * Input: root = [1, 2, 3, null, 5, null, 4]
 * Output: [1, 3, 4]
 */
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            if (i == size - 1) result.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

void dfsRightSideView(TreeNode* currentNode, int currentDepth, vector<int>& result) {
    if (!currentNode) return;

    // If the current depth matches the result size, it means this is the first visible node at this depth.
    if (static_cast<size_t>(currentDepth) == result.size()) {
        result.push_back(currentNode->val);
    }

    // Prioritize visiting the right subtree to ensure rightmost nodes are processed first.
    dfsRightSideView(currentNode->right, currentDepth + 1, result);
    // Then visit the left subtree.
    dfsRightSideView(currentNode->left, currentDepth + 1, result);
}

vector<int> rightSideViewDFS(TreeNode* root) {
    vector<int> result;
    dfsRightSideView(root, 0, result); // Start DFS from the root with depth 0.
    return result;
}

/**
 * Problem 7: Construct Binary Tree from Preorder and Inorder Traversal (LC 105)
 * Description:
 * Given two integer arrays preorder and inorder where preorder is the preorder traversal
 * of a binary tree and inorder is the inorder traversal of the same tree,
 * construct and return the binary tree.
 * Example:
 * Input: preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
 * Output: [3, 9, 20, null, null, 15, 7]
 */
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inorderMap;
    for (size_t i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }
    function<TreeNode*(int, int, int, int)> helper = [&](int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) return (TreeNode*)nullptr;
        TreeNode* root = new TreeNode(preorder[preStart]);
        int inRoot = inorderMap[preorder[preStart]];
        int numsLeft = inRoot - inStart;
        root->left = helper(preStart + 1, preStart + numsLeft, inStart, inRoot - 1);
        root->right = helper(preStart + numsLeft + 1, preEnd, inRoot + 1, inEnd);
        return root;
    };
    return helper(0, preorder.size() - 1, 0, inorder.size() - 1);
}

/**
 * Problem 8: Lowest Common Ancestor of a Binary Tree (LC 236)
 * Description:
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * Example:
 * Input: root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 1
 * Output: 3
 */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

/**
 * Problem 9: Validate Binary Search Tree (LC 98)
 * Description:
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * Example:
 * Input: root = [2, 1, 3]
 * Output: true
 */
bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValidBST(root->left, minVal, root->val) && isValidBST(root->right, root->val, maxVal);
}

/**
 * Problem 10: Binary Tree Zigzag Level Order Traversal (LC 103)
 * Description:
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes' values.
 * (i.e., from left to right, then right to left for the next level and alternate between).
 * Example:
 * Input: root = [3, 9, 20, null, null, 15, 7]
 * Output: [[3], [20, 9], [15, 7]]
 */
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            int index = leftToRight ? i : (size - 1 - i);
            level[index] = node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        leftToRight = !leftToRight;
        result.push_back(level);
    }
    return result;
}

/**
 * Problem 11: Flatten Binary Tree to Linked List (LC 114)
 * Description:
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * - The "linked list" should use the same TreeNode class where the right child pointer points to
 *   the next node in the list and the left child pointer is always null.
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 * Example:
 * Input: root = [1, 2, 5, 3, 4, null, 6]
 * Output: [1, 2, 3, 4, 5, 6]
 */
void flatten(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (curr->left) {
            TreeNode* pred = curr->left;
            while (pred->right) {
                pred = pred->right;
            }
            pred->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}

/**
 * Problem 12: Diameter of Binary Tree (LC 543)
 * Description:
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
 * Example:
 * Input: root = [1, 2, 3, 4, 5]
 * Output: 3
 */
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return 0;
        int left = dfs(node->left);
        int right = dfs(node->right);
        diameter = max(diameter, left + right);
        return 1 + max(left, right);
    };
    dfs(root);
    return diameter;
}

/**
 * Problem 13: Path Sum (LC 112)
 * Description:
 * Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf
 * path such that adding up all the values along the path equals targetSum.
 * Example:
 * Input: root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1], targetSum = 22
 * Output: true
 */
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    if (!root->left && !root->right) return root->val == targetSum;
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}

/**
 * Problem 14: Path Sum II (LC 113)
 * Description:
 * Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths
 * where the sum of the node values in the path equals targetSum.
 * Example:
 * Input: root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1], targetSum = 22
 * Output: [[5, 4, 11, 2], [5, 8, 4, 5]]
 */
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int target) {
        if (!node) return;
        path.push_back(node->val);
        if (!node->left && !node->right && node->val == target) {
            result.push_back(path);
        } else {
            dfs(node->left, target - node->val);
            dfs(node->right, target - node->val);
        }
        path.pop_back();
    };
    dfs(root, targetSum);
    return result;
}

/**
 * Problem 15: Balanced Binary Tree (LC 110)
 * Description:
 * Given a binary tree, determine if it is height-balanced. A height-balanced binary tree
 * is defined as a binary tree in which the depth of the two subtrees of every node
 * never differs by more than one.
 * Example:
 * Input: root = [3, 9, 20, null, null, 15, 7]
 * Output: true
 */
bool isBalanced(TreeNode* root) {
    function<int(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return 0;
        int left = dfs(node->left);
        int right = dfs(node->right);
        if (left == -1 || right == -1 || abs(left - right) > 1) return -1;
        return 1 + max(left, right);
    };
    return dfs(root) != -1;
}

/**
 * Problem 16: Minimum Depth of Binary Tree (LC 111)
 * Description:
 * Given a binary tree, find its minimum depth. The minimum depth is the number of nodes along
 * the shortest path from the root node down to the nearest leaf node.
 * Example:
 * Input: root = [3, 9, 20, null, null, 15, 7]
 * Output: 2
 */
int minDepth(TreeNode* root) {
    if (!root) return 0;
    if (!root->left) return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

/**
 * Problem 17: Convert Sorted Array to Binary Search Tree (LC 108)
 * Description:
 * Given an integer array nums where the elements are sorted in ascending order, convert it
 * into a height-balanced binary search tree.
 * Example:
 * Input: nums = [-10, -3, 0, 5, 9]
 * Output: [0, -3, 9, -10, null, 5]
 */
TreeNode* sortedArrayToBST(vector<int>& nums) {
    function<TreeNode*(int, int)> helper = [&](int left, int right) {
        if (left > right) return (TreeNode*)nullptr;
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(left, mid - 1);
        root->right = helper(mid + 1, right);
        return root;
    };
    return helper(0, nums.size() - 1);
}

/**
 * Problem 18: Binary Tree Maximum Path Sum (LC 124)
 * Description:
 * Given the root of a binary tree, return the maximum path sum. A path in a binary tree is
 * a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them.
 * Example:
 * Input: root = [-10, 9, 20, null, null, 15, 7]
 * Output: 42
 */
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return 0;
        int left = max(0, dfs(node->left));
        int right = max(0, dfs(node->right));
        maxSum = max(maxSum, left + right + node->val);
        return max(left, right) + node->val;
    };
    dfs(root);
    return maxSum;
}

/**
 * Problem 19: Construct Binary Tree from Inorder and Postorder Traversal (LC 106)
 * Description:
 * Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree
 * and postorder is the postorder traversal of the same tree, construct and return the binary tree.
 * Example:
 * Input: inorder = [9, 3, 15, 20, 7], postorder = [9, 15, 7, 20, 3]
 * Output: [3, 9, 20, null, null, 15, 7]
 */
TreeNode* buildTreeFromPostIn(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inorderMap;
    for (size_t i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }
    function<TreeNode*(int, int, int, int)> helper = [&](int inStart, int inEnd, int postStart, int postEnd) {
        if (inStart > inEnd || postStart > postEnd) return (TreeNode*)nullptr;
        TreeNode* root = new TreeNode(postorder[postEnd]);
        int inRoot = inorderMap[postorder[postEnd]];
        int numsLeft = inRoot - inStart;
        root->left = helper(inStart, inRoot - 1, postStart, postStart + numsLeft - 1);
        root->right = helper(inRoot + 1, inEnd, postStart + numsLeft, postEnd - 1);
        return root;
    };
    return helper(0, inorder.size() - 1, 0, postorder.size() - 1);
}

/**
 * Problem 20: Populating Next Right Pointers in Each Node (LC 116)
 * Description:
 * Given a perfect binary tree, populate each next pointer to point to its next right node.
 * If there is no next right node, the pointer should be set to null.
 * Example:
 * Input: root = [1, 2, 3, 4, 5, 6, 7]
 * Output: [1, #, 2, 3, #, 4, 5, 6, 7, #]
 */
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

Node* connect(Node* root) {
    if (!root) return nullptr;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        Node* prev = nullptr;
        for (int i = 0; i < size; ++i) {
            Node* node = q.front();
            q.pop();
            if (prev) prev->next = node;
            prev = node;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return root;
}

/**
 * Problem 21: Populating Next Right Pointers in Each Node II (LC 117)
 * Description:
 * Given a binary tree, populate each next pointer to point to its next right node. If there is
 * no next right node, the pointer should be set to null.
 * Example:
 * Input: root = [1, 2, 3, 4, 5, null, 7]
 * Output: [1, #, 2, 3, #, 4, 5, 7, #]
 */
Node* connectII(Node* root) {
    Node* curr = root;
    Node* head = nullptr; // Head of the next level
    Node* prev = nullptr; // Previous node on the next level
    while (curr) {
        while (curr) {
            if (curr->left) {
                if (prev) prev->next = curr->left;
                else head = curr->left;
                prev = curr->left;
            }
            if (curr->right) {
                if (prev) prev->next = curr->right;
                else head = curr->right;
                prev = curr->right;
            }
            curr = curr->next;
        }
        curr = head;
        head = nullptr;
        prev = nullptr;
    }
    return root;
}

/**
 * Problem 22: Lowest Common Ancestor of a BST (LC 235)
 * Description:
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
 * Example:
 * Input: root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5], p = 2, q = 8
 * Output: 6
 */
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (root->val > p->val && root->val > q->val) return lowestCommonAncestorBST(root->left, p, q);
    if (root->val < p->val && root->val < q->val) return lowestCommonAncestorBST(root->right, p, q);
    return root;
}

/**
 * Problem 23: Kth Smallest Element in a BST (LC 230)
 * Description:
 * Given the root of a binary search tree, and an integer k, return the kth smallest value
 * (1-indexed) of all the values of the nodes in the tree.
 * Example:
 * Input: root = [3, 1, 4, null, 2], k = 1
 * Output: 1
 */
int kthSmallest(TreeNode* root, int k) {
    function<int(TreeNode*)> inorder = [&](TreeNode* node) -> int {
        if (!node) return -1;
        int left = inorder(node->left);
        if (k == 0) return left;
        if (--k == 0) return node->val;
        return inorder(node->right);
    };

    return inorder(root);
}

/**
 * Problem 24: Serialize and Deserialize Binary Tree (LC 297)
 * Description:
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your
 * serialization/deserialization algorithm should work. You just need to ensure that a binary tree can
 * be serialized to a string and this string can be deserialized to the original tree structure.
 * Example:
 * Input: root = [1, 2, 3, null, null, 4, 5]
 * Output: [1, 2, 3, null, null, 4, 5]
 */
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "#";
        return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    TreeNode* deserialize(string data) {
        queue<string> q;
        string temp;
        for (char c : data) {
            if (c == ',') {
                q.push(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        if (!temp.empty()) q.push(temp);
        return helper(q);
    }

private:
    TreeNode* helper(queue<string>& q) {
        string val = q.front();
        q.pop();
        if (val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = helper(q);
        root->right = helper(q);
        return root;
    }
};

/**
 * Problem 25: BST Iterator (LC 173)
 * Description:
 * Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST).
 * Example:
 * Input: root = [7, 3, 15, null, null, 9, 20]
 * Output: ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
 * Output: [null, 3, 7, true, 9, true, 15, true, 20, false]
 */
class BSTIterator {
    stack<TreeNode*> s;
public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }

    int next() {
        TreeNode* node = s.top();
        s.pop();
        pushAll(node->right);
        return node->val;
    }

    bool hasNext() {
        return !s.empty();
    }

private:
    void pushAll(TreeNode* node) {
        while (node) {
            s.push(node);
            node = node->left;
        }
    }
};

/**
 * Problem 26: Recover Binary Search Tree (LC 99)
 * Description:
 * You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree
 * were swapped by mistake. Recover the tree without changing its structure.
 * Example:
 * Input: root = [1, 3, null, null, 2]
 * Output: [3, 1, null, null, 2]
 */
void recoverTree(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (prev && node->val < prev->val) {
            if (!first) first = prev;
            second = node;
        }
        prev = node;
        inorder(node->right);
    };
    inorder(root);
    swap(first->val, second->val);
}

/**
 * Problem 27: Validate Binary Tree Nodes (LC 1361)
 * Description:
 * You have n binary tree nodes numbered from 0 to n - 1 where each node has exactly one parent node, except for the root node.
 * Return true if and only if all the given nodes form exactly one valid binary tree.
 * Example:
 * Input: n = 4, leftChild = [1, -1, 3, -1], rightChild = [2, -1, -1, -1]
 * Output: true
 */
bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
    vector<int> inDegree(n, 0);
    for (int i = 0; i < n; ++i) {
        if (leftChild[i] != -1 && ++inDegree[leftChild[i]] > 1) return false;
        if (rightChild[i] != -1 && ++inDegree[rightChild[i]] > 1) return false;
    }
    int rootCount = 0;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) ++rootCount;
    }
    return rootCount == 1;
}

/**
 * Problem 28: Binary Tree Cameras (LC 968)
 * Description:
 * Given a binary tree, install the minimum number of cameras that are needed to monitor all nodes of the tree.
 * Example:
 * Input: root = [0, 0, null, 0, 0]
 * Output: 1
 */
int minCameraCover(TreeNode* root) {
    int cameras = 0;
    function<int(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return 1;
        int left = dfs(node->left);
        int right = dfs(node->right);
        if (left == 0 || right == 0) {
            ++cameras;
            return 2;
        }
        return left == 2 || right == 2 ? 1 : 0;
    };
    return (dfs(root) == 0 ? 1 : 0) + cameras;
}

/**
 * Problem 29: All Nodes Distance K in Binary Tree (LC 863)
 * Description:
 * Given the root of a binary tree, the root of a node target, and an integer k, return an array of the values
 * of all nodes that have a distance k from the target node.
 * Example:
 * Input: root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], target = 5, k = 2
 * Output: [7, 4, 1]
 */
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parentMap;
    function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node, TreeNode* parent) {
        if (!node) return;
        parentMap[node] = parent;
        dfs(node->left, node);
        dfs(node->right, node);
    };
    dfs(root, nullptr);

    queue<TreeNode*> q;
    unordered_set<TreeNode*> visited;
    q.push(target);
    visited.insert(target);
    int dist = 0;
    vector<int> result;
    while (!q.empty()) {
        int size = q.size();
        if (dist++ == k) {
            while (size--) {
                result.push_back(q.front()->val);
                q.pop();
            }
            return result;
        }
        while (size--) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left && visited.insert(node->left).second) q.push(node->left);
            if (node->right && visited.insert(node->right).second) q.push(node->right);
            if (parentMap[node] && visited.insert(parentMap[node]).second) q.push(parentMap[node]);
        }
    }
    return result;
}

/**
 * Problem 30: Sum of Distances in Tree (LC 834)
 * Description:
 * There is an undirected connected tree with n nodes labeled from 0 to n-1 and n-1 edges.
 * Return an array answer, where answer[i] is the sum of the distances between the ith node and all other nodes in the tree.
 * Example:
 * Input: n = 6, edges = [[0, 1], [0, 2], [2, 3], [2, 4], [2, 5]]
 * Output: [8, 12, 6, 10, 10, 10]
 */
vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<int> count(n, 1);
    vector<int> result(n, 0);

    function<void(int, int)> postOrder = [&](int node, int parent) {
        for (int neighbor : graph[node]) {
            if (neighbor == parent) continue;
            postOrder(neighbor, node);
            count[node] += count[neighbor];
            result[node] += result[neighbor] + count[neighbor];
        }
    };

    function<void(int, int)> preOrder = [&](int node, int parent) {
        for (int neighbor : graph[node]) {
            if (neighbor == parent) continue;
            result[neighbor] = result[node] - count[neighbor] + n - count[neighbor];
            preOrder(neighbor, node);
        }
    };

    postOrder(0, -1);
    preOrder(0, -1);

    return result;
}

int main() {
    // Problem 1: Binary Tree Traversal
    TreeNode* root1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    vector<int> preorder = preorderTraversal(root1);
    vector<int> inorder = inorderTraversal(root1);
    vector<int> postorder = postorderTraversal(root1);
    cout << "Preorder Traversal: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    cout << "Inorder Traversal: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    cout << "Postorder Traversal: ";
    for (int val : postorder) cout << val << " ";
    cout << endl;

    // Problem 2: Binary Tree Level Order Traversal
    vector<vector<int>> levels = levelOrder(root1);
    cout << "Level Order Traversal: ";
    for (const auto& level : levels) {
        for (int val : level) cout << val << " ";
        cout << "; ";
    }
    cout << endl;

    // Problem 3: Maximum Depth of Binary Tree
    cout << "Max Depth: " << maxDepth(root1) << endl;

    // Problem 4: Same Tree
    TreeNode* root4a = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    TreeNode* root4b = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    cout << "Is Same Tree: " << (isSameTree(root4a, root4b) ? "True" : "False") << endl;

    // Problem 5: Symmetric Tree
    TreeNode* root5 = new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(2, new TreeNode(4), new TreeNode(3)));
    cout << "Is Symmetric: " << (isSymmetric(root5) ? "True" : "False") << endl;

    // Problem 6: Binary Tree Right Side View
    TreeNode* root6 = new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(4)), new TreeNode(3, nullptr, new TreeNode(4)));
    vector<int> rightView = rightSideView(root6);
    vector<int> rightViewDFS = rightSideViewDFS(root6);
    cout << "Right Side View: ";
    for (int val : rightView) cout << val << " ";
    cout << endl;
    cout << "Right Side View: ";
    for (int val : rightViewDFS) cout << val << " ";
    cout << endl;

    // Problem 7: Construct Binary Tree from Preorder and Inorder Traversal
    vector<int> preorder7 = {3, 9, 20, 15, 7};
    vector<int> inorder7 = {9, 3, 15, 20, 7};
    TreeNode* root7 = buildTree(preorder7, inorder7);
    cout << "Constructed Tree Root: " << root7->val << endl;

    // Problem 8: Lowest Common Ancestor of a Binary Tree
    TreeNode* root8 = new TreeNode(3, new TreeNode(5, new TreeNode(6), new TreeNode(2)), new TreeNode(1));
    TreeNode* lca = lowestCommonAncestor(root8, root8->left, root8->right);
    cout << "LCA: " << lca->val << endl;

    // Problem 9: Validate Binary Search Tree
    TreeNode* root9 = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    cout << "Is Valid BST: " << (isValidBST(root9) ? "True" : "False") << endl;

    // Problem 10: Binary Tree Zigzag Level Order Traversal
    vector<vector<int>> zigzag = zigzagLevelOrder(root1);
    cout << "Zigzag Level Order: ";
    for (const auto& level : zigzag) {
        for (int val : level) cout << val << " ";
        cout << "; ";
    }
    cout << endl;

    // Problem 11: Flatten Binary Tree to Linked List
    TreeNode* root11 = new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(5, nullptr, new TreeNode(6)));
    flatten(root11);
    cout << "Flattened Tree: ";
    while (root11) { cout << root11->val << " "; root11 = root11->right; }
    cout << endl;

    // Problem 12: Diameter of Binary Tree
    TreeNode* root12 = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3));
    cout << "Diameter: " << diameterOfBinaryTree(root12) << endl;

    // Problem 13: Path Sum
    cout << "Has Path Sum: " << (hasPathSum(root12, 7) ? "True" : "False") << endl;

    // Problem 14: Path Sum II
    vector<vector<int>> paths = pathSum(root12, 7);
    cout << "Path Sum II: ";
    for (const auto& path : paths) {
        for (int val : path) cout << val << " ";
        cout << "; ";
    }
    cout << endl;

    // Problem 15: Balanced Binary Tree
    TreeNode* root15 = new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
    cout << "Is Balanced: " << (isBalanced(root15) ? "True" : "False") << endl;

    // Problem 16: Minimum Depth of Binary Tree
    cout << "Min Depth: " << minDepth(root15) << endl;

    // Problem 17: Convert Sorted Array to BST
    vector<int> nums17 = {-10, -3, 0, 5, 9};
    TreeNode* root17 = sortedArrayToBST(nums17);
    cout << "Sorted Array to BST Root: " << root17->val << endl;

    // Problem 18: Maximum Path Sum
    cout << "Max Path Sum: " << maxPathSum(root12) << endl;

    // Problem 19: Construct Binary Tree from Inorder and Postorder Traversal
    vector<int> inorder19 = {9, 3, 15, 20, 7};
    vector<int> postorder19 = {9, 15, 7, 20, 3};
    TreeNode* root19 = buildTreeFromPostIn(inorder19, postorder19);
    cout << "Constructed Tree Root (Postorder): " << root19->val << endl;

    // Problem 20: Populating Next Right Pointers in Each Node
Node* root20 = new Node(1, new Node(2, new Node(4, nullptr, nullptr, nullptr), new Node(5, nullptr, nullptr, nullptr), nullptr),
                           new Node(3, nullptr, new Node(7, nullptr, nullptr, nullptr), nullptr), nullptr);    root20 = connect(root20);
    cout << "Next Right of Root: " << (root20->next ? to_string(root20->next->val) : "None") << endl;

    // Problem 21: Populating Next Right Pointers in Each Node II
Node* root21 = new Node(1, new Node(2, new Node(4, nullptr, nullptr, nullptr), new Node(5, nullptr, nullptr, nullptr), nullptr),
                           new Node(3, nullptr, new Node(7, nullptr, nullptr, nullptr), nullptr), nullptr);    root21 = connectII(root21);
    cout << "Next Right of Node 1: " << (root21->next ? to_string(root21->next->val) : "None") << endl;

    // Problem 22: Lowest Common Ancestor of a BST
    TreeNode* root22 = new TreeNode(6, new TreeNode(2, new TreeNode(0), new TreeNode(4)), new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* lca22 = lowestCommonAncestorBST(root22, root22->left, root22->right);
    cout << "LCA in BST: " << lca22->val << endl;

    // Problem 23: Kth Smallest Element in a BST
    cout << "3rd Smallest in BST: " << kthSmallest(root22, 3) << endl;

    // Problem 24: Serialize and Deserialize Binary Tree
    Codec codec;
    TreeNode* root24 = new TreeNode(1, new TreeNode(2), new TreeNode(3, new TreeNode(4), new TreeNode(5)));
    string serialized = codec.serialize(root24);
    cout << "Serialized Tree: " << serialized << endl;
    TreeNode* deserialized = codec.deserialize(serialized);
    cout << "Deserialized Root: " << deserialized->val << endl;

    // Problem 25: BST Iterator
    BSTIterator* iterator = new BSTIterator(root22);
    cout << "BST Iterator: ";
    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;

    // Problem 26: Recover Binary Search Tree
    TreeNode* root26 = new TreeNode(3, new TreeNode(1), new TreeNode(4, new TreeNode(2), nullptr));
    recoverTree(root26);
    cout << "Recovered BST Root: " << root26->val << endl;

    // Problem 27: Validate Binary Tree Nodes
    vector<int> leftChild27 = {1, -1, 3, -1};
    vector<int> rightChild27 = {2, -1, -1, -1};
    cout << "Valid Binary Tree Nodes: " << (validateBinaryTreeNodes(4, leftChild27, rightChild27) ? "True" : "False") << endl;

    // Problem 28: Binary Tree Cameras
    TreeNode* root28 = new TreeNode(0, new TreeNode(0, new TreeNode(0), new TreeNode(0)), nullptr);
    cout << "Min Cameras: " << minCameraCover(root28) << endl;

    // Problem 29: All Nodes Distance K in Binary Tree
    TreeNode* root29 = new TreeNode(3, new TreeNode(5, new TreeNode(6), new TreeNode(2, new TreeNode(7), new TreeNode(4))), new TreeNode(1, new TreeNode(0), new TreeNode(8)));
    vector<int> distK = distanceK(root29, root29->left, 2);
    cout << "Nodes at Distance K: ";
    for (int val : distK) cout << val << " ";
    cout << endl;

    // Problem 30: Sum of Distances in Tree
    vector<vector<int>> edges30 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}};
    vector<int> sumDistances = sumOfDistancesInTree(6, edges30);
    cout << "Sum of Distances in Tree: ";
    for (int val : sumDistances) cout << val << " ";
    cout << endl;

    return 0;
}
