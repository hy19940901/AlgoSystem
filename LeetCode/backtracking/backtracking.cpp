#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/**
 * 📚 Backtracking Overview
 * ------------------------------------------------------------
 * Backtracking is a general algorithmic technique for solving problems incrementally,
 * by trying partial solutions and then abandoning them if they do not lead to a full solution.
 * It is often used when we need to explore all possibilities (search space) and the problem
 * includes constraints that should be respected.
 *
 * 🔧 Common Scenarios:
 * - Combinatorial problems (e.g., permutations, combinations, subsets)
 * - Constraint satisfaction problems (e.g., Sudoku, N-Queens)
 * - Path-finding with constraints (e.g., Word Search, Maze solving)
 * - Decision trees with pruning (e.g., Partitioning, Palindromic partitioning)
 *
 * 🧱 Template Pattern:
 * void backtrack(parameters) {
 *     if (goal is reached) {
 *         store result;
 *         return;
 *     }
 *     for (choice in choices) {
 *         if (choice is valid) {
 *             make choice;
 *             backtrack(next state);
 *             undo choice;
 *         }
 *     }
 * }
 *
 * 📈 Time Complexity:
 * Often exponential, as it explores all paths, but can be optimized with pruning or memoization.
 */

/**
 * Problem 1: Generate Parentheses (LeetCode 22)
 * ---------------------------------------------
 * 📟 Description:
 * Given n pairs of parentheses, generate all combinations of well-formed parentheses.
 * A well-formed parentheses string is valid if every opening '(' has a corresponding ')'.
 *
 * 🔍 Example:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * Use a backtracking helper function that builds the string one character at a time:
 *   - Maintain counts of remaining open and close parentheses.
 *   - You can add '(' if open > 0.
 *   - You can add ')' if close > open (to maintain balance).
 *   - When open == 0 and close == 0, we have a complete valid string.
 *
 * This ensures we only generate valid combinations and prune invalid ones early.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(4^n / sqrt(n)) — Catalan number complexity for valid parentheses
 *   - Space: O(n) recursion stack depth
 */
void GenerateParenthesisHelper(int open, int close, string current, vector<string>& result) {
    if (open == 0 && close == 0) {
        result.push_back(current);
        return;
    }
    if (open > 0) GenerateParenthesisHelper(open - 1, close, current + "(", result);
    if (close > open) GenerateParenthesisHelper(open, close - 1, current + ")", result);
}

vector<string> GenerateParenthesis(int n) {
    vector<string> result;
    GenerateParenthesisHelper(n, n, "", result);
    return result;
}

/**
 * Problem 2: N-Queens (LeetCode 51)
 * ----------------------------------
 * 📟 Description:
 * Place n queens on an n x n chessboard such that no two queens attack each other.
 * Queens attack vertically, and diagonally in both directions.
 * Return all distinct board configurations.
 *
 * 🔍 Example:
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."], ["..Q.","Q...","...Q",".Q.."]]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - Place a queen row by row.
 * - For each column in the current row, check if placing a queen is safe:
 *     - No queen in the same column above
 *     - No queen in upper-left and upper-right diagonals
 * - If valid, place the queen and continue to next row.
 * - Backtrack when invalid or when solution is recorded.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(n!) — Try n positions for each of n rows
 *   - Space: O(n^2) for storing board + recursion stack
 */
bool IsSafe(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q') return false; // Check column
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q') return false; // Check upper-left diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q') return false; // Check upper-right diagonal
    return true;
}

void SolveNQueensHelper(vector<string>& board, int row, vector<vector<string>>& result, int n) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (IsSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            SolveNQueensHelper(board, row + 1, result, n);
            board[row][col] = '.'; // Backtrack
        }
    }
}

vector<vector<string>> SolveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    SolveNQueensHelper(board, 0, result, n);
    return result;
}

/**
 * Problem 3: Permutations (LeetCode 46)
 * --------------------------------------
 * 📟 Description:
 * Given an array of distinct integers nums, return all possible permutations.
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * 💡 Approach: Backtracking with Usage Tracking
 * ------------------------------------------------------
 * - Maintain a boolean array `used[]` to track elements already in the current path.
 * - At each level, try adding any unused number to the current permutation.
 * - Once a permutation of size n is built, add it to result.
 * - Backtrack by removing last element and marking it unused.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(n!) for n elements
 *   - Space: O(n) for current path + used[]
 */

