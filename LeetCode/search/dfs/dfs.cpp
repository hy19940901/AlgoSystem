#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

/**
 * 📚 DFS (Depth-First Search) Technique Overview
 * ==============================================
 *
 * DFS is a core recursive technique used to explore state spaces in depth-first order.
 * Depending on the data structure and problem domain, DFS is commonly categorized into:
 * - 🌐 Graph DFS: node-based with arbitrary connectivity
 * - 🧱 Grid DFS: 2D matrix traversal with direction vectors
 * - 🌲 Tree DFS: implicit DFS via binary/N-ary tree recursion
 *
 * =====================================================================
 * 🌐 1. Graph DFS
 * =====================================================================
 * 🧠 Description:
 * Used for traversing nodes and edges in a graph, detecting cycles, finding components,
 * performing topological sort, and Tarjan-style algorithms.
 *
 * 💡 Strategy:
 * - Use a `visited` array or color-state to track visited nodes.
 * - For directed graphs, track recursion stack for cycle detection.
 * - For disconnected graphs, DFS each unvisited node to discover all components.
 *
 * ⏱️ Complexity:
 * - Time: O(V + E) where V = #vertices, E = #edges
 * - Space: O(V) for visited + O(V) recursion stack
 *
 * 🚨 Edge Cases:
 * - Cycles in directed/undirected graphs
 * - Self-loops and parallel edges
 * - Disconnected components
 *
 * 🔁 Template:
 * void dfs(int u, const vector<vector<int>>& graph, vector<bool>& visited) {
 *     visited[u] = true;
 *     for (int v : graph[u]) {
 *         if (!visited[v]) {
 *             dfs(v, graph, visited);
 *         }
 *     }
 * }
 *
 * =====================================================================
 * 🧱 2. Grid DFS (Matrix-based DFS)
 * =====================================================================
 * 🧠 Description:
 * Applied to 2D grids such as mazes, islands, and image-like problems.
 * Often used to explore all connected cells with value 1 (or 'O', etc.).
 *
 * 💡 Strategy:
 * - Recursively explore in 4 (or 8) directions using dx/dy vectors.
 * - Use visited matrix or mark cells directly (e.g., grid[i][j] = -1).
 * - Prune invalid cells (out-of-bounds, visited, or wrong value).
 *
 * ⏱️ Complexity:
 * - Time: O(m * n)
 * - Space: O(m * n) visited + recursion stack
 *
 * 🚨 Edge Cases:
 * - Border conditions (i < 0, j < 0, etc.)
 * - Visited flags vs. in-place marking
 *
 * 🔁 Template:
 * void dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
 *     if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] == 0) return;
 *     visited[i][j] = true;
 *     for (auto [dx, dy] : directions)
 *         dfs(i + dx, j + dy, grid, visited);
 * }
 *
 * =====================================================================
 * 🌲 3. Tree DFS (Recursive Binary/N-ary)
 * =====================================================================
 * 🧠 Description:
 * DFS is naturally applied to trees via recursion, used for:
 * - Path sums
 * - Subtree queries
 * - Traversals (pre/in/post-order)
 * - Backtracking on decision trees
 *
 * 💡 Strategy:
 * - Traverse recursively from the root
 * - Carry contextual information (path, sum, depth, etc.)
 * - No need for visited array (tree has no cycles)
 *
 * ⏱️ Complexity:
 * - Time: O(n) where n = #nodes
 * - Space: O(h) recursion depth, h = height of tree
 *
 * 🚨 Edge Cases:
 * - Null root
 * - Leaf-only conditions
 * - Depth-based limits
 *
 * 🔁 Template:
 * void dfs(TreeNode* node, vector<int>& path) {
 *     if (!node) return;
 *     path.push_back(node->val);
 *     if (!node->left && !node->right) {
 *         res.push_back(path);  // leaf path
 *     }
 *     dfs(node->left, path);
 *     dfs(node->right, path);
 *     path.pop_back();
 * }
 *
 * =====================================================================
 * 🔚 Summary:
 * - DFS is essential for solving problems in trees, grids, and graphs.
 * - Understanding the variant (graph/grid/tree) helps choose the right strategy.
 * - Extensions include memoization, coloring, cycle detection, and backtracking.
 */

