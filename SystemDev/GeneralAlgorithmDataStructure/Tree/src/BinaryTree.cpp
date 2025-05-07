#include "../include/BinaryTree.h"
using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree& other) {
    root = copyTree(other.root);
}

BinaryTree::~BinaryTree() {
    destroyTree(root);
}

void BinaryTree::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

TreeNode* BinaryTree::copyTree(const TreeNode* node) {
    if (!node) return nullptr;

    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

void BinaryTree::insert(int value) {
    if (!root) {
        root = new TreeNode(value);
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = new TreeNode(value);
            break;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = new TreeNode(value);
            break;
        } else {
            q.push(current->right);
        }
    }
}

bool BinaryTree::find(int value) {
    std::cout << "Searching for value: " << value << std::endl;

    // Execute Recursive Search
    bool foundRecursive = findRecursive(root, value);
    std::cout << "Recursive Search: " << (foundRecursive ? "Found" : "Not Found") << std::endl;

    // Execute BFS Search
    bool foundBFS = findBFS(root, value);
    std::cout << "BFS Search: " << (foundBFS ? "Found" : "Not Found") << std::endl;

    // Execute DFS Search
    bool foundDFS = findDFS(root, value);
    std::cout << "DFS Search: " << (foundDFS ? "Found" : "Not Found") << std::endl;

    // Return true if any of the search methods found the value
    return foundRecursive || foundBFS || foundDFS;
}

void BinaryTree::update(int oldVal, int newVal) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->value == oldVal) {
            current->value = newVal;
            return;
        }
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

void BinaryTree::preorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    ret.push_back(node->value);
    preorder(node->left, ret);
    preorder(node->right, ret);
    return;
}

vector<int> BinaryTree::preorderIterative(TreeNode* node) {
    vector<int> ret;
    if (!node) return ret;
    stack<TreeNode* > s;
    TreeNode* cur = node;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            ret.push_back(cur->value);
            cur = cur->left;
        }
        TreeNode* top = s.top();
        s.pop();
        cur = top->right;
    }

    return ret;
}

void BinaryTree::inorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    inorder(node->left, ret);
    ret.push_back(node->value);
    inorder(node->right, ret);
    return;
}

vector<int> BinaryTree::inorderIterative(TreeNode* node) {
    vector<int> ret;
    if (node == NULL)
        return ret;
    stack<TreeNode *> s;
    TreeNode *cur = node;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        TreeNode *top = s.top();
        s.pop();
        ret.push_back(top->value);
        cur = top->right;
    }
    return ret;
}

void BinaryTree::postorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    postorder(node->left, ret);
    postorder(node->right, ret);
    ret.push_back(node->value);
    return;
}

vector<int> BinaryTree::postorderIterative(TreeNode* node) {
    vector<int> ret;
    if (!node) return ret;
    TreeNode* cur = node, *last = nullptr;
    stack<TreeNode* > s;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        TreeNode* top = s.top();
        if (!top->right || top->right == last) {
            ret.push_back(top->value);
            s.pop();
            last = top;
        }
        else cur = top->right;
    }
    return ret;
}

vector<int> BinaryTree::levelOrder(TreeNode* node) const {
    vector<int> ret;
    if (!node) return ret;

    std::queue<TreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        ret.push_back(current->value);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    return ret;
}

TreeNode* BinaryTree::getRoot() {
    return root;
}