void PermuteHelper(vector<int>& nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& result) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        PermuteHelper(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> Permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);

    PermuteHelper(nums, used, path, result);
    return result;
}

/**
 * Problem 4: Subsets (LeetCode 78)
 * ---------------------------------
 * 📟 Description:
 * Given an integer array nums, return all possible subsets (the power set).
 * Each element may be either included or excluded.
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - Use DFS from index i to explore subsets.
 * - At each index, choose to include or exclude current element.
 * - Push the current subset into result at each recursive level.
 * - Backtrack after exploring each branch.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(2^n) — number of subsets
 *   - Space: O(n) recursion depth
 */
void SubsetsHelper(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    for (size_t i = index; i < nums.size(); ++i) {
        current.push_back(nums[i]);
        SubsetsHelper(nums, i + 1, current, result);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> Subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    SubsetsHelper(nums, 0, current, result);
    return result;
}

/**
 * Problem 5: Word Search (LeetCode 79)
 * -------------------------------------
 * 📟 Description:
 * Given a 2D board and a word, return true if the word exists in the grid.
 * The word can be constructed from adjacent cells (up/down/left/right), and each cell must be used only once.
 *
 * 🔍 Example:
 * Input:
 * board = [["A","B","C","E"], ["S","F","C","S"], ["A","D","E","E"]], word = "ABCCED"
 * Output: true
 *
 * 💡 Approach: Backtracking DFS
 * --------------------------------------
 * - Traverse each cell in the board.
 * - Start DFS if board[i][j] == word[0].
 * - Mark visited cells temporarily.
 * - Explore all 4 directions.
 * - Backtrack and restore cell state.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(m * n * 4^L), where L is length of the word
 *   - Space: O(L), recursion depth
 */
bool WordSearchHelper(vector<vector<char>>& board, string& word, int index, int row, int col) {
    if (static_cast<size_t>(index) == word.size()) return true; // Word found
    if (row < 0 || static_cast<size_t>(row) >= board.size() || col < 0 || static_cast<size_t>(col) >= board[0].size() || board[row][col] != word[index])
        return false;

    char temp = board[row][col];
    board[row][col] = '#'; // Mark as visited
    bool found = WordSearchHelper(board, word, index + 1, row + 1, col) ||
                 WordSearchHelper(board, word, index + 1, row - 1, col) ||
                 WordSearchHelper(board, word, index + 1, row, col + 1) ||
                 WordSearchHelper(board, word, index + 1, row, col - 1);
    board[row][col] = temp; // Backtrack
    return found;
}

bool Exist(vector<vector<char>>& board, string word) {
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            if (WordSearchHelper(board, word, 0, i, j)) return true;
        }
    }
    return false;
}

/**
 * Problem 6: Combination Sum (LeetCode 39)
 * ----------------------------------------
 * 📟 Description:
 * Given a set of distinct integers candidates and a target, return all unique combinations
 * in candidates where the chosen numbers sum to target. The same number may be chosen multiple times.
 *
 * 🔍 Example:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - For each index, decide to take the current candidate (can reuse same index).
 * - Subtract it from target and recurse.
 * - Backtrack after each recursion.
 * - Skip candidates that would overshoot the target.
 *
 * 📅 Time and Space Complexity:
 *   - Time: Exponential in worst-case
 *   - Space: O(target) recursion depth
 */
void CombinationSumHelper(vector<int>& candidates, int target, int index, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    for (size_t i = index; i < candidates.size(); ++i) {
        if (candidates[i] > target) continue;
        current.push_back(candidates[i]);
        CombinationSumHelper(candidates, target - candidates[i], i, current, result);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> CombinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> current;
    CombinationSumHelper(candidates, target, 0, current, result);
    return result;
}

/**
 * Problem 7: Palindrome Partitioning (LeetCode 131)
 * --------------------------------------------------
 * 📟 Description:
 * Given a string s, partition it such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning.
 *
 * 🔍 Example:
 * Input: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 *
 * 💡 Approach: Backtracking + Palindrome Checking
 * ---------------------------------------------------------
 * - Use DFS to try each possible cut.
 * - At each cut, check if substring is palindrome.
 * - If so, recurse and try further partitioning.
 * - Backtrack after each attempt.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(2^n * n) — all partitions * substring checks
 *   - Space: O(n) recursion depth
 */
bool IsPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start++] != s[end--]) return false;
    }
    return true;
}