/**
 * Problem 1: Number of Islands (LeetCode 200)
 * -------------------------------------------
 * 🧠 Description:
 * Given a 2D grid of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are surrounded by water.
 *
 * 🔍 Example:
 * Input:
 * grid = [
 *   ["1","1","1","1","0"],
 *   ["1","1","0","1","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","0","0","0"]
 * ]
 * Output: 1
 *
 * 💡 Strategy:
 * Use DFS to visit each land cell. For every unvisited '1', start a DFS to sink all
 * connected '1's (mark them as '0') and count the number of DFS initiations.
 *
 * ✨ Explanation:
 * Each DFS will "sink" an entire island — turning every connected '1' to '0'.
 * Thus, each DFS call from a '1' represents a new island. The total number of such
 * calls gives the number of islands.
 *
 * 🔁 Transition:
 * - Outer loop scans grid.
 * - If cell is '1', call DfsIsland(grid, row, col), and increment island count.
 * - Inside DfsIsland: recursively explore 4-connected neighbors and sink them.
 *
 * 🚨 Edge Cases:
 * - Grid is empty → return 0
 * - All cells are water → return 0
 * - One big connected island → return 1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsIsland(vector<vector<char>>& grid, int row, int col) {
    if (row < 0 || col < 0 || static_cast<size_t>(row) >= grid.size() || static_cast<size_t>(col) >= grid[0].size() || grid[row][col] != '1') return;
    grid[row][col] = '0';
    DfsIsland(grid, row + 1, col);
    DfsIsland(grid, row - 1, col);
    DfsIsland(grid, row, col + 1);
    DfsIsland(grid, row, col - 1);
}

int NumIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col] == '1') {
                DfsIsland(grid, row, col);
                ++count;
            }
        }
    }
    return count;
}

/**
 * Problem 2: Max Area of Island (LeetCode 695)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a 2D grid of 0's and 1's, return the area of the largest island.
 * An island is a group of 1's connected 4-directionally (horizontal or vertical).
 * Return the maximum area of any island in the grid.
 *
 * 🔍 Example:
 * Input:
 * grid = [
 *   [0,0,1,0,0],
 *   [0,1,1,1,0],
 *   [0,0,1,0,0],
 *   [1,1,0,0,0]
 * ]
 * Output: 5
 *
 * 💡 Strategy:
 * Use DFS to explore the area of each island. Count each visited cell as part of the area.
 *
 * ✨ Explanation:
 * Perform DFS from every unvisited 1. Recursively count all adjacent 1's as part of the island.
 * Track the max area seen so far.
 *
 * 🔁 Transition:
 * - Outer loop scans the grid.
 * - If grid[row][col] == 1 → call DfsArea(grid, row, col) to compute area.
 * - Update max_area accordingly.
 *
 * 🚨 Edge Cases:
 * - All water (0) → return 0
 * - One single cell island → return 1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int DfsArea(vector<vector<int>>& grid, int row, int col) {
    if (row < 0 || col < 0 || static_cast<size_t>(row) >= grid.size() || static_cast<size_t>(col) >= grid[0].size() || grid[row][col] != 1) return 0;
    grid[row][col] = 0;
    return 1 + DfsArea(grid, row + 1, col) + DfsArea(grid, row - 1, col) +
               DfsArea(grid, row, col + 1) + DfsArea(grid, row, col - 1);
}

int MaxAreaOfIsland(vector<vector<int>>& grid) {
    int max_area = 0;
    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col] == 1) {
                max_area = max(max_area, DfsArea(grid, row, col));
            }
        }
    }
    return max_area;
}

/**
 * Problem 3: Flood Fill (LeetCode 733)
 * -------------------------------------
 * 🧠 Description:
 * Given an image represented by a 2D array of integers, a starting pixel (sr, sc),
 * and a new color, fill the entire connected component containing (sr, sc) with the new color.
 *
 * 🔍 Example:
 * Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
 * Output: [[2,2,2],[2,2,0],[2,0,1]]
 *
 * 💡 Strategy:
 * Use DFS to spread from the starting pixel, recoloring any connected pixel with the same original color.
 *
 * ✨ Explanation:
 * Recursively update all 4-directionally connected pixels that match the starting color.
 * Prevent revisiting by early exit if color has already changed.
 *
 * 🔁 Transition:
 * - Start from (sr, sc), record original_color.
 * - Call DfsFill(image, row, col, new_color, original_color) recursively.
 * - Return the modified image.
 *
 * 🚨 Edge Cases:
 * - newColor == original color → no changes needed
 * - Entire image is same color → recolor all
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsFill(vector<vector<int>>& image, int row, int col, int new_color, int original_color) {
    if (row < 0 || col < 0 || static_cast<size_t>(row) >= image.size() || static_cast<size_t>(col) >= image[0].size()) return;
    if (image[row][col] != original_color || image[row][col] == new_color) return;
    image[row][col] = new_color;
    DfsFill(image, row + 1, col, new_color, original_color);
    DfsFill(image, row - 1, col, new_color, original_color);
    DfsFill(image, row, col + 1, new_color, original_color);
    DfsFill(image, row, col - 1, new_color, original_color);
}

vector<vector<int>> FloodFill(vector<vector<int>>& image, int sr, int sc, int new_color) {
    int original_color = image[sr][sc];
    if (original_color != new_color)
        DfsFill(image, sr, sc, new_color, original_color);
    return image;
}

/**
 * Problem 4: Surrounded Regions (LeetCode 130)
 * ---------------------------------------------
 * 🧠 Description:
 * Given an m x n board containing 'X' and 'O', capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 *
 * 🔍 Example:
 * Input:
 * board = [
 *   ['X','X','X','X'],
 *   ['X','O','O','X'],
 *   ['X','X','O','X'],
 *   ['X','O','X','X']
 * ]
 * Output:
 * board = [
 *   ['X','X','X','X'],
 *   ['X','X','X','X'],
 *   ['X','X','X','X'],
 *   ['X','O','X','X']
 * ]
 *
 * 💡 Strategy:
 * Use DFS from all border 'O's to mark safe regions as 'E'.
 * Then flip the remaining 'O's to 'X', and 'E' back to 'O'.
 *
 * ✨ Explanation:
 * Border-connected 'O's should not be captured. DFS marks them temporarily.
 * Then iterate the grid and flip enclosed 'O's to 'X'.
 *
 * 🔁 Transition:
 * - For each border cell == 'O', call DfsMarkEscape()
 * - After marking, flip all remaining 'O' to 'X', and 'E' back to 'O'.
 *
 * 🚨 Edge Cases:
 * - Empty grid
 * - No 'O's at all
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsMarkEscape(vector<vector<char>>& board, int row, int col) {
    if (row < 0 || col < 0 || static_cast<size_t>(row) >= board.size() || static_cast<size_t>(col) >= board[0].size()) return;
    if (board[row][col] != 'O') return;
    board[row][col] = 'E';
    DfsMarkEscape(board, row + 1, col);
    DfsMarkEscape(board, row - 1, col);
    DfsMarkEscape(board, row, col + 1);
    DfsMarkEscape(board, row, col - 1);
}

void SolveSurroundedRegions(vector<vector<char>>& board) {
    if (board.empty() || board[0].empty()) return;
    int m = board.size(), n = board[0].size();

    for (int i = 0; i < m; ++i) {
        if (board[i][0] == 'O') DfsMarkEscape(board, i, 0);
        if (board[i][n - 1] == 'O') DfsMarkEscape(board, i, n - 1);
    }
    for (int j = 0; j < n; ++j) {
        if (board[0][j] == 'O') DfsMarkEscape(board, 0, j);
        if (board[m - 1][j] == 'O') DfsMarkEscape(board, m - 1, j);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'E') board[i][j] = 'O';
        }
    }
}

/**
 * Problem 5: Pacific Atlantic Water Flow (LeetCode 417)
 * ------------------------------------------------------
 * 🧠 Description:
 * Given an m x n matrix of non-negative integers representing the height of each cell,
 * return a list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.
 * The Pacific touches the left and top edges, and the Atlantic touches the right and bottom edges.
 * Water can only flow from a cell to another with height equal or lower.
 *
 * 🔍 Example:
 * Input: heights = [
 *   [1,2,2,3,5],
 *   [3,2,3,4,4],
 *   [2,4,5,3,1],
 *   [6,7,1,4,5],
 *   [5,1,1,2,4]
 * ]
 * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
 *
 * 💡 Strategy:
 * Reverse the flow: for each ocean, perform DFS from the edges inward.
 * Use two boolean grids to track reachability from Pacific and Atlantic.
 * The intersection of the two gives valid results.
 *
 * ✨ Explanation:
 * Water can flow to ocean if there's a path to edge without increasing height.
 * By reversing the direction (start from ocean), we only walk uphill or flat.
 *
 * 🔁 Transition:
 * - DFS from all border cells of Pacific and Atlantic.
 * - Mark cells reachable from each ocean.
 * - Output all cells where both visited matrices are true.
 *
 * 🚨 Edge Cases:
 * - Grid is empty → return {}
 * - All heights same → all cells valid
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsWater(const vector<vector<int>>& heights, int row, int col, vector<vector<bool>>& visited) {
    int m = heights.size(), n = heights[0].size();
    visited[row][col] = true;
    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (auto [dx, dy] : directions) {
        int new_row = row + dx;
        int new_col = col + dy;
        if (new_row >= 0 && new_row < m && new_col >= 0 && new_col < n &&
            !visited[new_row][new_col] && heights[new_row][new_col] >= heights[row][col]) {
            DfsWater(heights, new_row, new_col, visited);
        }
    }
}

vector<vector<int>> PacificAtlantic(vector<vector<int>>& heights) {
    vector<vector<int>> result;
    if (heights.empty() || heights[0].empty()) return result;
    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        DfsWater(heights, i, 0, pacific);           // left edge
        DfsWater(heights, i, n - 1, atlantic);      // right edge
    }
    for (int j = 0; j < n; ++j) {
        DfsWater(heights, 0, j, pacific);           // top edge
        DfsWater(heights, m - 1, j, atlantic);      // bottom edge
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j])
                result.push_back({i, j});
        }
    }
    return result;
}

/**
 * Problem 6: Count Sub Islands (LeetCode 1905)
 * ---------------------------------------------
 * 🧠 Description:
 * Given two m x n binary matrices grid1 and grid2 containing only 0's and 1's,
 * return the number of islands in grid2 that are sub-islands of islands in grid1.
 *
 * 🔍 Example:
 * grid1 = [[1,1,1,0],[0,1,1,1],[0,0,0,1]]
 * grid2 = [[1,1,1,0],[0,0,1,1],[0,1,0,1]]
 * Output: 2
 *
 * 💡 Strategy:
 * Traverse each island in grid2. For each cell, if it's not 1 in grid1, the island is invalid.
 *
 * ✨ Explanation:
 * Use DFS to sink every island in grid2. If all cells match with grid1 during traversal, it's valid.
 *
 * 🔁 Transition:
 * - For each cell (i,j) == 1 in grid2 → dfs
 * - In DFS, check if grid1[i][j] == 1
 * - Track "is_sub" with bitwise AND across recursive calls
 *
 * 🚨 Edge Cases:
 * - grid2 contains no land → return 0
 * - All islands in grid2 not overlapping with grid1 → return 0
 * - grid1 and grid2 are identical → all islands are sub-islands
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
bool DfsSubIsland(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int row, int col) {
    int m = grid2.size(), n = grid2[0].size();
    if (row < 0 || col < 0 || row >= m || col >= n || grid2[row][col] != 1)
        return true;

    grid2[row][col] = 0;
    bool is_sub = grid1[row][col] == 1;
    is_sub &= DfsSubIsland(grid1, grid2, row + 1, col);
    is_sub &= DfsSubIsland(grid1, grid2, row - 1, col);
    is_sub &= DfsSubIsland(grid1, grid2, row, col + 1);
    is_sub &= DfsSubIsland(grid1, grid2, row, col - 1);
    return is_sub;
}

int CountSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int count = 0;
    for (size_t i = 0; i < grid2.size(); ++i) {
        for (size_t j = 0; j < grid2[0].size(); ++j) {
            if (grid2[i][j] == 1 && DfsSubIsland(grid1, grid2, static_cast<int>(i), static_cast<int>(j))) {
                ++count;
            }
        }
    }
    return count;
}

/**
 * Problem 7: Word Search (LeetCode 79)
 * -------------------------------------
 * 🧠 Description:
 * Given a 2D board and a word, return true if the word exists in the grid.
 * The word can be constructed from adjacent cells (horizontally/vertically),
 * and the same letter cell may not be used more than once.
 *
 * 🔍 Example:
 * board = [["A","B","C","E"],
 *          ["S","F","C","S"],
 *          ["A","D","E","E"]],
 * word = "ABCCED"
 * Output: true
 *
 * 💡 Strategy:
 * Start DFS from each cell. Explore 4 directions, mark visited with '#' temporarily.
 *
 * ✨ Explanation:
 * Perform DFS from each board[i][j] if it matches word[0].
 * Backtrack after each path attempt.
 *
 * 🔁 Transition:
 * - Try every cell as starting point.
 * - Use helper function with (row, col, index) state.
 *
 * 🚨 Edge Cases:
 * - Empty board → false
 * - Empty word → true
 * - Word longer than total board cells → false
 *
 * ⏱ Time: O(m * n * 4^L), 🧠 Space: O(L) recursion depth, where L = word.length()
 */
