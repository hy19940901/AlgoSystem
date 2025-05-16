#include "../include/search_algorithms.h"
#include <iostream>

using namespace std;

// Function to test linear search
void TestLinearSearch() {
    std::vector<int> arr = {10, 23, 45, 70, 11, 15};
    int target = 45;
    bool result = SearchAlgorithms::LinearSearch(arr, target);
    std::cout << "Linear Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test binary search
void TestBinarySearch() {
    std::vector<int> sortedArr = {10, 15, 23, 45, 70, 100};
    int target = 70;
    bool result = SearchAlgorithms::BinarySearch(sortedArr, target);
    std::cout << "Binary Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test KMP search
void TestKMP() {
    std::string text = "ABC ABCDAB ABCDABCDABDE";
    std::string pattern = "ABCDABD";
    bool result = SearchAlgorithms::KmpSearch(text, pattern);
    std::cout << "KMP Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test hash search
void TestHashSearch() {
    std::unordered_map<int, int> hashMap = {{1, 100}, {2, 200}, {3, 300}};
    bool result = SearchAlgorithms::HashSearch(hashMap, 2);
    std::cout << "Hash Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test DFS on a graph (searching for a target node)
void TestGraphDFS() {
    std::vector<std::list<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };
    int target = 5; // Set the target node to search for
    bool found = SearchAlgorithms::Dfs(graph, 0, target);
    std::cout << "DFS search for node " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test BFS on a graph (searching for a target node)
void TestGraphBFS() {
    std::vector<std::list<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };
    int target = 5; // Set the target node to search for
    bool found = SearchAlgorithms::Bfs(graph, 0, target);
    std::cout << "BFS search for node " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test DFS on a binary tree (searching for a target value)
void TestTreeDFS() {
    SearchAlgorithms::TreeNode* root = new SearchAlgorithms::TreeNode(1);
    root->left = new SearchAlgorithms::TreeNode(2);
    root->right = new SearchAlgorithms::TreeNode(3);
    root->left->left = new SearchAlgorithms::TreeNode(4);
    root->left->right = new SearchAlgorithms::TreeNode(5);

    int target = 5; // Set the target value to search for
    bool found = SearchAlgorithms::DfsTree(root, target);
    std::cout << "DFS search for value " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test BFS on a binary tree (searching for a target value)
void TestTreeBFS() {
    SearchAlgorithms::TreeNode* root = new SearchAlgorithms::TreeNode(1);
    root->left = new SearchAlgorithms::TreeNode(2);
    root->right = new SearchAlgorithms::TreeNode(3);
    root->left->left = new SearchAlgorithms::TreeNode(4);
    root->left->right = new SearchAlgorithms::TreeNode(5);

    int target = 5; // Set the target value to search for
    bool found = SearchAlgorithms::BfsTree(root, target);
    std::cout << "BFS search for value " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

int main() {
    // Test individual search algorithms
    TestLinearSearch();
    TestBinarySearch();
    TestKMP();
    TestHashSearch();
    TestGraphDFS();
    TestGraphBFS();
    TestTreeDFS();
    TestTreeBFS();

    return 0;
}