void PartitionHelper(string& s, int index, vector<string>& current, vector<vector<string>>& result) {
    if (static_cast<size_t>(index) == s.size()) {
        result.push_back(current);
        return;
    }
    for (size_t i = index; i < s.size(); ++i) {
        if (IsPalindrome(s, index, i)) {
            current.push_back(s.substr(index, i - index + 1));
            PartitionHelper(s, i + 1, current, result);
            current.pop_back(); // Backtrack
        }
    }
}

vector<vector<string>> Partition(string s) {
    vector<vector<string>> result;
    vector<string> current;
    PartitionHelper(s, 0, current, result);
    return result;
}

/**
 * Problem 8: Rat in a Maze (Classic Problem)
 * ------------------------------------------
 * 📟 Description:
 * Given an n x n binary matrix representing a maze, find all paths from top-left (0,0) to bottom-right (n-1,n-1)
 * using only right/down/left/up moves. Cells with value 1 are open; 0 are blocked.
 *
 * 🔍 Example:
 * Input:
 * maze = [
 *   [1, 0, 0, 0],
 *   [1, 1, 0, 1],
 *   [0, 1, 0, 0],
 *   [1, 1, 1, 1]
 * ]
 * Output: ["DDRDRR", "DRDDRR"]
 *
 * 💡 Approach: Backtracking + Visited Matrix
 * ---------------------------------------------------
 * - From current cell, try all 4 directions.
 * - If valid and not visited, mark and recurse.
 * - Backtrack after trying each path.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(4^(n^2)) worst-case
 *   - Space: O(n^2) for visited
 */
void RatInMazeHelper(vector<vector<int>>& maze, int x, int y, vector<vector<int>>& visited, string path, vector<string>& result) {
    int n = maze.size();
    if (x == n - 1 && y == n - 1) {
        result.push_back(path);
        return;
    }

    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    string moves = "DRUL";
    for (size_t i = 0; i < directions.size(); ++i) {
        int nx = x + directions[i].first;
        int ny = y + directions[i].second;
        if (nx >= 0 && ny >= 0 && nx < n && ny < n && maze[nx][ny] == 1 && visited[nx][ny] == 0) {
            visited[nx][ny] = 1;
            RatInMazeHelper(maze, nx, ny, visited, path + moves[i], result);
            visited[nx][ny] = 0; // Backtrack
        }
    }
}

vector<string> FindPathsInMaze(vector<vector<int>>& maze) {
    int n = maze.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    vector<string> result;
    if (maze[0][0] == 1) {
        visited[0][0] = 1;
        RatInMazeHelper(maze, 0, 0, visited, "", result);
    }
    return result;
}

/**
 * Problem 9: Path Sum II (LeetCode 113)
 * --------------------------------------
 * 📟 Description:
 * Given a binary tree and targetSum, return all root-to-leaf paths where each path's sum equals targetSum.
 *
 * 🔍 Example:
 * Input: Tree with values [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - Traverse from root to leaves.
 * - At each node, subtract node->val from remaining sum.
 * - If it's a leaf and sum is 0, add current path to result.
 * - Backtrack after traversing children.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(N^2) in worst case (unbalanced tree)
 *   - Space: O(H), height of tree
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void PathSumHelper(TreeNode* root, int target_sum, vector<int>& path, vector<vector<int>>& result) {
    if (!root) return; // Base case: if node is null, return

    path.push_back(root->val); // Choose: Add current node to path
    target_sum -= root->val;    // Update remaining sum

    // If it's a leaf node and sum equals target_sum, store the path
    if (!root->left && !root->right && target_sum == 0) {
        result.push_back(path);
    } else {
        // Explore left and right subtrees
        PathSumHelper(root->left, target_sum, path, result);
        PathSumHelper(root->right, target_sum, path, result);
    }

    path.pop_back(); // Backtrack: remove last node before returning
}

vector<vector<int>> PathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    PathSumHelper(root, targetSum, path, result);
    return result;
}

/**
 * Problem 10: Triangle Minimum Path Sum (LeetCode 120)
 * -----------------------------------------------------
 * 📟 Description:
 * You are given a triangle array where triangle[i] represents the i-th row of the triangle.
 * Your goal is to find the minimum path sum from the top to the bottom.
 *
 * At each step, you may move to adjacent numbers on the row below:
 * If you're at triangle[i][j], you may move to triangle[i+1][j] or triangle[i+1][j+1].
 *
 * 🔍 Example:
 * Input:
 * triangle = [
 *     [2],
 *    [3,4],
 *   [6,5,7],
 *  [4,1,8,3]
 * ]
 * The triangle looks like:
 *     2
 *    3 4
 *   6 5 7
 *  4 1 8 3
 * Output: 11
 * Explanation: The minimum path sum is 2 + 3 + 5 + 1 = 11
 *
 * 💡 Approach: Bottom-Up Dynamic Programming (Space Optimized)
 * ------------------------------------------------------------
 * We define a 1D DP array:
 *   - dp[j] represents the minimum path sum from row i+1, column j down to the bottom.
 *
 * Step-by-step:
 *   1. Initialize dp[] as the last row of the triangle (since it's the base).
 *   2. Iterate from the second-to-last row upward.
 *   3. For each element triangle[i][j], compute:
 *        dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];
 *      (either go straight down or diagonally down-right)
 *   4. After reaching the top row, dp[0] holds the final result.
 *
 * 👮️‍⚖️ Time and Space Complexity:
 *   - Time: O(n^2), where n is the number of rows in the triangle
 *   - Space: O(n), reusing a single array for DP
 *
 * ✅ Why Bottom-Up is Better:
 *   - Avoids recursion overhead
 *   - Eliminates redundant subproblem computation
 *   - Can be optimized to O(n) space
 */