bool DfsWordSearch(vector<vector<char>>& board, const string& word, int row, int col, int index) {
    if (static_cast<size_t>(index) == word.length()) return true;
    if (row < 0 || col < 0 || static_cast<size_t>(row) >= board.size() || static_cast<size_t>(col) >= board[0].size() || board[row][col] != word[index])
        return false;

    char temp = board[row][col];
    board[row][col] = '#';  // mark visited
    bool found = DfsWordSearch(board, word, row + 1, col, index + 1) ||
                 DfsWordSearch(board, word, row - 1, col, index + 1) ||
                 DfsWordSearch(board, word, row, col + 1, index + 1) ||
                 DfsWordSearch(board, word, row, col - 1, index + 1);
    board[row][col] = temp;
    return found;
}

bool Exist(vector<vector<char>>& board, string word) {
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            if (DfsWordSearch(board, word, static_cast<int>(i), static_cast<int>(j), 0)) return true;
        }
    }
    return false;
}

/**
 * Problem 8: All Paths from Source to Target (LeetCode 797)
 * ----------------------------------------------------------
 * 🧠 Description:
 * Given a DAG of n nodes labeled from 0 to n - 1,
 * return all possible paths from node 0 to node n - 1.
 *
 * 🔍 Example:
 * Input: graph = [[1,2],[3],[3],[]]
 * Output: [[0,1,3],[0,2,3]]
 *
 * 💡 Strategy:
 * DFS traversal with path vector. Backtrack after exploring each neighbor.
 *
 * ✨ Explanation:
 * Add current node to path. If destination reached, add to result.
 * Else recursively call DFS on all neighbors.
 *
 * 🔁 Transition:
 * - For each neighbor of current node → dfs(next)
 * - Backtrack: pop current from path after returning
 *
 * 🚨 Edge Cases:
 * - No path exists → return empty vector
 * - Graph is empty or no destination node → return {}
 *
 * ⏱ Time: O(2^n * n), worst case exponential paths. 🧠 Space: O(n) recursion + O(paths)
 */
void DfsAllPaths(const vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& result) {
    path.push_back(node);
    if (static_cast<size_t>(node) == graph.size() - 1) {
        result.push_back(path);
    } else {
        for (int neighbor : graph[node]) {
            DfsAllPaths(graph, neighbor, path, result);
        }
    }
    path.pop_back();
}

vector<vector<int>> AllPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> result;
    vector<int> path;
    DfsAllPaths(graph, 0, path, result);
    return result;
}

/**
 * Problem 9: Path Sum II (LeetCode 113)
 * --------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree and an integer targetSum,
 * return all root-to-leaf paths where the sum equals targetSum.
 *
 * 🔍 Example:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 *
 * 💡 Strategy:
 * DFS recursion. Maintain path + running sum. Backtrack on return.
 *
 * ✨ Explanation:
 * Visit each node. Append value to path, reduce target.
 * If leaf and target == val, store path. Then backtrack.
 *
 * 🔁 Transition:
 * - dfs(node, target - val, path)
 * - Add path if leaf && target == 0
 * - Backtrack: path.pop_back()
 *
 * 🚨 Edge Cases:
 * - Empty tree → return empty list
 * - No path found → return []
 *
 * ⏱ Time: O(n^2) worst case (n paths, each up to length n). 🧠 Space: O(h) recursion
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void DfsPathSum(TreeNode* node, int target, vector<int>& path, vector<vector<int>>& result) {
    if (!node) return;
    path.push_back(node->val);
    if (!node->left && !node->right && target == node->val) {
        result.push_back(path);
    } else {
        DfsPathSum(node->left, target - node->val, path, result);
        DfsPathSum(node->right, target - node->val, path, result);
    }
    path.pop_back();
}

vector<vector<int>> PathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    DfsPathSum(root, targetSum, path, result);
    return result;
}

/**
 * Problem 10: Clone Graph (LeetCode 133)
 * ---------------------------------------
 * 🧠 Description:
 * Given a reference to a node in a connected undirected graph,
 * return a deep copy (clone) of the graph.
 *
 * 🔍 Example:
 * Input: adj list [[2,4],[1,3],[2,4],[1,3]]
 * Output: clone of node 1 with correct neighbor links
 *
 * 💡 Strategy:
 * Use DFS and hashmap to track already cloned nodes.
 *
 * ✨ Explanation:
 * Clone each node recursively. For each neighbor, clone if not yet cloned.
 * Use map to avoid repeated work and cycles.
 *
 * 🔁 Transition:
 * - If node in map → return map[node]
 * - Otherwise → create clone, map it, clone neighbors
 *
 * 🚨 Edge Cases:
 * - Input is nullptr → return nullptr
 *
 * ⏱ Time: O(n), 🧠 Space: O(n) for visited map and recursion stack
 */
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors({}) {}
    Node(int _val) : val(_val), neighbors({}) {}
};

Node* DfsClone(Node* node, unordered_map<Node*, Node*>& visited) {
    if (!node) return nullptr;
    if (visited.count(node)) return visited[node];

    Node* clone = new Node(node->val);
    visited[node] = clone;
    for (Node* neighbor : node->neighbors) {
        clone->neighbors.push_back(DfsClone(neighbor, visited));
    }
    return clone;
}

Node* CloneGraph(Node* node) {
    unordered_map<Node*, Node*> visited;
    return DfsClone(node, visited);
}

/**
 * Problem 11: Course Schedule (LeetCode 207)
 * -------------------------------------------
 * 🧠 Description:
 * There are numCourses labeled 0 to numCourses-1.
 * Some courses have prerequisites. Return true if you can finish all courses.
 *
 * 🔍 Example:
 * numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * 💡 Strategy:
 * Use DFS to detect cycles in the dependency graph.
 *
 * ✨ Explanation:
 * 3-color DFS: unvisited (0), visiting (1), visited (2)
 * If we reach a visiting node again, there's a cycle.
 *
 * 🔁 Transition:
 * - dfs(u):
 *   - mark visiting
 *   - dfs all neighbors
 *   - mark visited
 *
 * 🚨 Edge Cases:
 * - No prerequisites → return true
 * - Self-loop → return false
 *
 * ⏱ Time: O(V+E), 🧠 Space: O(V) recursion
 */
