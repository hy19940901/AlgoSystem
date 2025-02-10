#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

/**
 * Problem 1: Generate Parentheses (LC 22)
 * Description:
 * Given n pairs of parentheses, generate all combinations of well-formed parentheses.
 * Approach:
 * Use backtracking to explore all valid combinations. At each step, you can either add an open or close parenthesis,
 * ensuring the number of close parentheses never exceeds open parentheses.
 * Example:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 */
void generateParenthesisHelper(int open, int close, string current, vector<string>& result) {
    if (open == 0 && close == 0) {
        result.push_back(current);
        return;
    }
    if (open > 0) generateParenthesisHelper(open - 1, close, current + "(", result);
    if (close > open) generateParenthesisHelper(open, close - 1, current + ")", result);
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    generateParenthesisHelper(n, n, "", result);
    return result;
}

/**
* Problem 2: N-Queens (LC 51)
 * Description:
 * Place n queens on an n x n chessboard so that no two queens threaten each other.
 * Return all distinct solutions.
 * Approach:
 * Use backtracking to explore all valid configurations. For each row, try placing a queen in every column
 * and check for conflicts with previously placed queens.
 * Example:
 * Input: n = 4
 * Output: [
 *   [".Q..","...Q","Q...","..Q."],
 *   ["..Q.","Q...","...Q",".Q.."]
 * ]
 */
bool isSafe(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q') return false; // Check column
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q') return false; // Check upper-left diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q') return false; // Check upper-right diagonal
    return true;
}

void solveNQueensHelper(vector<string>& board, int row, vector<vector<string>>& result, int n) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueensHelper(board, row + 1, result, n);
            board[row][col] = '.'; // Backtrack
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    solveNQueensHelper(board, 0, result, n);
    return result;
}

/**
* Problem 3: Permutations (LC 46)
 * Description:
 * Given an array nums of distinct integers, return all possible permutations.
 * Approach:
 * Use backtracking to generate all permutations by swapping elements at each step and exploring the possibilities.
 * Example:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 */

void permuteHelper(vector<int>& nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& result) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        permuteHelper(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);

    permuteHelper(nums, used, path, result);
    return result;
}

/**
 * Problem 4: Subsets (LC 78)
 * Description:
 * Given an array of integers nums, return all possible subsets (the power set).
 * Approach:
 * Use backtracking to explore all subsets by including or excluding each element at each step.
 * Example:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 */
void subsetsHelper(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    for (int i = index; i < nums.size(); ++i) {
        current.push_back(nums[i]);
        subsetsHelper(nums, i + 1, current, result);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    subsetsHelper(nums, 0, current, result);
    return result;
}

/**
 * Problem 5: Word Search (LC 79)
 * Description:
 * Given a 2D board and a word, determine if the word exists in the grid.
 * Approach:
 * Use backtracking to search for the word starting from each cell. At each step, explore all four directions.
 * Example:
 * Input: board = [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ], word = "ABCCED"
 * Output: true
 */
bool wordSearchHelper(vector<vector<char>>& board, string& word, int index, int row, int col) {
    if (index == word.size()) return true; // Word found
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index])
        return false;

    char temp = board[row][col];
    board[row][col] = '#'; // Mark as visited
    bool found = wordSearchHelper(board, word, index + 1, row + 1, col) ||
                 wordSearchHelper(board, word, index + 1, row - 1, col) ||
                 wordSearchHelper(board, word, index + 1, row, col + 1) ||
                 wordSearchHelper(board, word, index + 1, row, col - 1);
    board[row][col] = temp; // Backtrack
    return found;
}

bool exist(vector<vector<char>>& board, string word) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            if (wordSearchHelper(board, word, 0, i, j)) return true;
        }
    }
    return false;
}

/**
 * Problem 6: Combination Sum (LC 39)
 * Description:
 * Given an array of distinct integers candidates and a target integer target, return all unique combinations of candidates where the chosen numbers sum to target.
 * Approach:
 * Use backtracking to find all combinations by adding elements and tracking remaining sum.
 *
 * Example:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 */