void UniquePathsIIIHelper(vector<vector<int>>& grid, int x, int y, int remaining, int& result) {
    if (x < 0 || y < 0 || static_cast<size_t>(x) >= grid.size() || static_cast<size_t>(y) >= grid[0].size() || grid[x][y] == -1) return;

    if (grid[x][y] == 2) {
        if (remaining == 0) result++;
        return;
    }

    grid[x][y] = -1; // Mark the cell as visited
    UniquePathsIIIHelper(grid, x + 1, y, remaining - 1, result); // Down
    UniquePathsIIIHelper(grid, x - 1, y, remaining - 1, result); // Up
    UniquePathsIIIHelper(grid, x, y + 1, remaining - 1, result); // Right
    UniquePathsIIIHelper(grid, x, y - 1, remaining - 1, result); // Left
    grid[x][y] = 0; // Backtrack
}

int UniquePathsIII(vector<vector<int>>& grid) {
    int start_x = 0, start_y = 0, empty_count = 0;

    // Find the starting point and count empty squares
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 0) {
                empty_count++;
            }
        }
    }

    int result = 0;
    UniquePathsIIIHelper(grid, start_x, start_y, empty_count + 1, result);
    return result;
}

/**
 * Problem 11: Matchsticks to Square (LeetCode 473)
 * -----------------------------------------------
 * 📟 Description:
 * Given an array of matchsticks, determine if they can form a square.
 * You must use all matchsticks and each matchstick must be used exactly once.
 *
 * 🔍 Example:
 * Input: matchsticks = [1,1,2,2,2]
 * Output: true
 * Explanation: Can form a square with sides of length 2.
 *
 * 💡 Approach: Backtracking + Pruning
 * ------------------------------------------------
 * - First, check if sum of matchsticks is divisible by 4.
 * - Try assigning each matchstick to one of 4 sides.
 * - Prune if side exceeds target length.
 * - Sort in descending order to optimize early pruning.
 *
 * 📅 Time and Space Complexity:
 *   - Time: Exponential in number of matchsticks
 *   - Space: O(n) recursion depth
 */
bool CanFormSquare(vector<int>& sides, int index, vector<int>& matchsticks, int target) {
    if (static_cast<size_t>(index) == matchsticks.size()) {
        return sides[0] == target && sides[1] == target && sides[2] == target && sides[3] == target;
    }

    for (int i = 0; i < 4; ++i) {
        if (sides[i] + matchsticks[index] > target) continue;

        sides[i] += matchsticks[index];
        if (CanFormSquare(sides, index + 1, matchsticks, target)) return true;
        sides[i] -= matchsticks[index]; // Backtrack
    }

    return false;
}

bool Makesquare(vector<int>& matchsticks) {
    int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
    if (sum % 4 != 0) return false;

    int target = sum / 4;
    vector<int> sides(4, 0);
    sort(matchsticks.rbegin(), matchsticks.rend()); // Optimization: Start with largest sticks
    return CanFormSquare(sides, 0, matchsticks, target);
}