bool DfsCycle(int node, vector<vector<int>>& graph, vector<int>& visited) {
    if (visited[node] == 1) return false;  // cycle
    if (visited[node] == 2) return true;   // already checked

    visited[node] = 1; // visiting
    for (int neighbor : graph[node]) {
        if (!DfsCycle(neighbor, graph, visited)) return false;
    }
    visited[node] = 2; // visited
    return true;
}

bool CanFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto& edge : prerequisites) {
        graph[edge[1]].push_back(edge[0]);
    }

    vector<int> visited(numCourses, 0);
    for (int i = 0; i < numCourses; ++i) {
        if (!DfsCycle(i, graph, visited)) return false;
    }
    return true;
}

/**
 * Problem 12: Reconstruct Itinerary (LeetCode 332)
 * --------------------------------------------------
 * 🧠 Description:
 * Given a list of airline tickets represented as pairs [from, to],
 * reconstruct the itinerary in lexical order starting from "JFK".
 *
 * 🔍 Example:
 * tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
 * Output: ["JFK","MUC","LHR","SFO","SJC"]
 *
 * 💡 Strategy:
 * Use DFS and multiset (lexical order), backtracking with postorder traversal.
 *
 * ✨ Explanation:
 * Treat as graph, always choose smallest lexical destination.
 * Postorder traversal ensures children visited first.
 *
 * 🔁 Transition:
 * - dfs(current)
 * - while ticket exists → remove and recurse
 * - push to result after recursion (reverse later)
 *
 * 🚨 Edge Cases:
 * - Multiple same destinations → use multiset
 * - Cycles in graph → no problem if valid tickets used once
 *
 * ⏱ Time: O(E log E), 🧠 Space: O(E)
 */
void DfsItinerary(const string& airport, unordered_map<string, multiset<string>>& graph, vector<string>& path) {
    while (!graph[airport].empty()) {
        string next = *graph[airport].begin();
        graph[airport].erase(graph[airport].begin());
        DfsItinerary(next, graph, path);
    }
    path.push_back(airport);
}

vector<string> FindItinerary(vector<vector<string>>& tickets) {
    unordered_map<string, multiset<string>> graph;
    for (auto& ticket : tickets) {
        graph[ticket[0]].insert(ticket[1]);
    }

    vector<string> path;
    DfsItinerary("JFK", graph, path);
    reverse(path.begin(), path.end());
    return path;
}

/**
 * Problem 13: Detect Cycle in Directed Graph (Custom Variant)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given a directed graph, determine if it contains a cycle.
 * Return true if any cycle exists, otherwise false.
 *
 * 🔍 Example:
 * Input: V = 4, edges = [[0,1],[1,2],[2,0],[2,3]]
 * Output: true (cycle exists: 0→1→2→0)
 *
 * 💡 Strategy:
 * Use DFS with 3-state coloring: unvisited (0), visiting (1), visited (2).
 *
 * ✨ Explanation:
 * Visiting a node already marked as "visiting" means we've hit a back edge = cycle.
 *
 * 🔁 Transition:
 * - dfs(u):
 *   - mark u as visiting
 *   - for each neighbor → dfs
 *   - mark u as visited
 *
 * 🚨 Edge Cases:
 * - Empty graph → false
 * - Self-loop → true
 *
 * ⏱ Time: O(V+E), 🧠 Space: O(V)
 */
bool HasCycleDFS(int node, const vector<vector<int>>& graph, vector<int>& state) {
    state[node] = 1; // visiting
    for (int neighbor : graph[node]) {
        if (state[neighbor] == 1) return true; // back edge
        if (state[neighbor] == 0 && HasCycleDFS(neighbor, graph, state))
            return true;
    }
    state[node] = 2; // visited
    return false;
}

bool HasCycle(int num_nodes, const vector<vector<int>>& graph) {
    vector<int> state(num_nodes, 0);
    for (int i = 0; i < num_nodes; ++i) {
        if (state[i] == 0 && HasCycleDFS(i, graph, state))
            return true;
    }
    return false;
}

/**
 * Problem 14: Graph Valid Tree (LeetCode 261)
 * -------------------------------------------
 * 🧠 Description:
 * Given n nodes labeled from 0 to n-1 and a list of undirected edges,
 * determine if the graph is a valid tree (i.e., connected and acyclic).
 *
 * 🔍 Example:
 * Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
 * Output: true
 *
 * 💡 Strategy:
 * Perform DFS and check for cycles. Also check if all nodes are visited.
 *
 * ✨ Explanation:
 * Detect cycle via DFS from any node. If a cycle exists or not all nodes are visited → not tree.
 *
 * 🔁 Transition:
 * - Track parent to avoid false cycles from undirected edges
 * - Count visited nodes
 *
 * 🚨 Edge Cases:
 * - n == 0 → false
 * - Edges.length != n - 1 → not tree
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V)
 */
bool DfsTreeCheck(int node, int parent, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (neighbor == parent) continue; // skip parent
        if (visited[neighbor] || DfsTreeCheck(neighbor, node, graph, visited))
            return true; // cycle
    }
    return false;
}

bool ValidTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != static_cast<size_t>(n) - 1) return false;

    vector<vector<int>> graph(n);
    for (auto& e : edges) {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<bool> visited(n, false);
    if (DfsTreeCheck(0, -1, graph, visited)) return false;

    for (bool v : visited)
        if (!v) return false;
    return true;
}

/**
 * Problem 15: Redundant Connection (LeetCode 684)
 * -----------------------------------------------
 * 🧠 Description:
 * In a graph with a cycle, return the edge that can be removed to make it a tree.
 *
 * 🔍 Example:
 * Input: edges = [[1,2],[1,3],[2,3]]
 * Output: [2,3]
 *
 * 💡 Strategy:
 * Use DFS to check whether two nodes are already connected. If yes, current edge is redundant.
 *
 * ✨ Explanation:
 * For each edge (u,v), if path exists between u and v, it forms a cycle.
 * Otherwise, add edge to graph.
 *
 * 🔁 Transition:
 * - dfs(u, v): check if u can reach v
 * - if yes → return edge
 *
 * 🚨 Edge Cases:
 * - Input guaranteed to form a single cycle
 *
 * ⏱ Time: O(n^2), 🧠 Space: O(n)
 */
bool DfsConnected(int curr, int target, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
    if (curr == target) return true;
    visited.insert(curr);
    for (int neighbor : graph[curr]) {
        if (!visited.count(neighbor)) {
            if (DfsConnected(neighbor, target, graph, visited))
                return true;
        }
    }
    return false;
}

vector<int> FindRedundantConnection(vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> graph;

    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        unordered_set<int> visited;
        if (graph.count(u) && graph.count(v) && DfsConnected(u, v, graph, visited))
            return edge;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return {};
}

/**
 * Problem 16: Decode String (LeetCode 394)
 * -----------------------------------------
 * 🧠 Description:
 * Given an encoded string, return its decoded version.
 * The encoding rule is: k[encoded_string], where encoded_string inside brackets is repeated k times.
 *
 * 🔍 Example:
 * Input: "3[a2[c]]"
 * Output: "accaccacc"
 *
 * 💡 Strategy:
 * Use DFS via recursion with index reference. Parse digits and nested brackets.
 *
 * ✨ Explanation:
 * Traverse string char-by-char. When hitting '[', recurse to decode substring.
 * Return result when matching ']'.
 *
 * 🔁 Transition:
 * - For each character:
 *   - if digit → accumulate number
 *   - if '[' → recurse
 *   - if ']' → return substring
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - No brackets → return input directly
 *
 * ⏱ Time: O(n), 🧠 Space: O(n) for recursion
 */
