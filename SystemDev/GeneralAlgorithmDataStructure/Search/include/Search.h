#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>

/**
 * @brief The SearchAlgorithms class contains public interfaces for various searching algorithms
 *        including linear search, binary search, KMP string search, hash search, 
 *        and algorithms for searching in graphs and trees (DFS and BFS).
 */
class SearchAlgorithms {
public:
    /**
     * @brief Public interface for linear search on an array of integers.
     *
     * @param arr A vector of integers where the search is performed.
     * @param target The integer value to be searched.
     * @return bool True if the target is found, otherwise false.
     */
    static bool linearSearch(const std::vector<int>& arr, int target);

    /**
     * @brief Public interface for binary search on a sorted array of integers.
     *
     * @param arr A sorted vector of integers where the search is performed.
     * @param target The integer value to be searched.
     * @return bool True if the target is found, otherwise false.
     */
    static bool binarySearch(const std::vector<int>& arr, int target);

    /**
     * @brief Public interface for KMP search to find a pattern in a text.
     *
     * @param text The main text where the search is performed.
     * @param pattern The pattern string to be searched within the text.
     * @return bool True if the pattern is found in the text, otherwise false.
     */
    static bool KMP_search(const std::string& text, const std::string& pattern);

    /**
     * @brief Public interface for searching for a key in an unordered map (hash search).
     *
     * @param hashMap An unordered_map where the search is performed.
     * @param key The key to be searched within the map.
     * @return bool True if the key is found, otherwise false.
     */
    static bool hashSearch(const std::unordered_map<int, int>& hashMap, int key);

    /**
     * @brief Public interface for Depth-First Search (DFS) on a graph.
     *
     * @param graph A vector of adjacency lists representing the graph.
     * @param start The starting node for the search.
     * @param target The node to search for in the graph.
     * @return bool True if the target node is found, otherwise false.
     */
    static bool DFS(const std::vector<std::list<int>>& graph, int start, int target);

    /**
     * @brief Public interface for Breadth-First Search (BFS) on a graph.
     *
     * @param graph A vector of adjacency lists representing the graph.
     * @param start The starting node for the search.
     * @param target The node to search for in the graph.
     * @return bool True if the target node is found, otherwise false.
     */
    static bool BFS(const std::vector<std::list<int>>& graph, int start, int target);

    /**
     * @brief Defines a structure for a binary tree node.
     */
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /**
     * @brief Public interface for DFS (Pre-order traversal) on a binary tree.
     *
     * @param root The root of the binary tree.
     * @param target The target value to search for.
     * @return bool True if the target value is found, otherwise false.
     */
    static bool DFS_Tree(TreeNode* root, int target);

    /**
     * @brief Public interface for BFS (Level-order traversal) on a binary tree.
     *
     * @param root The root of the binary tree.
     * @param target The target value to search for.
     * @return bool True if the target value is found, otherwise false.
     */
    static bool BFS_Tree(TreeNode* root, int target);

private:
    /**
     * @brief Private implementation for linear search (returns index).
     *
     * @param arr A vector of integers where the search is performed.
     * @param target The integer value to be searched.
     * @return int The index of the target if found, otherwise returns -1.
     */
    static int linearSearchImpl(const std::vector<int>& arr, int target);

    /**
     * @brief Private implementation for binary search (returns index).
     *
     * @param arr A sorted vector of integers where the search is performed.
     * @param target The integer value to be searched.
     * @return int The index of the target if found, otherwise returns -1.
     */
    static int binarySearchImpl(const std::vector<int>& arr, int target);

    /**
     * @brief Builds the partial match table (prefix table) for the KMP algorithm.
     *
     * @param pattern The string pattern for which the table is built.
     * @return std::vector<int> The partial match table for the given pattern.
     */
    static std::vector<int> buildPartialMatchTable(const std::string& pattern);

    /**
     * @brief Private implementation for KMP search (returns index).
     *
     * @param text The main text where the search is performed.
     * @param pattern The pattern string to be searched within the text.
     * @return int The starting index of the first match, otherwise returns -1.
     */
    static int KMP_searchImpl(const std::string& text, const std::string& pattern);

    /**
     * @brief Private implementation for hash search without using any standard library algorithms.
     *        This function manually iterates over the unordered_map and checks for the target key.
     *
     * @param hashMap The unordered_map in which the search is performed.
     * @param key The key to search for in the unordered_map.
     * @return bool True if the key is found, otherwise false.
     */
    static bool hashSearchImpl(const std::unordered_map<int, int>& hashMap, int key);

    /**
     * @brief Private DFS implementation for graphs.
     *
     * @param graph A vector of adjacency lists representing the graph.
     * @param start The starting node for the search.
     * @param target The target node to find.
     * @return bool True if the target node is found, otherwise false.
     */
    static bool DFSImpl(const std::vector<std::list<int>>& graph, int start, int target);

    /**
     * @brief Private BFS implementation for graphs.
     *
     * @param graph A vector of adjacency lists representing the graph.
     * @param start The starting node for the search.
     * @param target The target node to find.
     * @return bool True if the target node is found, otherwise false.
     */
    static bool BFSImpl(const std::vector<std::list<int>>& graph, int start, int target);

    /**
     * @brief Private DFS implementation for binary trees (Pre-order traversal).
     *
     * @param root The root of the binary tree.
     * @param target The target value to find.
     * @return bool True if the target value is found, otherwise false.
     */
    static bool DFS_TreeImpl(TreeNode* root, int target);

    /**
     * @brief Private BFS implementation for binary trees (Level-order traversal).
     *
     * @param root The root of the binary tree.
     * @param target The target value to find.
     * @return bool True if the target value is found, otherwise false.
     */
    static bool BFS_TreeImpl(TreeNode* root, int target);
};

#endif // SEARCH_H