/**
 * Problem 12: Hamiltonian Path (Classic)
 * --------------------------------------
 * 📟 Description:
 * Given a graph as an adjacency matrix, determine whether a Hamiltonian Path exists.
 * A Hamiltonian Path visits each vertex exactly once.
 *
 * 🔍 Example:
 * Input: graph = [[0,1,0,1], [1,0,1,0], [0,1,0,1], [1,0,1,0]]
 * Output: true
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - Try starting from each vertex.
 * - For each move, check if the next vertex is connected and unvisited.
 * - Recurse until all vertices are visited.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(n!) in worst-case
 *   - Space: O(n) recursion stack
 */
bool HamiltonianPathHelper(vector<vector<int>>& graph, vector<bool>& visited, int current, int visited_count) {
    if (static_cast<size_t>(visited_count) == graph.size()) return true;

    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[current][i] == 1 && !visited[i]) {
            visited[i] = true;
            if (HamiltonianPathHelper(graph, visited, i, visited_count + 1)) return true;
            visited[i] = false; // Backtrack
        }
    }

    return false;
}

bool HamiltonianPath(vector<vector<int>>& graph) {
    int n = graph.size();
    for (int start = 0; start < n; ++start) {
        vector<bool> visited(n, false);
        visited[start] = true;
        if (HamiltonianPathHelper(graph, visited, start, 1)) return true;
    }
    return false;
}

/**
 * Problem 13: Letter Combinations of a Phone Number (LeetCode 17)
 * ----------------------------------------------------------------
 * 📟 Description:
 * Given a string of digits from 2 to 9, return all possible letter combinations based on the phone keypad.
 *
 * 🔍 Example:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * 💡 Approach: Backtracking with Mapping
 * ------------------------------------------------
 * - Map digits to corresponding letters.
 * - For each digit, try every possible character.
 * - Recursively build the string and backtrack.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(3^n * 4^m), where n is count of digits mapped to 3 letters, m to 4 letters
 *   - Space: O(n) recursion depth
 */
vector<string> LetterCombinationsHelper(const string& digits, int index, const vector<string>& mapping, string& current, vector<string>& result) {
    if (static_cast<size_t>(index) == digits.size()) {
        result.push_back(current);
        return result;
    }
    for (char c : mapping[digits[index] - '2']) {
        current.push_back(c);
        LetterCombinationsHelper(digits, index + 1, mapping, current, result);
        current.pop_back();  // Backtrack
    }
    return result;
}

vector<string> LetterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> mapping = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result;
    string current;
    return LetterCombinationsHelper(digits, 0, mapping, current, result);
}

/**
 * Problem 14: Sudoku Solver (LeetCode 37)
 * ----------------------------------------
 * 📟 Description:
 * Solve a given 9x9 Sudoku puzzle by filling the empty cells.
 * Each digit 1-9 must appear once per row, column, and 3x3 box.
 *
 * 🔍 Example:
 * Input: A partially filled board
 * Output: Solved board in-place
 *
 * 💡 Approach: Backtracking with Constraint Checking
 * -----------------------------------------------------------
 * - Try placing digits 1 to 9 in each empty cell.
 * - For each placement, check if it's valid.
 * - If valid, recurse. If not, backtrack.
 * - Backtrack when no valid number can be placed.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(9^(n*n)) in worst-case
 *   - Space: O(n^2) board state
 */
bool IsValid(vector<vector<char>>& board, int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num || 
            board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) return false;
    }
    return true;
}

