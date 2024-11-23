#include "../include/Search.h"
#include <iostream>

using namespace std;

// Function to test linear search
void testLinearSearch() {
    std::vector<int> arr = {10, 23, 45, 70, 11, 15};
    int target = 45;
    bool result = SearchAlgorithms::linearSearch(arr, target);
    std::cout << "Linear Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test binary search
void testBinarySearch() {
    std::vector<int> sortedArr = {10, 15, 23, 45, 70, 100};
    int target = 70;
    bool result = SearchAlgorithms::binarySearch(sortedArr, target);
    std::cout << "Binary Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test KMP search
void testKMP() {
    std::string text = "ABC ABCDAB ABCDABCDABDE";
    std::string pattern = "ABCDABD";
    bool result = SearchAlgorithms::KMP_search(text, pattern);
    std::cout << "KMP Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test hash search
void testHashSearch() {
    std::unordered_map<int, int> hashMap = {{1, 100}, {2, 200}, {3, 300}};
    bool result = SearchAlgorithms::hashSearch(hashMap, 2);
    std::cout << "Hash Search result: " << (result ? "Found" : "Not Found") << std::endl;
}

// Function to test DFS on a graph (searching for a target node)
void testGraphDFS() {
    std::vector<std::list<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };
    int target = 5; // Set the target node to search for
    bool found = SearchAlgorithms::DFS(graph, 0, target);
    std::cout << "DFS search for node " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test BFS on a graph (searching for a target node)
void testGraphBFS() {
    std::vector<std::list<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };
    int target = 5; // Set the target node to search for
    bool found = SearchAlgorithms::BFS(graph, 0, target);
    std::cout << "BFS search for node " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test DFS on a binary tree (searching for a target value)
void testTreeDFS() {
    SearchAlgorithms::TreeNode* root = new SearchAlgorithms::TreeNode(1);
    root->left = new SearchAlgorithms::TreeNode(2);
    root->right = new SearchAlgorithms::TreeNode(3);
    root->left->left = new SearchAlgorithms::TreeNode(4);
    root->left->right = new SearchAlgorithms::TreeNode(5);

    int target = 5; // Set the target value to search for
    bool found = SearchAlgorithms::DFS_Tree(root, target);
    std::cout << "DFS search for value " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

// Function to test BFS on a binary tree (searching for a target value)
void testTreeBFS() {
    SearchAlgorithms::TreeNode* root = new SearchAlgorithms::TreeNode(1);
    root->left = new SearchAlgorithms::TreeNode(2);
    root->right = new SearchAlgorithms::TreeNode(3);
    root->left->left = new SearchAlgorithms::TreeNode(4);
    root->left->right = new SearchAlgorithms::TreeNode(5);

    int target = 5; // Set the target value to search for
    bool found = SearchAlgorithms::BFS_Tree(root, target);
    std::cout << "BFS search for value " << target << ": " << (found ? "Found" : "Not Found") << std::endl;
}

int main() {
    // Test individual search algorithms
    testLinearSearch();
    testBinarySearch();
    testKMP();
    testHashSearch();
    testGraphDFS();
    testGraphBFS();
    testTreeDFS();
    testTreeBFS();

    return 0;
}