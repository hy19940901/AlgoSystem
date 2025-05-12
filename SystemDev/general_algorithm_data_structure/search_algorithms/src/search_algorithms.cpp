#include "../include/search_algorithms.h"

// Public interface for linear search
bool SearchAlgorithms::LinearSearch(const std::vector<int>& arr, int target) {
    return LinearSearchImpl(arr, target) != -1;
}

// Private implementation for linear search (returns index)
int SearchAlgorithms::LinearSearchImpl(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i; // Target found, return index
        }
    }
    return -1; // Target not found
}

// Public interface for binary search
bool SearchAlgorithms::BinarySearch(const std::vector<int>& arr, int target) {
    return BinarySearchImpl(arr, target) != -1;
}

// Private implementation for binary search (returns index)
int SearchAlgorithms::BinarySearchImpl(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Target not found
}

// Private helper for building the partial match table for KMP
std::vector<int> SearchAlgorithms::BuildPartialMatchTable(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> next(m, 0);
    int j = 0; // Length of longest matching prefix-suffix
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// Public interface for KMP search
bool SearchAlgorithms::KmpSearch(const std::string& text, const std::string& pattern) {
    return KmpSearchImpl(text, pattern) != -1;
}

// Private implementation for KMP search (returns index)
int SearchAlgorithms::KmpSearchImpl(const std::string& text, const std::string& pattern) {
    std::vector<int> next = BuildPartialMatchTable(pattern);
    int n = text.size(), m = pattern.size();
    int j = 0;

    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1; // Match found
        }
    }
    return -1; // Match not found
}

// Public interface for hash search
bool SearchAlgorithms::HashSearch(const std::unordered_map<int, int>& hashMap, int key) {
    //return hashMap.find(key) != hashMap.end();
    return HashSearchImpl(hashMap, key);
}

bool SearchAlgorithms::HashSearchImpl(const std::unordered_map<int, int>& hashMap, int key) {
    // Manually iterate over the unordered_map using iterators
    for (auto it = hashMap.begin(); it != hashMap.end(); ++it) {
        if (it->first == key) {
            return true; // Found the key
        }
    }
    return false; // Key not found
}

// Public interface for DFS on a graph
bool SearchAlgorithms::Dfs(const std::vector<std::list<int>>& graph, int start, int target) {
    return DfsImpl(graph, start, target);
}

// Private DFS implementation for graphs
bool SearchAlgorithms::DfsImpl(const std::vector<std::list<int>>& graph, int start, int target) {
    std::stack<int> stack;
    std::vector<bool> visited(graph.size(), false);
    stack.push(start);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (node == target) {
            return true; // Target found
        }

        if (!visited[node]) {
            visited[node] = true;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
    return false; // Target not found
}

// Public interface for BFS on a graph
bool SearchAlgorithms::Bfs(const std::vector<std::list<int>>& graph, int start, int target) {
    return BfsImpl(graph, start, target);
}

// Private BFS implementation for graphs
bool SearchAlgorithms::BfsImpl(const std::vector<std::list<int>>& graph, int start, int target) {
    std::queue<int> queue;
    std::vector<bool> visited(graph.size(), false);
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        if (node == target) {
            return true; // Target found
        }

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    return false; // Target not found
}

// Public interface for DFS on a binary tree
bool SearchAlgorithms::DfsTree(TreeNode* root, int target) {
    return DfsTreeImpl(root, target);
}

// Private DFS implementation for binary trees (pre-order traversal)
bool SearchAlgorithms::DfsTreeImpl(TreeNode* root, int target) {
    if (!root) return false;
    if (root->val == target) return true;

    // Search in left and right subtree
    return DfsTreeImpl(root->left, target) || DfsTreeImpl(root->right, target);
}

// Public interface for BFS on a binary tree
bool SearchAlgorithms::BfsTree(TreeNode* root, int target) {
    return BfsTreeImpl(root, target);
}

// Private BFS implementation for binary trees (level-order traversal)
bool SearchAlgorithms::BfsTreeImpl(TreeNode* root, int target) {
    if (!root) return false;
    std::queue<TreeNode*> queue;
    queue.push(root);

    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();

        if (node->val == target) {
            return true; // Target found
        }

        if (node->left) queue.push(node->left);
        if (node->right) queue.push(node->right);
    }
    return false; // Target not found
}