bool SolveSudokuHelper(vector<vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (IsValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (SolveSudokuHelper(board)) return true;
                        board[row][col] = '.';  // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void SolveSudoku(vector<vector<char>>& board) {
    SolveSudokuHelper(board);
}

/**
 * Problem 15: Word Break II (LeetCode 140)
 * ----------------------------------------
 * 📟 Description:
 * Given a string s and a dictionary of words, return all sentences that can be formed by breaking s into valid words.
 *
 * 🔍 Example:
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 * 💡 Approach: Backtracking + Memoization
 * ------------------------------------------------
 * - For each prefix of the string, check if it's in the dictionary.
 * - If so, recurse on the remaining suffix.
 * - Cache intermediate results to avoid recomputation.
 *
 * 📅 Time and Space Complexity:
 *   - Time: Exponential without memo, reduced with caching
 *   - Space: O(n^2) in memo and recursion
 */
unordered_map<string, vector<string>> memo;

vector<string> WordBreakHelper(const string& s, unordered_set<string>& word_dict) {
    if (memo.count(s)) return memo[s];
    vector<string> result;
    if (word_dict.count(s)) result.push_back(s);
    for (size_t i = 1; i < s.size(); i++) {
        string prefix = s.substr(0, i), suffix = s.substr(i);
        if (word_dict.count(prefix)) {
            vector<string> suffix_results = WordBreakHelper(suffix, word_dict);
            for (const string& sr : suffix_results) result.push_back(prefix + " " + sr);
        }
    }
    return memo[s] = result;
}

vector<string> WordBreak(string s, vector<string>& word_dict) {
    unordered_set<string> word_set(word_dict.begin(), word_dict.end());
    return WordBreakHelper(s, word_set);
}

/**
 * Problem 16: Restore IP Addresses (LeetCode 93)
 * ---------------------------------------------
 * 📟 Description:
 * Given a string of digits, return all possible valid IP address combinations.
 * Each segment must be between 0 and 255, and cannot have leading zeros.
 *
 * 🔍 Example:
 * Input: s = "25525511135"
 * Output: ["255.255.11.135","255.255.111.35"]
 *
 * 💡 Approach: Backtracking
 * ----------------------------------
 * - Try every possible split into 4 parts.
 * - For each part, validate length and value range.
 * - If valid, recurse into next segment.
 * - Stop when 4 parts are found and string is consumed.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(1), constant bounded by 4 segments and up to 3 digits each
 *   - Space: O(1) call stack (max depth 4)
 */
void RestoreIPHelper(string& s, int start, int part, string current, vector<string>& result) {
    if (part == 4 && static_cast<size_t>(start) == s.size()) {
        result.push_back(current.substr(0, current.size() - 1)); // Remove last dot
        return;
    }
    if (part == 4 || static_cast<size_t>(start) == s.size()) return;

    for (int len = 1; len <= 3; len++) {
        if (static_cast<size_t>(start + len) > s.size()) return;
        string segment = s.substr(start, len);
        if ((segment.size() > 1 && segment[0] == '0') || stoi(segment) > 255) return;
        RestoreIPHelper(s, start + len, part + 1, current + segment + ".", result);
    }
}

vector<string> RestoreIpAddresses(string s) {
    vector<string> result;
    RestoreIPHelper(s, 0, 0, "", result);
    return result;
}

/**
 * Problem 17: Combination Sum II (LeetCode 40)
 * --------------------------------------------
 * 📟 Description:
 * Given a collection of candidates (with duplicates) and a target, return all unique combinations
 * where candidates sum to the target. Each number may be used only once.
 *
 * 🔍 Example:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
 *
 * 💡 Approach: Backtracking + Sorting + Skip Duplicates
 * --------------------------------------------------------------
 * - Sort the array to bring duplicates together.
 * - At each level, skip duplicates (i > index && nums[i] == nums[i-1]).
 * - Only use each number once in the current path.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(2^n) worst-case combinations
 *   - Space: O(n) recursion depth
 */
void CombinationSum2Helper(vector<int>& candidates, int target, int index, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    for (int i = index; i < (int)candidates.size(); ++i) {
        if (i > index && candidates[i] == candidates[i - 1]) continue;
        if (candidates[i] > target) break;
        current.push_back(candidates[i]);
        CombinationSum2Helper(candidates, target - candidates[i], i + 1, current, result);
        current.pop_back();
    }
}

vector<vector<int>> CombinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> current;
    CombinationSum2Helper(candidates, target, 0, current, result);
    return result;
}

/**
 * Problem 18: Generate Abbreviations (LeetCode 320)
 * --------------------------------------------------
 * 📟 Description:
 * Given a word, return all generalized abbreviations of the word.
 *
 * 🔍 Example:
 * Input: "word"
 * Output: ["word","1ord","w1rd","wo1d","wor1","2rd",...]
 *
 * 💡 Approach: Backtracking + Count Abbreviated Chars
 * -------------------------------------------------------------
 * - At each character, either keep it or abbreviate (count and skip).
 * - Pass along the abbreviation count and append it when switching to letters.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(2^n), each character has 2 choices
 *   - Space: O(n) call stack
 */
void AbbreviationHelper(string& word, int pos, string current, int count, vector<string>& result) {
    if (pos == (int)word.size()) {
        if (count > 0) current += to_string(count);
        result.push_back(current);
        return;
    }
    AbbreviationHelper(word, pos + 1, current, count + 1, result);
    if (count > 0) current += to_string(count);
    AbbreviationHelper(word, pos + 1, current + word[pos], 0, result);
}