void combinationSumHelper(vector<int>& candidates, int target, int index, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    for (int i = index; i < candidates.size(); ++i) {
        if (candidates[i] > target) continue;
        current.push_back(candidates[i]);
        combinationSumHelper(candidates, target - candidates[i], i, current, result);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> current;
    combinationSumHelper(candidates, target, 0, current, result);
    return result;
}

/**
 * Problem 7: Palindrome Partitioning (LC 131)
 * Description:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Approach:
 * Use backtracking to explore partitions and check if substrings are palindromes.
 *
 * Example:
 * Input: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 */
bool isPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start++] != s[end--]) return false;
    }
    return true;
}

void partitionHelper(string& s, int index, vector<string>& current, vector<vector<string>>& result) {
    if (index == s.size()) {
        result.push_back(current);
        return;
    }
    for (int i = index; i < s.size(); ++i) {
        if (isPalindrome(s, index, i)) {
            current.push_back(s.substr(index, i - index + 1));
            partitionHelper(s, i + 1, current, result);
            current.pop_back(); // Backtrack
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> current;
    partitionHelper(s, 0, current, result);
    return result;
}

/**
 * Problem 8: Rat in a Maze (Custom Classic Problem)
 * Description:
 * Given a maze, find all possible paths from the top-left corner to the bottom-right corner.
 * Approach:
 * Use backtracking to explore all paths and ensure valid moves.
 *
 * Example:
 * Input: maze = [
 *   [1, 0, 0, 0],
 *   [1, 1, 0, 1],
 *   [0, 1, 0, 0],
 *   [1, 1, 1, 1]
 * ]
 * Output: Paths leading to bottom-right corner.
 */
void ratInMazeHelper(vector<vector<int>>& maze, int x, int y, vector<vector<int>>& visited, string path, vector<string>& result) {
    int n = maze.size();
    if (x == n - 1 && y == n - 1) {
        result.push_back(path);
        return;
    }

    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    string moves = "DRUL";
    for (int i = 0; i < directions.size(); ++i) {
        int nx = x + directions[i].first;
        int ny = y + directions[i].second;
        if (nx >= 0 && ny >= 0 && nx < n && ny < n && maze[nx][ny] == 1 && visited[nx][ny] == 0) {
            visited[nx][ny] = 1;
            ratInMazeHelper(maze, nx, ny, visited, path + moves[i], result);
            visited[nx][ny] = 0; // Backtrack
        }
    }
}

vector<string> findPathsInMaze(vector<vector<int>>& maze) {
    int n = maze.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    vector<string> result;
    if (maze[0][0] == 1) {
        visited[0][0] = 1;
        ratInMazeHelper(maze, 0, 0, visited, "", result);
    }
    return result;
}

/**
 * Problem 9: Path Sum II (LC 113)
 * Description:
 * Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths
 * where the sum of the node values in the path equals targetSum.
 * Approach:
 * Use backtracking to explore all root-to-leaf paths and track the remaining sum.
 *
 * Example:
 * Input:
 *        5
 *       / \
 *      4   8
 *     /   / \
 *    11  13  4
 *   /  \    / \
 *  7    2  5   1
 * targetSum = 22
 *
 * Output: [[5,4,11,2], [5,8,4,5]]
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void pathSumHelper(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& result) {
    if (!root) return; // Base case: if node is null, return

    path.push_back(root->val); // Choose: Add current node to path
    targetSum -= root->val;    // Update remaining sum

    // If it's a leaf node and sum equals targetSum, store the path
    if (!root->left && !root->right && targetSum == 0) {
        result.push_back(path);
    } else {
        // Explore left and right subtrees
        pathSumHelper(root->left, targetSum, path, result);
        pathSumHelper(root->right, targetSum, path, result);
    }

    path.pop_back(); // Backtrack: remove last node before returning
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    pathSumHelper(root, targetSum, path, result);
    return result;
}

/**
 * Problem 10: Unique Paths III (LC 980)
 * Description:
 * You are given an m x n integer array grid where 1 represents the starting square, 2 represents the ending square,
 * 0 represents empty squares, and -1 represents obstacles. Return the number of unique paths that visit every non-obstacle square exactly once.
 * Approach:
 * Use backtracking to explore all valid paths from the starting square to the ending square,
 * while ensuring all empty squares are visited exactly once.
 *
 * Example:
 * Input: grid = [
 *   [1,0,0,0],
 *   [0,0,0,0],
 *   [0,0,2,-1]
 * ]
 * Output: 2
 */
void uniquePathsIIIHelper(vector<vector<int>>& grid, int x, int y, int remaining, int& result) {
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] == -1) return;

    if (grid[x][y] == 2) {
        if (remaining == 0) result++;
        return;
    }

    grid[x][y] = -1; // Mark the cell as visited
    uniquePathsIIIHelper(grid, x + 1, y, remaining - 1, result); // Down
    uniquePathsIIIHelper(grid, x - 1, y, remaining - 1, result); // Up
    uniquePathsIIIHelper(grid, x, y + 1, remaining - 1, result); // Right
    uniquePathsIIIHelper(grid, x, y - 1, remaining - 1, result); // Left
    grid[x][y] = 0; // Backtrack
}