string DecodeDFS(const string& s, int& index) {
    string result;
    while (static_cast<size_t>(index) < s.size() && s[index] != ']') {
        if (isdigit(s[index])) {
            int count = 0;
            while (isdigit(s[index])) {
                count = count * 10 + (s[index++] - '0');
            }
            index++;  // skip '['
            string decoded = DecodeDFS(s, index);
            index++;  // skip ']'
            while (count--) result += decoded;
        } else {
            result += s[index++];
        }
    }
    return result;
}

string DecodeString(string s) {
    int index = 0;
    return DecodeDFS(s, index);
}

/**
 * Problem 17: Evaluate Division (LeetCode 399)
 * ---------------------------------------------
 * 🧠 Description:
 * You are given equations like a / b = 2.0 and queries like a / c.
 * Return the result of each query, or -1.0 if it cannot be determined.
 *
 * 🔍 Example:
 * equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["c","a"]]
 * Output: [6.0, 1/6.0]
 *
 * 💡 Strategy:
 * Build a weighted graph and run DFS to compute product along the path.
 *
 * ✨ Explanation:
 * Treat each variable as a node. DFS through edges multiplying values until reaching target.
 *
 * 🔁 Transition:
 * - dfs(curr, target, visited, acc_product)
 * - return product if target is reached
 *
 * 🚨 Edge Cases:
 * - var not in graph → return -1.0
 * - self query a/a → return 1.0
 *
 * ⏱ Time: O(E + Q * V), 🧠 Space: O(V + E)
 */
bool DfsDivision(const string& curr, const string& target, unordered_map<string, vector<pair<string, double>>>& graph,
                 unordered_set<string>& visited, double& result, double product) {
    if (curr == target) {
        result = product;
        return true;
    }
    visited.insert(curr);
    for (auto& [neighbor, weight] : graph[curr]) {
        if (!visited.count(neighbor)) {
            if (DfsDivision(neighbor, target, graph, visited, result, product * weight))
                return true;
        }
    }
    return false;
}

vector<double> CalcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    unordered_map<string, vector<pair<string, double>>> graph;
    for (size_t i = 0; i < equations.size(); ++i) {
        string a = equations[i][0], b = equations[i][1];
        double val = values[i];
        graph[a].emplace_back(b, val);
        graph[b].emplace_back(a, 1.0 / val);
    }

    vector<double> results;
    for (auto& q : queries) {
        string src = q[0], dst = q[1];
        if (!graph.count(src) || !graph.count(dst)) {
            results.push_back(-1.0);
            continue;
        }
        unordered_set<string> visited;
        double result = -1.0;
        if (DfsDivision(src, dst, graph, visited, result, 1.0))
            results.push_back(result);
        else
            results.push_back(-1.0);
    }
    return results;
}

/**
 * Problem 18: Rotting Oranges (LeetCode 994 - DFS Variant)
 * ---------------------------------------------------------
 * 🧠 Description:
 * Given a grid with 0 (empty), 1 (fresh), and 2 (rotten) oranges.
 * Every minute, adjacent fresh oranges turn rotten. Return minutes until all rot, or -1.
 *
 * 🔍 Example:
 * Input: [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * 💡 Strategy:
 * For DFS variant: From each rotten orange, propagate rot and track depth.
 *
 * ✨ Explanation:
 * Start DFS from all rotten oranges. Keep a separate matrix of rot times.
 * Use max of dfs return values to determine total time.
 *
 * 🔁 Transition:
 * - dfs(row, col, time) → update rot_time grid
 * - skip if already rotted earlier
 *
 * 🚨 Edge Cases:
 * - No fresh oranges → return 0
 * - Isolated fresh → return -1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsRot(vector<vector<int>>& grid, int row, int col, int time, vector<vector<int>>& rot_time) {
    int m = grid.size(), n = grid[0].size();
    if (row < 0 || row >= m || col < 0 || col >= n || grid[row][col] != 1)
        return;
    if (rot_time[row][col] != -1 && rot_time[row][col] <= time)
        return;

    grid[row][col] = 2;
    rot_time[row][col] = time;
    DfsRot(grid, row + 1, col, time + 1, rot_time);
    DfsRot(grid, row - 1, col, time + 1, rot_time);
    DfsRot(grid, row, col + 1, time + 1, rot_time);
    DfsRot(grid, row, col - 1, time + 1, rot_time);
}

int OrangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> rot_time(m, vector<int>(n, -1));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 2)
                DfsRot(grid, i, j, 0, rot_time);

    int max_time = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) return -1;
            max_time = max(max_time, rot_time[i][j]);
        }

    return max_time;
}

/**
 * Problem 19: Longest Increasing Path in Matrix (LeetCode 329)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given an m x n matrix, return the length of the longest strictly increasing path.
 * You may move in four directions (up, down, left, right).
 *
 * 🔍 Example:
 * Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
 * Output: 4
 *
 * 💡 Strategy:
 * Use DFS + memoization to record length from each cell.
 *
 * ✨ Explanation:
 * For each cell, explore all 4 directions and track increasing paths.
 * Use dp[row][col] to memoize path length starting from (row,col).
 *
 * 🔁 Transition:
 * - If dp[row][col] != 0 → return cached result
 * - For each valid neighbor with larger value → dfs + 1
 *
 * 🚨 Edge Cases:
 * - Empty matrix → return 0
 * - All values same → max path = 1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int DfsLongestPath(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& memo) {
    if (memo[row][col] != 0) return memo[row][col];
    int max_len = 1;
    vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (auto [dr, dc] : dirs) {
        int r = row + dr, c = col + dc;
        if (r >= 0 && static_cast<size_t>(r) < matrix.size() && c >= 0 && static_cast<size_t>(c) < matrix[0].size()
            && matrix[r][c] > matrix[row][col]) {
            max_len = max(max_len, 1 + DfsLongestPath(matrix, r, c, memo));
        }
    }
    memo[row][col] = max_len;
    return max_len;
}

int LongestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> memo(m, vector<int>(n, 0));
    int max_path = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            max_path = max(max_path, DfsLongestPath(matrix, i, j, memo));
    return max_path;
}

/**
 * Problem 20: Count Connected Components in Undirected Graph
 * -----------------------------------------------------------
 * 🧠 Description:
 * Given an undirected graph with n nodes and a list of edges,
 * return the number of connected components.
 *
 * 🔍 Example:
 * Input: n = 5, edges = [[0,1],[1,2],[3,4]]
 * Output: 2
 *
 * 💡 Strategy:
 * DFS traversal from unvisited nodes, count # of connected launches.
 *
 * ✨ Explanation:
 * Each DFS visit will mark an entire connected component.
 * Count how many times we initiate DFS.
 *
 * 🔁 Transition:
 * - For i in 0..n-1:
 *   - If unvisited → dfs(i), count++
 *
 * 🚨 Edge Cases:
 * - No edges → return n
 * - Empty graph → return 0
 *
 * ⏱ Time: O(n + e), 🧠 Space: O(n)
 */
void DfsComponents(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor])
            DfsComponents(neighbor, graph, visited);
    }
}

int CountComponents(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<bool> visited(n, false);
    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            DfsComponents(i, graph, visited);
            ++components;
        }
    }
    return components;
}