vector<string> GenerateAbbreviations(string word) {
    vector<string> result;
    AbbreviationHelper(word, 0, "", 0, result);
    return result;
}

/**
 * Problem 19: Restore The Array (LeetCode 1416)
 * ---------------------------------------------
 * 📟 Description:
 * Given a string s containing digits and an integer k, return the number of ways to split s into a list
 * of integers where each integer is in the range [1, k] and no integer has leading zeros.
 *
 * 🔍 Example:
 * Input: s = "1000", k = 10000
 * Output: 1
 *
 * 💡 Approach: Backtracking with Memoization
 * ----------------------------------------------------
 * - Try all possible prefixes starting at index i.
 * - If valid and ≤ k, recurse on suffix.
 * - Use dp[i] to memoize number of ways from i to end.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(n * log k)
 *   - Space: O(n) memo
 */
const int MOD = 1e9 + 7;

int RestoreHelper(const string& s, int k, int start, vector<int>& dp) {
    if ((size_t)start == s.size()) return 1;
    if (s[start] == '0') return 0;
    if (dp[start] != -1) return dp[start];

    long num = 0;
    int ways = 0;
    for (int i = start; i < (int)s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
        if (num > k) break;
        ways = (ways + RestoreHelper(s, k, i + 1, dp)) % MOD;
    }
    return dp[start] = ways;
}

int NumberOfArrays(string s, int k) {
    vector<int> dp(s.size(), -1);
    return RestoreHelper(s, k, 0, dp);
}

/**
 * Problem 20: Expression Add Operators (LeetCode 282)
 * ----------------------------------------------------
 * 📟 Description:
 * Given a string num and an integer target, add operators '+', '-', or '*' between digits
 * so that the resulting expression evaluates to the target.
 *
 * 🔍 Example:
 * Input: num = "123", target = 6
 * Output: ["1+2+3","1*2*3"]
 *
 * 💡 Approach: Backtracking with Expression Evaluation
 * -------------------------------------------------------------
 * - At each index, try all splits.
 * - Keep track of cumulative value and last multiplied term (for '*').
 * - Use long long to avoid overflow and prevent leading zeros.
 *
 * 📅 Time and Space Complexity:
 *   - Time: O(4^n), trying +, -, *, or skip at each digit
 *   - Space: O(n) stack + result storage
 */
void AddOperatorsHelper(string& num, int index, long long value, long long prev, string expr, int target, vector<string>& result) {
    if ((size_t)index == num.size()) {
        if (value == target) result.push_back(expr);
        return;
    }
    for (int i = index; i < (int)num.size(); ++i) {
        if (i != index && num[index] == '0') break; // skip leading 0
        string part = num.substr(index, i - index + 1);
        long long curr = stoll(part);
        if (index == 0) {
            AddOperatorsHelper(num, i + 1, curr, curr, part, target, result);
        } else {
            AddOperatorsHelper(num, i + 1, value + curr, curr, expr + "+" + part, target, result);
            AddOperatorsHelper(num, i + 1, value - curr, -curr, expr + "-" + part, target, result);
            AddOperatorsHelper(num, i + 1, value - prev + prev * curr, prev * curr, expr + "*" + part, target, result);
        }
    }
}

vector<string> AddOperators(string num, int target) {
    vector<string> result;
    AddOperatorsHelper(num, 0, 0, 0, "", target, result);
    return result;
}