void BinaryTree::displayPreorder() {
    vector<int> ret;
    preorder(root, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayPreorderIterative() {
    vector<int> ret = preorderIterative(root);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayInorder() {
    vector<int> ret;
    inorder(root, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayInorderIterative() {
    vector<int> ret = inorderIterative(root);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayPostorder() {
    vector<int> ret;
    postorder(root, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayPostorderIterative() {
    vector<int> ret = postorderIterative(root);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayLevelOrder() {
    vector<int> ret = levelOrder(root);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::displayPathSum(int targetSum) {
    vector<vector<int> > paths = pathSum(root, targetSum);

    cout << "[ ";

    for (size_t i = 0; i < paths.size(); ++i) {
        cout << "[ ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << paths[i][j];
            if (j != paths[i].size() - 1) {
                std::cout << ", ";
            }
        }
        cout << " ]";
        if (i != paths.size() - 1) {
            std::cout << ", ";
        }
    }

    cout << " ]\n";
}

vector<vector<int>> BinaryTree::pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> paths;
    vector<int> path;
    if (!root) return paths;
    dfsPaths(root, targetSum, path, paths);

    return paths;
}

int BinaryTree::maxDepth() {
    return maxDepth(root);
}

int BinaryTree::minDepth() {
    return minDepth(root);
}

int BinaryTree::countNodes() {
    return countNodes(root);
}

void BinaryTree::dfsPaths(TreeNode* node, int targetSum, vector<int>& path, vector<vector<int>>& paths) {
    if (!node) return;
    path.push_back(node->value);
    if (!node->left && !node->right && targetSum == node->value) {
        paths.push_back(path);
    }
    dfsPaths(node->left, targetSum - node->value, path, paths);
    dfsPaths(node->right, targetSum - node->value, path, paths);
    path.pop_back();
}

bool BinaryTree::isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (p && q && p->value == q->value) return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    return false;
}

void BinaryTree::mirrorTree(TreeNode *node) {
    if (!node) return;

    // Swap the left and right children
    std::swap(node->left, node->right);

    // Recur for the left and right subtrees
    mirrorTree(node->left);
    mirrorTree(node->right);
}

bool BinaryTree::isFullBinaryTree(TreeNode *node) {
    // Base case: An empty tree is considered a full binary tree
    if (!node) return true;

    // If the node is a leaf (has no children), it's a full binary tree
    if (!node->left && !node->right) return true;

    // If the node has both left and right children, check its subtrees
    if (node->left && node->right) {
        return isFullBinaryTree(node->left) && isFullBinaryTree(node->right);
    }

    // If the node has only one child, it's not a full binary tree
    return false;
}

bool BinaryTree::isCompleteBinaryTree(TreeNode *node, int index, int nodeCount)
{
    // An empty tree is considered a complete binary tree
    if (!node) return true;

    // If the current node's index exceeds or equals the total number of nodes, it's not complete
    if (index >= nodeCount) return false;

    // Recursively check the left and right subtrees
    return isCompleteBinaryTree(node->left, 2 * index + 1, nodeCount) &&
           isCompleteBinaryTree(node->right, 2 * index + 2, nodeCount);
}

TreeNode *BinaryTree::invertTree(TreeNode *node)
{
    if (!node) return nullptr;

    // Recursively invert left and right subtrees
    TreeNode* left = invertTree(node->left);
    TreeNode* right = invertTree(node->right);

    // Swap the left and right children
    node->left = right;
    node->right = left;

    return node;
}

bool BinaryTree::isBalanced(TreeNode* node) {
    if (!node) return true;
    int left = depth(node->left);
    int right = depth(node->right);

    return abs(left - right) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

int BinaryTree::maxDepth(TreeNode* node) {
    if (!node) return 0;
    int l = maxDepth(node->left);
    int r = maxDepth(node->right);
    return max(l+1, r+1);
}

int BinaryTree::minDepth(TreeNode* node) {
    if(!node) return 0;
    int l = minDepth(node->left), r = minDepth(node->right);
    return (min(l, r) ? min(l, r) : max(l, r)) + 1;
}

int BinaryTree::countNodes(TreeNode *node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

bool BinaryTree::isSameTree(const BinaryTree &other) {
    return isSameTree(this->root, other.root);
}

bool BinaryTree::isBalanced() {
    return isBalanced(root);
}

void BinaryTree::mirrorTree() {
    mirrorTree(root);
}

bool BinaryTree::isFullBinaryTree() {
    return isFullBinaryTree(root);
}

bool BinaryTree::isCompleteBinaryTree() {
    int nodeCount = countNodes(root);
    return isCompleteBinaryTree(root, 0, nodeCount);
}

void BinaryTree::invertTree() {
    root = invertTree(root);
}

int BinaryTree::findMinValue() {
    return findMinValue(root);
}

int BinaryTree::findMaxValue() {
    return findMaxValue(root);
}

int BinaryTree::depth(TreeNode *node) {
    if (!node) return 0;
    return max(depth(node->left), depth(node->right)) + 1;
}

bool BinaryTree::findRecursive(TreeNode *node, int value) {
    if (!node) return false;

    if (node->value == value) return true;

    return findRecursive(node->left, value) || findRecursive(node->right, value);
}

bool BinaryTree::findBFS(TreeNode* node, int value) {
    if (!node) return false;

    std::queue<TreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current->value == value) return true;

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }

    return false;
}

bool BinaryTree::findDFS(TreeNode* node, int value) {
    if (!node) return false;

    std::stack<TreeNode*> s;
    s.push(node);

    while (!s.empty()) {
        TreeNode* current = s.top();
        s.pop();

        if (current->value == value) return true;

        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }

    return false;
}

int BinaryTree::findMinValue(TreeNode *node) {
    if (!node) return INT_MAX;

    int minVal = node->value;
    int leftMin = findMinValue(node->left);
    int rightMin = findMinValue(node->right);

    return std::min(minVal, std::min(leftMin, rightMin));
}

int BinaryTree::findMaxValue(TreeNode *node) {
    if (!node) return INT_MIN;

    int maxVal = node->value;
    int leftMax = findMaxValue(node->left);
    int rightMax = findMaxValue(node->right);

    return std::max(maxVal, std::max(leftMax, rightMax));
}