/**
 * Problem 21: Number of Enclaves (LeetCode 1020)
 * -----------------------------------------------
 * 🧠 Description:
 * Given a binary matrix `grid` of 0s and 1s, return the number of 1s that cannot reach the boundary.
 *
 * 🔍 Example:
 * Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 * Output: 3
 *
 * 💡 Strategy:
 * Use DFS to eliminate all land (1s) connected to the border.
 * Then count remaining 1s as enclaves.
 *
 * ✨ Explanation:
 * Similar to “surrounded regions”. Start DFS from border 1s and mark them as water (0).
 *
 * 🔁 Transition:
 * - For all border cells == 1 → dfs(i, j)
 * - In dfs, mark grid[i][j] = 0
 *
 * 🚨 Edge Cases:
 * - Empty grid → return 0
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsEnclave(vector<vector<int>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1) return;
    grid[i][j] = 0;
    DfsEnclave(grid, i + 1, j);
    DfsEnclave(grid, i - 1, j);
    DfsEnclave(grid, i, j + 1);
    DfsEnclave(grid, i, j - 1);
}

int NumEnclaves(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; ++i) {
        DfsEnclave(grid, i, 0);
        DfsEnclave(grid, i, n - 1);
    }
    for (int j = 0; j < n; ++j) {
        DfsEnclave(grid, 0, j);
        DfsEnclave(grid, m - 1, j);
    }

    int count = 0;
    for (auto& row : grid)
        for (int cell : row)
            count += (cell == 1);
    return count;
}

/**
 * Problem 22: Surrounded Regions (visited variant)
 * -------------------------------------------------
 * 🧠 Description:
 * Modify LC 130 to use a separate visited array instead of marking board directly.
 *
 * 🔍 Example:
 * Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
 * Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
 *
 * 💡 Strategy:
 * DFS from border 'O', mark visited.
 * Then flip unvisited 'O' → 'X'
 *
 * ✨ Explanation:
 * Instead of using 'E', we use a visited matrix to track safety.
 *
 * 🔁 Transition:
 * - dfs(i, j) → visited[i][j] = true
 * - flip remaining unvisited 'O'
 *
 * 🚨 Edge Cases:
 * - All 'X' or all 'O' grid
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsSafe(vector<vector<char>>& board, int i, int j, vector<vector<bool>>& visited) {
    int m = board.size(), n = board[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O' || visited[i][j]) return;
    visited[i][j] = true;
    DfsSafe(board, i + 1, j, visited);
    DfsSafe(board, i - 1, j, visited);
    DfsSafe(board, i, j + 1, visited);
    DfsSafe(board, i, j - 1, visited);
}

void SolveSurroundedRegionsVisited(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        DfsSafe(board, i, 0, visited);
        DfsSafe(board, i, n - 1, visited);
    }
    for (int j = 0; j < n; ++j) {
        DfsSafe(board, 0, j, visited);
        DfsSafe(board, m - 1, j, visited);
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] == 'O' && !visited[i][j])
                board[i][j] = 'X';
}

/**
 * Problem 23: Count Subtree Nodes with Same Label (LeetCode 1519)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a tree and a string of labels, return count of nodes in subtree with same label.
 *
 * 🔍 Example:
 * n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels = "abaedcd"
 * Output: [2,1,1,1,1,1,1]
 *
 * 💡 Strategy:
 * Postorder DFS. At each node, aggregate label counts from children.
 *
 * ✨ Explanation:
 * Build tree with adjacency list. Traverse bottom-up and tally label counts.
 *
 * 🔁 Transition:
 * - dfs(node, parent): get count from children
 * - update count[char] += sum from children
 *
 * 🚨 Edge Cases:
 * - Single node → count = 1
 *
 * ⏱ Time: O(n), 🧠 Space: O(n * 26)
 */
vector<int> DfsLabelCount(int node, int parent, vector<vector<int>>& tree, string& labels, vector<int>& result) {
    vector<int> count(26, 0);
    for (int child : tree[node]) {
        if (child == parent) continue;
        vector<int> child_count = DfsLabelCount(child, node, tree, labels, result);
        for (int i = 0; i < 26; ++i)
            count[i] += child_count[i];
    }
    count[labels[node] - 'a']++;
    result[node] = count[labels[node] - 'a'];
    return count;
}

vector<int> CountSubTrees(int n, vector<vector<int>>& edges, string labels) {
    vector<vector<int>> tree(n);
    for (auto& e : edges) {
        tree[e[0]].push_back(e[1]);
        tree[e[1]].push_back(e[0]);
    }
    vector<int> result(n, 0);
    DfsLabelCount(0, -1, tree, labels, result);
    return result;
}

/**
 * Problem 24: Critical Connections (LeetCode 1192)
 * -------------------------------------------------
 * 🧠 Description:
 * Given a network of n servers and connections, return all critical connections.
 * A critical connection is an edge that, if removed, makes the network disconnected.
 *
 * 🔍 Example:
 * Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
 * Output: [[1,3]]
 *
 * 💡 Strategy:
 * Tarjan's algorithm: track discovery time and lowest reachable time.
 *
 * ✨ Explanation:
 * If low[neighbor] > discovery[node], edge is a bridge.
 * Use DFS to compute discovery time and back edge reachability.
 *
 * 🔁 Transition:
 * - dfs(node, parent):
 *   - set disc[node] = low[node] = time++
 *   - for neighbors:
 *     - skip parent
 *     - if unvisited → recurse
 *     - update low[node]
 *
 * 🚨 Edge Cases:
 * - Fully connected graph → return []
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V)
 */
void DfsBridge(int u, int parent, vector<vector<int>>& graph, vector<int>& disc, vector<int>& low,
               int& time, vector<vector<int>>& result) {
    disc[u] = low[u] = time++;
    for (int v : graph[u]) {
        if (v == parent) continue;
        if (disc[v] == -1) {
            DfsBridge(v, u, graph, disc, low, time, result);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                result.push_back({u, v});
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<vector<int>> CriticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n), result;
    for (auto& c : connections) {
        graph[c[0]].push_back(c[1]);
        graph[c[1]].push_back(c[0]);
    }
    vector<int> disc(n, -1), low(n, -1);
    int time = 0;
    DfsBridge(0, -1, graph, disc, low, time, result);
    return result;
}

/**
 * Problem 25: Find Eventual Safe States (LeetCode 802)
 * ------------------------------------------------------
 * 🧠 Description:
 * In a directed graph, return all nodes that lead to terminal nodes (no cycles).
 *
 * 🔍 Example:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 * Output: [2,4,5,6]
 *
 * 💡 Strategy:
 * DFS with coloring: 0 = unvisited, 1 = visiting, 2 = safe.
 *
 * ✨ Explanation:
 * A node is safe if all its paths lead to safe nodes (not in cycles).
 *
 * 🔁 Transition:
 * - dfs(node): if visiting again → not safe
 * - if all neighbors are safe → mark current safe
 *
 * 🚨 Edge Cases:
 * - Graph with no cycles → all nodes are safe
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V)
 */
bool DfsSafe(int node, vector<vector<int>>& graph, vector<int>& state) {
    if (state[node] == 1) return false;
    if (state[node] == 2) return true;

    state[node] = 1;
    for (int neighbor : graph[node]) {
        if (!DfsSafe(neighbor, graph, state))
            return false;
    }
    state[node] = 2;
    return true;
}

vector<int> EventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> state(n, 0);
    vector<int> result;

    for (int i = 0; i < n; ++i) {
        if (DfsSafe(i, graph, state))
            result.push_back(i);
    }
    return result;
}