int main() {
    // Test Problem 1: Generate Parentheses
    cout << "Test Problem 1: Generate Parentheses (LC 22) \n";
    int n = 3;
    vector<string> parentheses = GenerateParenthesis(n);
    //cout << "Generate Parentheses:" << endl;
    for (const auto& p : parentheses) cout << p << endl;

    // Test Problem 2: N-Queens
    cout << "Test Problem 2: N-Queens (LC 51) \n";
    int queens = 4;
    vector<vector<string>> nQueens = SolveNQueens(queens);
    //cout << "N-Queens:" << endl;
    for (const auto& solution : nQueens) {
        for (const auto& row : solution) cout << row << endl;
        cout << endl;
    }

    // Test Problem 3: Permutations
    cout << "Test Problem 3: Permutations (LC 46) \n";
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> permutations = Permute(nums);
    //cout << "Permutations:" << endl;
    for (const auto& perm : permutations) {
        for (int num : perm) cout << num << " ";
        cout << endl;
    }

    // Test Problem 4: Subsets
    cout << "Test Problem 4: Subsets (LC 78) \n";
    vector<int> numsSubset = {1, 2, 3};
    vector<vector<int>> allSubsets = Subsets(numsSubset);
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
    cout << "Word Search: " << (Exist(board, word) ? "True" : "False") << endl;

    // Test Problem 6: Combination Sum
    cout << "Test Problem 6: Combination Sum (LC 39) \n";
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> combinationResults = CombinationSum(candidates, target);
    //cout << "Combination Sum:" << endl;
    for (const auto& combination : combinationResults) {
        for (int num : combination) cout << num << " ";
        cout << endl;
    }

    // Test Problem 7: Palindrome Partitioning
    cout << "Test Problem 7: Palindrome Partitioning(LC 131) \n";
    string s = "aab";
    vector<vector<string>> partition_results = Partition(s);
    //cout << "Palindrome Partitioning:" << endl;
    for (const auto& partition : partition_results) {
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
    vector<string> paths = FindPathsInMaze(maze);
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
    vector<vector<int>> result = PathSum(root, targetSum);

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

    int result_10 = UniquePathsIII(grid_10);
    cout << "Number of unique paths: " << result_10 << " (Expected: 2)\n" << endl;

    // Test Problem 11: Matchsticks to Square (LC 473)
    cout << "Test Problem 11: Matchsticks to Square (LC 473)\n" << endl;

    vector<int> matchsticks_11 = {1, 1, 2, 2, 2};

    cout << "Matchsticks: [ ";
    for (int stick : matchsticks_11) cout << stick << " ";
    cout << "]\n";

    bool result_11 = Makesquare(matchsticks_11);
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

    bool result_12 = HamiltonianPath(graph_12);
    cout << "Has Hamiltonian Path: " << (result_12 ? "true" : "false") << " (Expected: true)\n" << endl;

    // Test Problem 13: Letter Combinations of a Phone Number
    cout << "Test Problem 13: Letter Combinations (LC 17)\n";
    vector<string> letters = LetterCombinations("23");
    for (const string& str : letters) cout << str << " ";
    cout << endl;

    // Test Problem 14: Sudoku Solver
    cout << "Test Problem 14: Sudoku Solver (LC 37)\n";
    vector<vector<char>> board_14 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    SolveSudoku(board_14);
    for (const auto& row : board_14) {
        for (char num : row) cout << num << " ";
        cout << endl;
    }

    // Test Problem 15: Word Break II
    cout << "Test Problem 15: Word Break II (LC 140)\n";
    vector<string> word_dict = {"cat", "cats", "and", "sand", "dog"};
    vector<string> sentences = WordBreak("catsanddog", word_dict);
    for (const string& sentence : sentences) cout << sentence << endl;

    // Test Problem 16: Restore IP Addresses
    cout << "Test Problem 16: Restore IP Addresses (LC 93)\n";
    vector<string> ips = RestoreIpAddresses("25525511135");
    for (const string& ip : ips) cout << ip << endl;

    // Problem 17: Combination Sum II
    cout << "Problem 17: Combination Sum II" << endl;
    vector<int> candidates_17 = {10, 1, 2, 7, 6, 1, 5};
    int target_17 = 8;
    vector<vector<int>> results_17 = CombinationSum2(candidates_17, target_17);
    for (const auto& combo : results_17) {
        for (int num : combo) cout << num << " ";
        cout << endl;
    }
    cout << endl;

    // Problem 18: Generate Abbreviations
    cout << "Problem 18: Generate Abbreviations" << endl;
    string word_18 = "word";
    vector<string> abbreviations = GenerateAbbreviations(word_18);
    for (const string& abbr : abbreviations) cout << abbr << " ";
    cout << endl << endl;

    // Problem 19: Restore The Array
    cout << "Problem 19: Restore The Array" << endl;
    string s_19 = "1000";
    int k_19 = 10000;
    cout << "Number of ways: " << NumberOfArrays(s_19, k_19) << endl;
    cout << endl;

    // Problem 20: Expression Add Operators
    cout << "Problem 20: Expression Add Operators" << endl;
    string num_20 = "123";
    int target_20 = 6;
    vector<string> expressions_20 = AddOperators(num_20, target_20);
    for (const string& expr : expressions_20) cout << expr << endl;

    return 0;
}
