#include "../include/binary_tree.hpp"
using namespace std;

namespace binary_tree {

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root_(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree& other) {
    root_ = CopyTree(other.root_);
}

BinaryTree::~BinaryTree() {
    DestroyTree(root_);
}

void BinaryTree::DestroyTree(TreeNode* node) {
    if (node) {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}

TreeNode* BinaryTree::CopyTree(const TreeNode* node) {
    if (!node) return nullptr;

    TreeNode* new_node = new TreeNode(node->value);
    new_node->left = CopyTree(node->left);
    new_node->right = CopyTree(node->right);

    return new_node;
}

void BinaryTree::Insert(int value) {
    if (!root_) {
        root_ = new TreeNode(value);
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root_);

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

bool BinaryTree::Find(int value) {
    std::cout << "Searching for value: " << value << std::endl;

    // Execute Recursive Search
    bool found_recursive = FindRecursive(root_, value);
    std::cout << "Recursive Search: " << (found_recursive ? "Found" : "Not Found") << std::endl;

    // Execute BFS Search
    bool found_bfs = FindBFS(root_, value);
    std::cout << "BFS Search: " << (found_bfs ? "Found" : "Not Found") << std::endl;

    // Execute DFS Search
    bool found_dfs = FindDFS(root_, value);
    std::cout << "DFS Search: " << (found_dfs ? "Found" : "Not Found") << std::endl;

    // Return true if any of the search methods found the value
    return found_recursive || found_bfs || found_dfs;
}

void BinaryTree::Update(int old_val, int new_val) {
    if (!root_) return;

    std::queue<TreeNode*> q;
    q.push(root_);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->value == old_val) {
            current->value = new_val;
            return;
        }
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

void BinaryTree::Preorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    ret.push_back(node->value);
    Preorder(node->left, ret);
    Preorder(node->right, ret);
    return;
}

vector<int> BinaryTree::PreorderIterative(TreeNode* node) {
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

void BinaryTree::Inorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    Inorder(node->left, ret);
    ret.push_back(node->value);
    Inorder(node->right, ret);
    return;
}

vector<int> BinaryTree::InorderIterative(TreeNode* node) {
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

void BinaryTree::Postorder(TreeNode* node, vector<int>& ret) {
    if (!node) return;
    Postorder(node->left, ret);
    Postorder(node->right, ret);
    ret.push_back(node->value);
    return;
}

vector<int> BinaryTree::PostorderIterative(TreeNode* node) {
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

vector<int> BinaryTree::LevelOrder(TreeNode* node) const {
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

TreeNode* BinaryTree::GetRoot() {
    return root_;
}

void BinaryTree::SetRootNode(TreeNode* node) {
    root_ = node;
}

void BinaryTree::DisplayPreorder() {
    vector<int> ret;
    Preorder(root_, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayPreorderIterative() {
    vector<int> ret = PreorderIterative(root_);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayInorder() {
    vector<int> ret;
    Inorder(root_, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayInorderIterative() {
    vector<int> ret = InorderIterative(root_);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayPostorder() {
    vector<int> ret;
    Postorder(root_, ret);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayPostorderIterative() {
    vector<int> ret = PostorderIterative(root_);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayLevelOrder() {
    vector<int> ret = LevelOrder(root_);
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;
}

void BinaryTree::DisplayPathSum(int target_sum) {
    vector<vector<int> > paths = PathSum(root_, target_sum);

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

vector<vector<int>> BinaryTree::PathSum(TreeNode* root, int target_sum) {
    vector<vector<int>> paths;
    vector<int> path;
    if (!root) return paths;
    DfsPaths(root, target_sum, path, paths);

    return paths;
}

int BinaryTree::MaxDepth() {
    return MaxDepth(root_);
}

int BinaryTree::MinDepth() {
    return MinDepth(root_);
}

int BinaryTree::CountNodes() {
    return CountNodes(root_);
}

void BinaryTree::DfsPaths(TreeNode* node, int target_sum, vector<int>& path, vector<vector<int>>& paths) {
    if (!node) return;
    path.push_back(node->value);
    if (!node->left && !node->right && target_sum == node->value) {
        paths.push_back(path);
    }
    DfsPaths(node->left, target_sum - node->value, path, paths);
    DfsPaths(node->right, target_sum - node->value, path, paths);
    path.pop_back();
}

bool BinaryTree::IsSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (p && q && p->value == q->value) return IsSameTree(p->left, q->left) && IsSameTree(p->right, q->right);
    return false;
}

void BinaryTree::MirrorTree(TreeNode *node) {
    if (!node) return;

    // Swap the left and right children
    std::swap(node->left, node->right);

    // Recur for the left and right subtrees
    MirrorTree(node->left);
    MirrorTree(node->right);
}

bool BinaryTree::IsFullBinaryTree(TreeNode *node) {
    // Base case: An empty tree is considered a full binary tree
    if (!node) return true;

    // If the node is a leaf (has no children), it's a full binary tree
    if (!node->left && !node->right) return true;

    // If the node has both left and right children, check its subtrees
    if (node->left && node->right) {
        return IsFullBinaryTree(node->left) && IsFullBinaryTree(node->right);
    }

    // If the node has only one child, it's not a full binary tree
    return false;
}

bool BinaryTree::IsCompleteBinaryTree(TreeNode *node, int index, int node_count)
{
    // An empty tree is considered a complete binary tree
    if (!node) return true;

    // If the current node's index exceeds or equals the total number of nodes, it's not complete
    if (index >= node_count) return false;

    // Recursively check the left and right subtrees
    return IsCompleteBinaryTree(node->left, 2 * index + 1, node_count) &&
           IsCompleteBinaryTree(node->right, 2 * index + 2, node_count);
}

TreeNode *BinaryTree::InvertTree(TreeNode *node)
{
    if (!node) return nullptr;

    // Recursively invert left and right subtrees
    TreeNode* left = InvertTree(node->left);
    TreeNode* right = InvertTree(node->right);

    // Swap the left and right children
    node->left = right;
    node->right = left;

    return node;
}

bool BinaryTree::IsBalanced(TreeNode* node) {
    if (!node) return true;
    int left = Depth(node->left);
    int right = Depth(node->right);

    return abs(left - right) <= 1 && IsBalanced(node->left) && IsBalanced(node->right);
}

int BinaryTree::MaxDepth(TreeNode* node) {
    if (!node) return 0;
    int l = MaxDepth(node->left);
    int r = MaxDepth(node->right);
    return max(l+1, r+1);
}

int BinaryTree::MinDepth(TreeNode* node) {
    if(!node) return 0;
    int l = MinDepth(node->left), r = MinDepth(node->right);
    return (min(l, r) ? min(l, r) : max(l, r)) + 1;
}

int BinaryTree::CountNodes(TreeNode *node) {
    if (!node) return 0;
    return 1 + CountNodes(node->left) + CountNodes(node->right);
}

bool BinaryTree::IsSameTree(const BinaryTree &other) {
    return IsSameTree(this->root_, other.root_);
}

bool BinaryTree::IsBalanced() {
    return IsBalanced(root_);
}

void BinaryTree::MirrorTree() {
    MirrorTree(root_);
}

bool BinaryTree::IsFullBinaryTree() {
    return IsFullBinaryTree(root_);
}

bool BinaryTree::IsCompleteBinaryTree() {
    int node_count = CountNodes(root_);
    return IsCompleteBinaryTree(root_, 0, node_count);
}

void BinaryTree::InvertTree() {
    root_ = InvertTree(root_);
}

int BinaryTree::FindMinValue() {
    return FindMinValue(root_);
}

int BinaryTree::FindMaxValue() {
    return FindMaxValue(root_);
}

int BinaryTree::Depth(TreeNode *node) {
    if (!node) return 0;
    return max(Depth(node->left), Depth(node->right)) + 1;
}

bool BinaryTree::FindRecursive(TreeNode *node, int value) {
    if (!node) return false;

    if (node->value == value) return true;

    return FindRecursive(node->left, value) || FindRecursive(node->right, value);
}

bool BinaryTree::FindBFS(TreeNode* node, int value) {
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

bool BinaryTree::FindDFS(TreeNode* node, int value) {
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

int BinaryTree::FindMinValue(TreeNode *node) {
    if (!node) return INT_MAX;

    int min_val = node->value;
    int left_min = FindMinValue(node->left);
    int right_min = FindMinValue(node->right);

    return std::min(min_val, std::min(left_min, right_min));
}

int BinaryTree::FindMaxValue(TreeNode *node) {
    if (!node) return INT_MIN;

    int max_val = node->value;
    int left_max = FindMaxValue(node->left);
    int right_max = FindMaxValue(node->right);

    return std::max(max_val, std::max(left_max, right_max));
}

// ==================== BinarySearchTree Implementation ==================== //

BinarySearchTree::BinarySearchTree() : BinaryTree() {}

void BinarySearchTree::Insert(int value) {
    SetRootNode(InsertBST(GetRoot(), value));
}

TreeNode* BinarySearchTree::InsertBST(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->value) {
        node->left = InsertBST(node->left, value);
    } else if (value > node->value) {
        node->right = InsertBST(node->right, value);
    }
    return node;
}

void BinarySearchTree::Update(int old_val, int new_val) {
    // In BST, update is typically a combination of removal and insertion
    SetRootNode(RemoveBST(GetRoot(), old_val));
    Insert(new_val);
}

TreeNode* BinarySearchTree::RemoveBST(TreeNode* node, int value) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = RemoveBST(node->left, value);
    } else if (value > node->value) {
        node->right = RemoveBST(node->right, value);
    } else {
        if (!node->left) {
            TreeNode* right_child = node->right;
            delete node;
            return right_child;
        }
        if (!node->right) {
            TreeNode* left_child = node->left;
            delete node;
            return left_child;
        }
        TreeNode* min_node = GetMin(node->right);
        node->value = min_node->value;
        node->right = RemoveBST(node->right, min_node->value);
    }
    return node;
}

TreeNode* BinarySearchTree::GetMin(TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

}