int uniquePathsIII(vector<vector<int>>& grid) {
    int startX = 0, startY = 0, emptyCount = 0;

    // Find the starting point and count empty squares
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 0) {
                emptyCount++;
            }
        }
    }

    int result = 0;
    uniquePathsIIIHelper(grid, startX, startY, emptyCount + 1, result);
    return result;
}

/**
 * Problem 11: Matchsticks to Square (LC 473)
 * Description:
 * Given an integer array matchsticks, return true if you can make a square using all the matchsticks.
 * Each matchstick must be used exactly one time.
 * Approach:
 * Use backtracking to assign matchsticks to one of the four sides of the square.
 *
 * Example:
 * Input: matchsticks = [1,1,2,2,2]
 * Output: true
 */
bool canFormSquare(vector<int>& sides, int index, vector<int>& matchsticks, int target) {
    if (index == matchsticks.size()) {
        return sides[0] == target && sides[1] == target && sides[2] == target && sides[3] == target;
    }

    for (int i = 0; i < 4; ++i) {
        if (sides[i] + matchsticks[index] > target) continue;

        sides[i] += matchsticks[index];
        if (canFormSquare(sides, index + 1, matchsticks, target)) return true;
        sides[i] -= matchsticks[index]; // Backtrack
    }

    return false;
}

bool makesquare(vector<int>& matchsticks) {
    int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
    if (sum % 4 != 0) return false;

    int target = sum / 4;
    vector<int> sides(4, 0);
    sort(matchsticks.rbegin(), matchsticks.rend()); // Optimization: Start with largest sticks
    return canFormSquare(sides, 0, matchsticks, target);
}

/**
 * Problem 12: Hamiltonian Path (Classic)
 * Description:
 * Given a graph represented as an adjacency matrix, check if there exists a Hamiltonian Path,
 * which visits each vertex exactly once.
 * Approach:
 * Use backtracking to try all possible paths and check if each vertex is visited exactly once.
 *
 * Example:
 * Input: graph = {
 *   {0, 1, 0, 1},
 *   {1, 0, 1, 0},
 *   {0, 1, 0, 1},
 *   {1, 0, 1, 0}
 * }
 * Output: true
 */
bool hamiltonianPathHelper(vector<vector<int>>& graph, vector<bool>& visited, int current, int visitedCount) {
    if (visitedCount == graph.size()) return true;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[current][i] == 1 && !visited[i]) {
            visited[i] = true;
            if (hamiltonianPathHelper(graph, visited, i, visitedCount + 1)) return true;
            visited[i] = false; // Backtrack
        }
    }

    return false;
}

bool hamiltonianPath(vector<vector<int>>& graph) {
    int n = graph.size();
    for (int start = 0; start < n; ++start) {
        vector<bool> visited(n, false);
        visited[start] = true;
        if (hamiltonianPathHelper(graph, visited, start, 1)) return true;
    }
    return false;
}

