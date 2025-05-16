#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/**
 * 📚 Backtracking Technique Overview
 * ===================================
 *
 * 🧠 Description:
 * Backtracking is a systematic way of trying out different sequences of decisions until finding one
 * that "works", i.e., satisfies the problem constraints. It is typically used for combinatorial problems
 * such as generating all subsets, permutations, combinations, or solving constraint satisfaction problems
 * (e.g., N-Queens, Sudoku).
 *
 * 🔍 Example:
 * For instance, given a set [1, 2, 3], to generate all subsets you would:
 *   - Start with an empty subset []
 *   - At each step, decide whether to include the current number.
 *   - If you include a number, the "state" changes; when a branch (choice) is fully explored, the algorithm
 *     backtracks (undoes the choice) to try alternative possibilities.
 *
 * 💡 Strategy:
 * -----------
 * 1. **Define the Recursion:**
 *    - Use a helper function (e.g., backtrack) that takes the current state (often stored in a vector, e.g., `path`)
 *      and the decision point (often an index or starting parameter).
 * 2. **Base Case:**
 *    - When a valid or complete solution is found (e.g., current path satisfies the target condition),
 *      record the solution (push to result vector, `res`).
 * 3. **Recursive Case:**
 *    - Iterate over the choices available from the current decision point.
 *    - For each choice:
 *         a. **Make a Choice:** Update the current state (`path.push_back(choice)`).
 *         b. **Recurse:** Call the helper function with the updated state and new decision point.
 *         c. **Undo the Choice (Backtrack):** Remove the last element (`path.pop_back()`) to restore state.
 *
 * 4. **Pruning:**
 *    - Optionally, add conditions to skip certain choices early (e.g., if a choice makes the state invalid)
 *      to reduce the search space.
 *
 * 🚨 Edge Cases:
 * --------------
 * - **Duplicate Handling:** When input contains duplicates and unique solutions are required,
 *   sort the input and skip duplicate choices in the same recursive level.
 * - **Empty Input:** Ensure handling of edge case when the input set or sequence is empty.
 * - **Infeasible States:** Incorporate condition checks to prevent unnecessary recursion
 *   when the current state cannot lead to a valid solution.
 *
 * ⏱️ Time & Space Complexity:
 * ----------------------------
 * - **Time:** Typically exponential, O(2^n) for generating all subsets or O(n!) for permutations,
 *   depending on the problem constraints and pruning effectiveness.
 * - **Space:** O(n) for recursion call stack plus additional space for storing the current path.
 *
 * 💡 Template Example:
 * --------------------
 * vector<vector<int>> res;
 * void backtrack(vector<int>& path, int start, vector<int>& choices) {
 *     if (/* base condition: e.g., valid solution found * /) {
 *         res.push_back(path);
 *         return;
 *     }
 *     for (int i = start; i < choices.size(); ++i) {
 *         // Optionally skip duplicates: if(i > start && choices[i] == choices[i-1]) continue;
 *         path.push_back(choices[i]);       // Make a choice
 *         backtrack(path, i + 1, choices);    // Recurse with updated state
 *         path.pop_back();                    // Undo the choice (backtrack)
 *     }
 * }
 *
 * This template can be tailored to problems like generating combinations,
 * permutations, subsets, or partitioning problems.
 */

/**
 * Problem 1: Generate Parentheses (LeetCode 22)
 * ---------------------------------------------
 * 🧠 Description:
 * Given an integer `n`, return all combinations of `n` pairs of well-formed parentheses.
 * Each combination must be valid — meaning every '(' must be closed by a corresponding ')'.
 *
 * 🔍 Example:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * 💡 Strategy: Backtracking with Remaining Count
 * ---------------------------------------------
 * - Track how many left '(' and right ')' parentheses remain.
 * - You may:
 *   → Add '(' if open > 0
 *   → Add ')' if close > open (ensures balance)
 * - When both open and close are zero, a valid combination is complete.
 * - Use recursion and backtrack after trying each choice.
 *
 * 🚨 Edge Cases:
 * - n = 0 → should return [""]
 * - Only balanced and valid strings are allowed
 *
 * ⏱️ Time: O(4^n / sqrt(n)) — Catalan number growth
 * 🧠 Space: O(n) recursion depth per path
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
 * ---------------------------------
 * 🧠 Description:
 * Place `n` queens on an `n x n` chessboard such that no two queens attack each other.
 * Queens attack vertically, and diagonally in both directions.
 * Return all distinct valid board configurations.
 *
 * 🔍 Example:
 * Input: n = 4
 * Output:
 * [
 *   [".Q..","...Q","Q...","..Q."],
 *   ["..Q.","Q...","...Q",".Q.."]
 * ]
 *
 * 💡 Strategy: Backtracking Row by Row
 * -------------------------------------
 * - Place a queen in each row.
 * - For each column in the row, check if it's valid:
 *     → No other queen in same column
 *     → No other queen in upper-left or upper-right diagonals
 * - If valid, place the queen and recurse to the next row.
 * - Backtrack after each attempt to explore all board states.
 *
 * 🚨 Edge Cases:
 * - n = 2 or n = 3 → no solution exists
 *
 * ⏱️ Time: O(n!) — try n columns for each row
 * 🧠 Space: O(n^2) for board + recursion stack
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
 * -------------------------------------
 * 🧠 Description:
 * Given a list of distinct integers `nums`, return all possible permutations of the list.
 *
 * 🔍 Example:
 * Input: nums = [1, 2, 3]
 * Output:
 * [
 *   [1,2,3], [1,3,2], [2,1,3],
 *   [2,3,1], [3,1,2], [3,2,1]
 * ]
 *
 * 💡 Strategy: Backtracking with Used[] Array
 * ---------------------------------------------
 * - Maintain a `used[]` array to track which elements are in the current permutation.
 * - Recurse by choosing any unused element.
 * - When the path size reaches nums.size(), store the result.
 * - Backtrack after each choice to explore other possibilities.
 *
 * 🚨 Edge Cases:
 * - Empty input → returns [[]]
 *
 * ⏱️ Time: O(n!) — total permutations for n elements
 * 🧠 Space: O(n) recursion + used[] + path
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
 * --------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, return all possible subsets (the power set).
 * Each element may be included or excluded in a subset.
 *
 * 🔍 Example:
 * Input: nums = [1, 2, 3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * 💡 Strategy: Backtracking from Index
 * -------------------------------------
 * - At each index, you can:
 *     → Include nums[i] in the subset
 *     → Skip nums[i] and continue
 * - Push the current subset into result at every recursive level.
 * - Use index to avoid duplicates and preserve order.
 *
 * 🚨 Edge Cases:
 * - Empty array → returns [[]]
 *
 * ⏱️ Time: O(2^n) — each element has 2 choices
 * 🧠 Space: O(n) recursion stack
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
 * 🧠 Description:
 * Given a 2D board of characters and a target word, return true if the word exists in the board.
 * The word can be constructed from sequentially adjacent cells (up/down/left/right),
 * and the same cell cannot be used more than once.
 *
 * 🔍 Example:
 * Input:
 * board = [["A","B","C","E"],
 *          ["S","F","C","S"],
 *          ["A","D","E","E"]]
 * word = "ABCCED"
 * Output: true
 *
 * 💡 Strategy: Backtracking DFS on Grid
 * --------------------------------------
 * - Start DFS from every cell matching word[0].
 * - Mark visited cells temporarily to avoid reuse.
 * - Explore all 4 directions recursively.
 * - Restore the cell value (backtrack) after exploration.
 *
 * 🚨 Edge Cases:
 * - Empty board or word → return false
 * - Words longer than total board size → return false
 *
 * ⏱️ Time: O(m * n * 4^L), where L is word length
 * 🧠 Space: O(L) recursion depth
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
 * 🧠 Description:
 * Given a set of distinct integers `candidates` and a target number `target`,
 * return all unique combinations of candidates that sum to target.
 * Each number may be chosen unlimited times.
 *
 * 🔍 Example:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3], [7]]
 *
 * 💡 Strategy: Backtracking with Repeated Choice
 * ----------------------------------------------
 * - From each index, try adding the current candidate if it doesn't exceed the target.
 * - Since we can reuse a number, do not advance index after including it.
 * - When target reaches 0, store the current path.
 * - Backtrack after each choice to explore other combinations.
 *
 * 🚨 Edge Cases:
 * - No combination sums to target → return empty list
 * - Candidates must be positive (to guarantee termination)
 *
 * ⏱️ Time: Exponential in worst case (unbounded combinations)
 * 🧠 Space: O(target) recursion depth
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
 * 🧠 Description:
 * Given a string `s`, return all possible ways to partition it into substrings
 * such that every substring is a palindrome.
 *
 * 🔍 Example:
 * Input: s = "aab"
 * Output: [["a","a","b"], ["aa","b"]]
 *
 * 💡 Strategy: Backtracking with Palindrome Check
 * --------------------------------------------------
 * - From index i, try every possible substring s[i..j]
 * - If s[i..j] is a palindrome:
 *     → Add it to path and recurse on s[j+1..]
 * - Backtrack after each partition attempt.
 *
 * 🚨 Edge Cases:
 * - Empty string → returns [[]]
 * - Single character → returns [[char]]
 *
 * ⏱️ Time: O(2^n * n) — all partitions * O(n) for palindrome checking
 * 🧠 Space: O(n) recursion + output
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
 * Problem 8: Rat in a Maze (Classic)
 * ----------------------------------
 * 🧠 Description:
 * Given an `n x n` binary matrix where `1` is open and `0` is blocked,
 * find all paths from (0, 0) to (n-1, n-1) using only D, R, U, L moves.
 * You cannot visit the same cell more than once in a path.
 *
 * 🔍 Example:
 * Input:
 * maze = [[1, 0, 0, 0],
 *         [1, 1, 0, 1],
 *         [0, 1, 0, 0],
 *         [1, 1, 1, 1]]
 * Output: ["DDRDRR", "DRDDRR"]
 *
 * 💡 Strategy: DFS + Backtracking with Visited Matrix
 * ------------------------------------------------------
 * - At each cell, try all 4 directions if valid (open and unvisited).
 * - Mark cell as visited before moving, and unmark it after (backtracking).
 * - If destination is reached, add current path to result.
 *
 * 🚨 Edge Cases:
 * - maze[0][0] == 0 → no valid path
 * - All 0s → return empty result
 *
 * ⏱️ Time: O(4^(n^2)) in worst-case  
 * 🧠 Space: O(n^2) for visited matrix and recursion
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
 * 🧠 Description:
 * Given a binary tree and a target sum, return all root-to-leaf paths
 * where the sum of node values equals the target.
 *
 * 🔍 Example:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], target = 22
 * Output: [[5,4,11,2], [5,8,4,5]]
 *
 * 💡 Strategy: Backtracking on Binary Tree
 * -----------------------------------------
 * - Start DFS from root.
 * - Track current path and subtract current node from target.
 * - If it's a leaf and target becomes 0 → add path to result.
 * - Backtrack after visiting left and right subtrees.
 *
 * 🚨 Edge Cases:
 * - Tree is null → return empty list
 * - Only root node equals target → return single-node path
 *
 * ⏱️ Time: O(N^2) in worst case (skewed tree with copying path)
 * 🧠 Space: O(H) recursion, H = height of tree
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
 * Problem 10: Unique Paths III (LeetCode 980)
 * --------------------------------------------
 * 🧠 Description:
 * You are given a grid of size m x n, where:
 *   - `1` represents the starting square,
 *   - `2` represents the ending square,
 *   - `0` represents empty squares you can walk over,
 *   - `-1` represents obstacles that cannot be walked over.
 *
 * You must find all unique paths from the start to the end that visit every non-obstacle square exactly once.
 *
 * 🔍 Example:
 * Input:
 * grid = [
 *   [1, 0, 0, 0],
 *   [0, 0, 0, 0],
 *   [0, 0, 2, -1]
 * ]
 * Output: 2
 * Explanation: There are two unique paths that go from 1 to 2 and cover all zeros exactly once.
 *
 * 💡 Strategy:
 * ------------
 * - First, find the starting point and count the total number of empty squares (including the start).
 * - Use DFS/backtracking to explore all possible paths from the starting point.
 * - Mark the cell as visited by setting it to -1 (temporarily).
 * - When you reach the end cell (`2`) with exactly all empty squares visited (`remaining == 0`), count it as a valid path.
 * - Backtrack to explore other paths.
 *
 * 🚨 Edge Cases:
 * -------------
 * - Start or end not found (guaranteed valid input by constraints).
 * - All paths blocked by `-1`: result is 0.
 * - The only path is a direct 1 → 2 with no 0s in between: result is 1.
 *
 * ⏱️ Time Complexity:
 * --------------------
 * - Worst case: O(4^(m * n)) — since at most each cell tries 4 directions recursively.
 *
 * 🧠 Space Complexity:
 * ---------------------
 * - O(m * n) for recursion stack and backtracking path.
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
 * -------------------------------------------------
 * 🧠 Description:
 * You are given an integer array `matchsticks` where each element represents the length of a matchstick.
 * You must determine if you can use **all** the matchsticks to form a square.
 * You cannot break any matchstick and each matchstick must be used exactly once.
 *
 * 🔍 Example:
 * Input: matchsticks = [1, 1, 2, 2, 2]
 * Output: true
 * Explanation: You can form a square with sides [2,2,2,2]
 *
 * 💡 Strategy:
 * - If the sum of all matchsticks is not divisible by 4, it's impossible.
 * - The target side length = total sum / 4.
 * - Use backtracking to try placing each stick in one of 4 "buckets" (the 4 sides of the square).
 * - Prune early:
 *     → If current bucket exceeds side length, stop.
 *     → Sort matchsticks in descending order to fill larger sticks earlier and fail faster if impossible.
 *
 * 🚨 Edge Cases:
 * - sum % 4 ≠ 0 → immediately return false
 * - matchsticks has fewer than 4 sticks → impossible
 * - a single stick > side length → prune early
 *
 * ⏱️ Time: O(4^N) worst case (try placing N matchsticks into 4 sides)
 * 🧠 Space: O(N) recursion depth + 4-element side state
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
 * ---------------------------------------
 * 🧠 Description:
 * Given an undirected graph represented as an adjacency matrix,
 * determine whether a **Hamiltonian Path** exists — a path that visits each vertex **exactly once**.
 *
 * 🔍 Example:
 * Input: graph = [
 *   [0,1,0,1],
 *   [1,0,1,0],
 *   [0,1,0,1],
 *   [1,0,1,0]
 * ]
 * Output: true
 *
 * 💡 Strategy:
 * - Try starting DFS from each node.
 * - At each step:
 *     → For every unvisited neighbor, recurse and mark as visited.
 *     → Backtrack to try other options.
 * - If we’ve visited all vertices exactly once, a Hamiltonian Path exists.
 *
 * 🚨 Edge Cases:
 * - Disconnected graph → no valid path
 * - Fully connected graph → always has Hamiltonian Path
 *
 * ⏱️ Time: O(N!) — factorial complexity (visit every permutation)
 * 🧠 Space: O(N) recursion depth for visited array
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
 * 🧠 Description:
 * Given a string `digits` containing numbers from 2 to 9,
 * return all possible letter combinations the number could represent
 * based on the telephone keypad mapping.
 *
 * 🔍 Example:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * 💡 Strategy:
 * - Map digits to corresponding characters using a lookup table.
 * - Use backtracking to build combinations:
 *     → For each digit, try all mapped letters and recurse to next digit.
 *     → Backtrack after each letter to try other possibilities.
 *
 * 🚨 Edge Cases:
 * - Empty input → return empty list
 *
 * ⏱️ Time: O(3^N * 4^M), where N is digits mapped to 3 letters, M to 4 letters
 * 🧠 Space: O(N) recursion depth
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
 * 🧠 Description:
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * Each cell must contain a digit 1–9 such that:
 *   - Each row, column, and 3×3 box contains the digits 1–9 exactly once.
 *
 * 🔍 Example:
 * Input: A 9×9 grid with some cells filled and others as '.'
 * Output: A fully solved valid Sudoku board (modified in-place)
 *
 * 💡 Strategy:
 * - For each empty cell, try placing numbers 1–9.
 * - Before placing, validate:
 *     → Not already in the current row/column/box.
 * - Recurse to next empty cell; backtrack if invalid.
 *
 * 🚨 Edge Cases:
 * - Multiple solutions may exist — problem requires **any** valid one.
 *
 * ⏱️ Time: O(9^(81)) worst-case brute force
 * 🧠 Space: O(81) recursion stack (if all cells are empty)
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
 * -----------------------------------------
 * 🧠 Description:
 * Given a string `s` and a dictionary of words `wordDict`,
 * return all possible sentences where `s` can be segmented into valid words from the dictionary.
 *
 * 🔍 Example:
 * Input: s = "catsanddog", wordDict = ["cat", "cats", "and", "sand", "dog"]
 * Output: ["cats and dog", "cat sand dog"]
 *
 * 💡 Strategy:
 * - At each index, try every prefix that exists in the dictionary.
 * - Recurse on the remaining suffix.
 * - Use memoization to store previously computed substrings.
 *
 * 🚨 Edge Cases:
 * - s is empty → return []
 * - No valid segmentation → return []
 *
 * ⏱️ Time: O(2^N) without memoization, better with caching
 * 🧠 Space: O(N^2) for memo + recursion
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
 * -----------------------------------------------
 * 🧠 Description:
 * Given a string `s` containing only digits, return all possible valid IP address combinations.
 * An IP address must consist of exactly 4 parts separated by dots.
 * Each part must be a number between 0 and 255, with no leading zeros.
 *
 * 🔍 Example:
 * Input: s = "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 *
 * 💡 Strategy:
 * - Try every possible 1-3 digit segment.
 * - Backtrack after each segment:
 *     → Validate segment is in [0, 255] and has no leading zeros.
 * - Stop when 4 segments are built and all digits are used.
 *
 * 🚨 Edge Cases:
 * - Segment like "00" or "01" is invalid.
 * - String length too short or too long (e.g., <4 or >12) → return []
 *
 * ⏱️ Time: O(1) — bounded by fixed segment combinations (max 12 digits)
 * 🧠 Space: O(1) call stack (max depth 4)
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
 * ---------------------------------------------
 * 🧠 Description:
 * Given a list of candidates (with possible duplicates) and a target,
 * return all unique combinations where candidates sum to the target.
 * Each candidate may be used only once.
 *
 * 🔍 Example:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
 *
 * 💡 Strategy:
 * - Sort the array to group duplicates.
 * - Use backtracking:
 *     → At each level, skip duplicates (i > index && nums[i] == nums[i-1]).
 *     → Prune if current candidate > target.
 * - Only move to next index after use (to avoid reusing the same element).
 *
 * 🚨 Edge Cases:
 * - Empty input or all numbers > target → return []
 *
 * ⏱️ Time: O(2^n) — worst-case combination space
 * 🧠 Space: O(n) recursion stack
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
 * 🧠 Description:
 * Given a word, return all possible generalized abbreviations of the word.
 * You can replace any number of characters with their count (e.g., "word" → "w2d", "3d", etc).
 *
 * 🔍 Example:
 * Input: "word"
 * Output: ["word","1ord","w1rd","wo1d","wor1","2rd",...]
 *
 * 💡 Strategy:
 * - For each character, you have two choices:
 *     → Abbreviate it (increment count)
 *     → Keep it (append count if > 0, then append char)
 * - Use backtracking to explore both branches.
 *
 * 🚨 Edge Cases:
 * - Empty string → return [""]
 *
 * ⏱️ Time: O(2^n) — binary decision at each character
 * 🧠 Space: O(n) call stack
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
 * ----------------------------------------------
 * 🧠 Description:
 * Given a string `s` and an integer `k`, return the number of ways
 * to split `s` into a sequence of integers (no leading zeros),
 * where each integer is in the range [1, k].
 *
 * 🔍 Example:
 * Input: s = "1000", k = 10000
 * Output: 1
 *
 * 💡 Strategy:
 * - At each index, try extending the number as long as it's <= k.
 * - Use dynamic programming with memoization (dp[i] = #ways from i to end).
 * - Skip paths that start with '0'.
 *
 * 🚨 Edge Cases:
 * - Leading zeros (e.g., "01") are invalid.
 * - Single-digit 0 is invalid.
 *
 * ⏱️ Time: O(n * log k)
 * 🧠 Space: O(n) for memoization
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
 * -----------------------------------------------------
 * 🧠 Description:
 * Given a string `num` and a target integer, add binary operators (+, -, *) between digits
 * to form valid expressions that evaluate to the target. Return all such expressions.
 *
 * 🔍 Example:
 * Input: num = "123", target = 6
 * Output: ["1+2+3","1*2*3"]
 *
 * 💡 Strategy:
 * - Try all possible splits of the string into numbers.
 * - Track:
 *     → Current value of expression,
 *     → Last multiplied term (to correctly handle "*"),
 *     → Expression string.
 * - Use long long to prevent overflow.
 *
 * 🚨 Edge Cases:
 * - Skip numbers with leading zeros like "05".
 * - Result can be very large, prune if needed.
 *
 * ⏱️ Time: O(4^n) — 3 choices (+, -, *) per digit split
 * 🧠 Space: O(n) call stack for recursion
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