/**
 * Problem 26: Island Perimeter (LeetCode 463)
 * --------------------------------------------
 * 🧠 Description:
 * Given a grid of 0s and 1s, return the perimeter of the island.
 * The island has exactly one component.
 *
 * 🔍 Example:
 * Input: [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
 * Output: 16
 *
 * 💡 Strategy:
 * Use DFS to visit each land cell and count its exposed sides.
 *
 * ✨ Explanation:
 * For each land cell, check all 4 directions. If out of bounds or water, add to perimeter.
 *
 * 🔁 Transition:
 * - dfs(i, j) → return 1 if out of bounds or water
 * - mark visited
 *
 * 🚨 Edge Cases:
 * - Only one land cell → return 4
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int DfsPerimeter(vector<vector<int>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0) return 1;
    if (grid[i][j] == 2) return 0;

    grid[i][j] = 2;
    return DfsPerimeter(grid, i + 1, j) + DfsPerimeter(grid, i - 1, j) +
           DfsPerimeter(grid, i, j + 1) + DfsPerimeter(grid, i, j - 1);
}

int IslandPerimeter(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 1)
                return DfsPerimeter(grid, i, j);
    return 0;
}

/**
 * Problem 27: Max Area of Connected 1s (Custom)
 * ----------------------------------------------
 * 🧠 Description:
 * Given a binary matrix of 0s and 1s, return the size of the largest connected area of 1s.
 *
 * 🔍 Example:
 * Input: [[1,1,0,0],[0,1,1,0],[0,0,1,0],[1,0,0,0]]
 * Output: 5
 *
 * 💡 Strategy:
 * Use DFS to explore each component. Track size of current component.
 *
 * ✨ Explanation:
 * Perform DFS on each unvisited 1. Count number of 1s in this component.
 *
 * 🔁 Transition:
 * - dfs(i, j): mark visited, return 1 + dfs(neighbors)
 *
 * 🚨 Edge Cases:
 * - All 0s → return 0
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int DfsMaxArea(vector<vector<int>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1) return 0;

    grid[i][j] = 2;
    return 1 + DfsMaxArea(grid, i + 1, j) + DfsMaxArea(grid, i - 1, j) +
               DfsMaxArea(grid, i, j + 1) + DfsMaxArea(grid, i, j - 1);
}

int MaxConnectedArea(vector<vector<int>>& grid) {
    int max_area = 0;
    for (size_t i = 0; i < grid.size(); ++i)
        for (size_t j = 0; j < grid[0].size(); ++j)
            if (grid[i][j] == 1)
                max_area = max(max_area, DfsMaxArea(grid, static_cast<int>(i), static_cast<int>(j)));
    return max_area;
}

/**
 * Problem 28: Pacific Atlantic Count (Variant)
 * ---------------------------------------------
 * 🧠 Description:
 * Count number of cells that can reach both Pacific and Atlantic oceans.
 *
 * 🔍 Example:
 * Input: heights = [[1,2,2,3],[3,2,3,4],[2,4,5,3]]
 * Output: 5 (cells reachable by both)
 *
 * 💡 Strategy:
 * Same as LC 417, but only return count.
 *
 * ✨ Explanation:
 * DFS from Pacific and Atlantic borders separately, count intersection.
 *
 * 🔁 Transition:
 * - dfs(i, j, ocean): mark visited[i][j]
 *
 * 🚨 Edge Cases:
 * - Grid all same → all cells valid
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsOcean(const vector<vector<int>>& heights, int i, int j, vector<vector<bool>>& visited) {
    int m = heights.size(), n = heights[0].size();
    visited[i][j] = true;
    vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto [di, dj] : dirs) {
        int ni = i + di, nj = j + dj;
        if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
            !visited[ni][nj] && heights[ni][nj] >= heights[i][j]) {
            DfsOcean(heights, ni, nj, visited);
        }
    }
}

int PacificAtlanticCount(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pac(m, vector<bool>(n, false));
    vector<vector<bool>> atl(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        DfsOcean(heights, i, 0, pac);
        DfsOcean(heights, i, n - 1, atl);
    }
    for (int j = 0; j < n; ++j) {
        DfsOcean(heights, 0, j, pac);
        DfsOcean(heights, m - 1, j, atl);
    }

    int count = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (pac[i][j] && atl[i][j]) ++count;
    return count;
}

/**
 * Problem 29: Largest Color Value in a Directed Graph (LeetCode 1857)
 * --------------------------------------------------------------------
 * 🧠 Description:
 * Given a DAG and a string colors, return the largest number of same color along any path.
 * Return -1 if the graph has a cycle.
 *
 * 🔍 Example:
 * colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
 * Output: 3 (for 'a' path: 0->2->3->4)
 *
 * 💡 Strategy:
 * DFS with memoization and cycle detection. Use color count arrays.
 *
 * ✨ Explanation:
 * Top-down DFS. Track max count per color per node.
 *
 * 🔁 Transition:
 * - dfs(node): returns vector<int> color_count[26]
 * - merge max of child color vectors
 *
 * 🚨 Edge Cases:
 * - Graph with cycle → return -1
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V * 26)
 */
bool DfsColor(int node, const string& colors, vector<vector<int>>& graph, vector<vector<int>>& dp,
              vector<bool>& visited, vector<bool>& in_stack, bool& has_cycle) {
    if (in_stack[node]) { has_cycle = true; return false; }
    if (visited[node]) return true;

    visited[node] = true;
    in_stack[node] = true;

    for (int nei : graph[node]) {
        if (!DfsColor(nei, colors, graph, dp, visited, in_stack, has_cycle))
            return false;
        for (int i = 0; i < 26; ++i)
            dp[node][i] = max(dp[node][i], dp[nei][i]);
    }

    dp[node][colors[node] - 'a']++;
    in_stack[node] = false;
    return true;
}

int LargestPathValue(string colors, vector<vector<int>>& edges) {
    int n = colors.size();
    vector<vector<int>> graph(n);
    for (auto& e : edges)
        graph[e[0]].push_back(e[1]);

    vector<vector<int>> dp(n, vector<int>(26, 0));
    vector<bool> visited(n, false), in_stack(n, false);
    bool has_cycle = false;
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            DfsColor(i, colors, graph, dp, visited, in_stack, has_cycle);

    if (has_cycle) return -1;
    int max_color = 0;
    for (auto& v : dp)
        for (int count : v)
            max_color = max(max_color, count);
    return max_color;
}