int main() {
    // Test Problem 1: Generate Parentheses
    cout << "Test Problem 1: Generate Parentheses (LC 22) \n";
    int n = 3;
    vector<string> parentheses = generateParenthesis(n);
    //cout << "Generate Parentheses:" << endl;
    for (const auto& p : parentheses) cout << p << endl;

    // Test Problem 2: N-Queens
    cout << "Test Problem 2: N-Queens (LC 51) \n";
    int queens = 4;
    vector<vector<string>> nQueens = solveNQueens(queens);
    //cout << "N-Queens:" << endl;
    for (const auto& solution : nQueens) {
        for (const auto& row : solution) cout << row << endl;
        cout << endl;
    }

    // Test Problem 3: Permutations
    cout << "Test Problem 3: Permutations (LC 46) \n";
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> permutations = permute(nums);
    //cout << "Permutations:" << endl;
    for (const auto& perm : permutations) {
        for (int num : perm) cout << num << " ";
        cout << endl;
    }

    // Test Problem 4: Subsets
    cout << "Test Problem 4: Subsets (LC 78) \n";
    vector<int> numsSubset = {1, 2, 3};
    vector<vector<int>> allSubsets = subsets(numsSubset);
    //cout << "Subsets:" << endl;
    for (const auto& subset : allSubsets) {
        for (int num : subset) cout << num << " ";
        cout << endl;
    }

    // Test Problem 5: Word Search
    cout << "Test Problem 5: Word Search (LC 79) \n";
    vector<vector<char>> board = {{'A', 'B', 'C', 'E'},
                                  {'S', 'F', 'C', 'S'},
                                  {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";
    cout << "Word Search: " << (exist(board, word) ? "True" : "False") << endl;

    // Test Problem 6: Combination Sum
    cout << "Test Problem 6: Combination Sum (LC 39) \n";
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> combinationResults = combinationSum(candidates, target);
    //cout << "Combination Sum:" << endl;
    for (const auto& combination : combinationResults) {
        for (int num : combination) cout << num << " ";
        cout << endl;
    }

    // Test Problem 7: Palindrome Partitioning
    cout << "Test Problem 7: Palindrome Partitioning(LC 131) \n";
    string s = "aab";
    vector<vector<string>> partitionResults = partition(s);
    //cout << "Palindrome Partitioning:" << endl;
    for (const auto& partition : partitionResults) {
        for (const string& part : partition) cout << part << " ";
        cout << endl;
    }

    // Test Problem 8: Rat in a Maze
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    vector<string> paths = findPathsInMaze(maze);
    cout << "Test Problem 8: Rat in a Maze Paths:" << endl;
    for (const auto& path : paths) {
        cout << path << endl;
    }

    // Test Problem 9: Path Sum II (LC 113)
    cout << "Test Problem 9: Path Sum II (LC 113)\n" << endl;
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);

    int targetSum = 22;
    vector<vector<int>> result = pathSum(root, targetSum);

    cout << "Paths with sum " << targetSum << ":\n";
    for (const auto& path : result) {
        cout << "[ ";
        for (int num : path) {
            cout << num << " ";
        }
        cout << "]\n";
    }

    // Test Problem 10: Unique Paths III (LC 980)
    cout << "Test Problem 10: Unique Paths III (LC 980)\n" << endl;

    vector<vector<int>> grid_10 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}
    };

    cout << "Grid:\n";
    for (const auto& row : grid_10) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }

    int result_10 = uniquePathsIII(grid_10);
    cout << "Number of unique paths: " << result_10 << " (Expected: 2)\n" << endl;

    // Test Problem 11: Matchsticks to Square (LC 473)
    cout << "Test Problem 11: Matchsticks to Square (LC 473)\n" << endl;

    vector<int> matchsticks_11 = {1, 1, 2, 2, 2};

    cout << "Matchsticks: [ ";
    for (int stick : matchsticks_11) cout << stick << " ";
    cout << "]\n";

    bool result_11 = makesquare(matchsticks_11);
    cout << "Can form square: " << (result_11 ? "true" : "false") << " (Expected: true)\n" << endl;

    // Test Problem 12: Hamiltonian Path (Classic)
    cout << "Test Problem 12: Hamiltonian Path (Classic)\n" << endl;

    vector<vector<int>> graph_12 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    cout << "Graph Adjacency Matrix:\n";
    for (const auto& row : graph_12) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }

    bool result_12 = hamiltonianPath(graph_12);
    cout << "Has Hamiltonian Path: " << (result_12 ? "true" : "false") << " (Expected: true)\n" << endl;

    return 0;
}