/**
 * Problem 30: Number of Distinct Islands (LeetCode 694)
 * -------------------------------------------------------
 * 🧠 Description:
 * Count number of distinct shapes of islands in the grid (not position, just shape).
 *
 * 🔍 Example:
 * Input: [[1,1,0,0],[1,0,0,0],[0,0,1,1],[0,0,1,1]]
 * Output: 1
 *
 * 💡 Strategy:
 * Use DFS with path signature encoding.
 *
 * ✨ Explanation:
 * Record relative movement directions (e.g., 'U','D','L','R','B') to represent shape.
 *
 * 🔁 Transition:
 * - dfs(i, j, path, dir), append 'B' when backtracking
 *
 * 🚨 Edge Cases:
 * - No islands → return 0
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void DfsIslandShape(vector<vector<int>>& grid, int i, int j, string& path, char dir) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1) return;
    grid[i][j] = 0;
    path += dir;
    DfsIslandShape(grid, i + 1, j, path, 'D');
    DfsIslandShape(grid, i - 1, j, path, 'U');
    DfsIslandShape(grid, i, j + 1, path, 'R');
    DfsIslandShape(grid, i, j - 1, path, 'L');
    path += 'B';  // backtrack
}

int NumDistinctIslands(vector<vector<int>>& grid) {
    set<string> shapes;
    for (size_t i = 0; i < grid.size(); ++i)
        for (size_t j = 0; j < grid[0].size(); ++j)
            if (grid[i][j] == 1) {
                string path;
                DfsIslandShape(grid, static_cast<int>(i), static_cast<int>(j), path, 'S');
                shapes.insert(path);
            }
    return shapes.size();
}


int main() {
    // Problem 1: Number of Islands
    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Problem 1: " << NumIslands(grid1) << endl;

    // Problem 2: Max Area of Island
    vector<vector<int>> grid2 = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    cout << "Problem 2: " << MaxAreaOfIsland(grid2) << endl;

    // Problem 3: Flood Fill
    vector<vector<int>> image3 = {
        {1,1,1},
        {1,1,0},
        {1,0,1}
    };
    auto result3 = FloodFill(image3, 1, 1, 2);
    cout << "Problem 3: ";
    for (auto row : result3) {
        for (int val : row) cout << val << " ";
        cout << " | ";
    }
    cout << endl;

    // Problem 4: Surrounded Regions
    vector<vector<char>> board4 = {
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    };
    SolveSurroundedRegions(board4);
    cout << "Problem 4: ";
    for (auto row : board4) {
        for (char c : row) cout << c << " ";
        cout << "| ";
    }
    cout << endl;

    // Problem 5: Pacific Atlantic Water Flow
    vector<vector<int>> heights5 = {
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    };
    auto result5 = PacificAtlantic(heights5);
    cout << "Problem 5: ";
    for (auto& v : result5) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << endl;

        // Problem 6: Count Sub Islands
    vector<vector<int>> grid1_6 = {
        {1,1,1,0},
        {0,1,1,1},
        {0,0,0,1}
    };
    vector<vector<int>> grid2_6 = {
        {1,1,1,0},
        {0,0,1,1},
        {0,1,0,1}
    };
    cout << "Problem 6: " << CountSubIslands(grid1_6, grid2_6) << endl;

    // Problem 7: Word Search
    vector<vector<char>> board7 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << "Problem 7: " << (Exist(board7, "ABCCED") ? "true" : "false") << endl;

    // Problem 8: All Paths from Source to Target
    vector<vector<int>> graph8 = {
        {1,2}, {3}, {3}, {}
    };
    auto paths8 = AllPathsSourceTarget(graph8);
    cout << "Problem 8: ";
    for (auto& path : paths8) {
        cout << "[";
        for (int v : path) cout << v << " ";
        cout << "] ";
    }
    cout << endl;

    // Problem 9: Path Sum II
    TreeNode* root9 = new TreeNode(5);
    root9->left = new TreeNode(4);
    root9->right = new TreeNode(8);
    root9->left->left = new TreeNode(11);
    root9->left->left->left = new TreeNode(7);
    root9->left->left->right = new TreeNode(2);
    root9->right->left = new TreeNode(13);
    root9->right->right = new TreeNode(4);
    root9->right->right->left = new TreeNode(5);
    root9->right->right->right = new TreeNode(1);
    auto result9 = PathSum(root9, 22);
    cout << "Problem 9: ";
    for (auto& path : result9) {
        cout << "[";
        for (int val : path) cout << val << " ";
        cout << "] ";
    }
    cout << endl;

    // Problem 10: Clone Graph
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};
    Node* cloned = CloneGraph(n1);
    cout << "Problem 10: Cloned node value = " << (cloned ? cloned->val : -1) << endl;

        // Problem 11: Course Schedule
    int numCourses11 = 2;
    vector<vector<int>> prereqs11 = {{1, 0}};
    cout << "Problem 11: " << (CanFinish(numCourses11, prereqs11) ? "true" : "false") << endl;

    // Problem 12: Reconstruct Itinerary
    vector<vector<string>> tickets12 = {
        {"MUC", "LHR"},
        {"JFK", "MUC"},
        {"SFO", "SJC"},
        {"LHR", "SFO"}
    };
    auto result12 = FindItinerary(tickets12);
    cout << "Problem 12: ";
    for (const string& s : result12) cout << s << " ";
    cout << endl;

    // Problem 13: Detect Cycle in Directed Graph
    vector<vector<int>> graph13 = {
        {1}, {2}, {0}, {4}, {}
    };
    cout << "Problem 13: " << (HasCycle(5, graph13) ? "true" : "false") << endl;

    // Problem 14: Valid Tree
    int n14 = 5;
    vector<vector<int>> edges14 = {
        {0,1},{0,2},{0,3},{1,4}
    };
    cout << "Problem 14: " << (ValidTree(n14, edges14) ? "true" : "false") << endl;

    // Problem 15: Redundant Connection
    vector<vector<int>> edges15 = {
        {1,2},{1,3},{2,3}
    };
    auto result15 = FindRedundantConnection(edges15);
    cout << "Problem 15: [" << result15[0] << "," << result15[1] << "]" << endl;

    // Problem 16: Decode String
    string input16 = "3[a2[c]]";
    cout << "Problem 16: " << DecodeString(input16) << endl;

    // Problem 17: Evaluate Division
    vector<vector<string>> eqs17 = {{"a", "b"}, {"b", "c"}};
    vector<double> vals17 = {2.0, 3.0};
    vector<vector<string>> queries17 = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    auto result17 = CalcEquation(eqs17, vals17, queries17);
    cout << "Problem 17: ";
    for (double d : result17) cout << d << " ";
    cout << endl;

    // Problem 18: Rotting Oranges
    vector<vector<int>> grid18 = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    cout << "Problem 18: " << OrangesRotting(grid18) << endl;

    // Problem 19: Longest Increasing Path in Matrix
    vector<vector<int>> matrix19 = {
        {9,9,4},
        {6,6,8},
        {2,1,1}
    };
    cout << "Problem 19: " << LongestIncreasingPath(matrix19) << endl;

    // Problem 20: Count Connected Components
    int n20 = 5;
    vector<vector<int>> edges20 = {
        {0,1},{1,2},{3,4}
    };
    cout << "Problem 20: " << CountComponents(n20, edges20) << endl;

        // Problem 21: Number of Enclaves
    vector<vector<int>> grid21 = {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    cout << "Problem 21: " << NumEnclaves(grid21) << endl;

    // Problem 22: Surrounded Regions (visited variant)
    vector<vector<char>> board22 = {
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    };
    SolveSurroundedRegionsVisited(board22);
    cout << "Problem 22: ";
    for (auto& row : board22) {
        for (char c : row) cout << c << " ";
        cout << "| ";
    }
    cout << endl;

    // Problem 23: Count Subtree Nodes with Same Label
    int n23 = 7;
    vector<vector<int>> edges23 = {
        {0,1},{0,2},{1,4},{1,5},{2,3},{2,6}
    };
    string labels23 = "abaedcd";
    auto result23 = CountSubTrees(n23, edges23, labels23);
    cout << "Problem 23: ";
    for (int x : result23) cout << x << " ";
    cout << endl;

    // Problem 24: Critical Connections
    int n24 = 4;
    vector<vector<int>> connections24 = {
        {0,1},{1,2},{2,0},{1,3}
    };
    auto bridges24 = CriticalConnections(n24, connections24);
    cout << "Problem 24: ";
    for (auto& b : bridges24) cout << "[" << b[0] << "," << b[1] << "] ";
    cout << endl;

    // Problem 25: Eventual Safe States
    vector<vector<int>> graph25 = {
        {1,2},{2,3},{5},{0},{5},{},{}
    };
    auto safe25 = EventualSafeNodes(graph25);
    cout << "Problem 25: ";
    for (int x : safe25) cout << x << " ";
    cout << endl;

    // Problem 26: Island Perimeter
    vector<vector<int>> grid26 = {
        {0,1,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {1,1,0,0}
    };
    cout << "Problem 26: " << IslandPerimeter(grid26) << endl;

    // Problem 27: Max Connected Area (Custom)
    vector<vector<int>> grid27 = {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {1,0,0,0}
    };
    cout << "Problem 27: " << MaxConnectedArea(grid27) << endl;

    // Problem 28: Pacific Atlantic Count
    vector<vector<int>> heights28 = {
        {1,2,2,3},
        {3,2,3,4},
        {2,4,5,3}
    };
    cout << "Problem 28: " << PacificAtlanticCount(heights28) << endl;

    // Problem 29: Largest Color Value in DAG
    string colors29 = "abaca";
    vector<vector<int>> edges29 = {
        {0,1},{0,2},{2,3},{3,4}
    };
    cout << "Problem 29: " << LargestPathValue(colors29, edges29) << endl;

    // Problem 30: Number of Distinct Islands
    vector<vector<int>> grid30 = {
        {1,1,0,0},
        {1,0,0,0},
        {0,0,1,1},
        {0,0,1,1}
    };
    cout << "Problem 30: " << NumDistinctIslands(grid30) << endl;

    return 0;
}
