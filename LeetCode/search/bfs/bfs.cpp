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
#include <numeric>
#include <climits>
#include <cstdint>
using namespace std;

/**
 * 📚 BFS (Breadth-First Search) Technique Overview
 * ================================================
 *
 * BFS is a fundamental graph traversal and search algorithm used to explore nodes level-by-level.
 * It is particularly useful for finding shortest paths, solving layer-based problems,
 * or performing reachability analysis in various data structures:
 * - 🌐 Graph BFS: node-based search over arbitrary connectivity
 * - 🧱 Grid BFS: matrix-based traversal with direction vectors
 * - 🌲 Tree BFS: level-order traversal of hierarchical trees
 * 
 *  *
 * 🧠 When to Use BFS:
 * -------------------
 * ✅ Use BFS when the problem requires:
 * - Finding the shortest path in **unweighted graphs** or grids
 * - Exploring states in layers (i.e., minimum number of steps/moves)
 * - Processing **multi-source spread** problems (e.g., rotting oranges, gate distances)
 * - Building structures level-by-level (e.g., tree level order traversal)
 *
 * ❗ Use BFS over DFS when:
 * - You want the **minimum number of transitions** (e.g., word ladder, sliding puzzle)
 * - You must guarantee the first path found is the **shortest**
 * - DFS would go too deep and miss shorter solutions (especially in cyclic/large graphs)
 *
 * 🛑 Problems where **only BFS works** (DFS fails):
 * - **Shortest path** from one state to another (e.g., "hit" to "cog")
 * - **Minimum steps to transform** or spread something (e.g., oranges, distance to nearest 0)
 * - Where DFS might go deep into non-optimal branches and not guarantee minimality
 *
 * =====================================================================
 * 🌐 1. Graph BFS
 * =====================================================================
 * 🧠 Description:
 * Graph BFS explores the nearest neighbors first, expanding outwards.
 * Common uses include:
 * - Finding the shortest path in unweighted graphs
 * - Detecting connected components
 * - Level-wise processing
 *
 * 💡 Strategy:
 * - Use a queue to process nodes in FIFO order.
 * - Maintain a visited array or set to avoid revisiting.
 * - Each layer processed represents one "step" away from the source.
 *
 * ⏱️ Complexity:
 * - Time: O(V + E) where V = number of vertices, E = edges
 * - Space: O(V) for visited and queue
 *
 * 🚨 Edge Cases:
 * - Disconnected nodes
 * - Self-loops and duplicate edges
 *
 * 🔁 Template:
 * void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
 *     queue<int> q;
 *     q.push(start);
 *     visited[start] = true;
 *     while (!q.empty()) {
 *         int node = q.front(); q.pop();
 *         for (int neighbor : graph[node]) {
 *             if (!visited[neighbor]) {
 *                 visited[neighbor] = true;
 *                 q.push(neighbor);
 *             }
 *         }
 *     }
 * }
 *
 * =====================================================================
 * 🧱 2. Grid BFS (Matrix BFS)
 * =====================================================================
 * 🧠 Description:
 * Grid BFS is used for traversing 2D (or 3D) matrices, such as in maze solving,
 * island problems, or simulating diffusion.
 *
 * 💡 Strategy:
 * - Enqueue all valid starting cells (e.g., all '1's or all gates)
 * - Use dx/dy direction vectors to explore 4 or 8 directions
 * - Mark visited cells to avoid repetition
 *
 * ⏱️ Complexity:
 * - Time: O(m * n)
 * - Space: O(m * n) for visited or in-place marking
 *
 * 🚨 Edge Cases:
 * - Out-of-bounds checks for neighbors
 * - Cells with impassable values (e.g., walls)
 *
 * 🔁 Template:
 * void bfs(int i, int j, vector<vector<int>>& grid) {
 *     int m = grid.size(), n = grid[0].size();
 *     queue<pair<int, int>> q;
 *     q.push({i, j});
 *     vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
 *     while (!q.empty()) {
 *         auto [x, y] = q.front(); q.pop();
 *         for (auto [dx, dy] : dirs) {
 *             int nx = x + dx, ny = y + dy;
 *             if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == target) {
 *                 grid[nx][ny] = visitedMark;
 *                 q.push({nx, ny});
 *             }
 *         }
 *     }
 * }
 *
 * =====================================================================
 * 🌲 3. Tree BFS (Level-Order Traversal)
 * =====================================================================
 * 🧠 Description:
 * Tree BFS is used to traverse trees level-by-level.
 * Common applications include:
 * - Zigzag traversal
 * - Minimum depth calculation
 * - Printing/processing nodes by level
 *
 * 💡 Strategy:
 * - Start from root, process current level, then enqueue children
 * - Track level size to separate layers
 *
 * ⏱️ Complexity:
 * - Time: O(n), n = number of nodes
 * - Space: O(w), w = maximum width of tree
 *
 * 🚨 Edge Cases:
 * - Empty tree → return []
 *
 * 🔁 Template:
 * void bfs(TreeNode* root) {
 *     if (!root) return;
 *     queue<TreeNode*> q;
 *     q.push(root);
 *     while (!q.empty()) {
 *         int size = q.size();
 *         for (int i = 0; i < size; ++i) {
 *             TreeNode* node = q.front(); q.pop();
 *             if (node->left) q.push(node->left);
 *             if (node->right) q.push(node->right);
 *         }
 *     }
 * }
 *
 * =====================================================================
 * 🔚 Summary:
 * - BFS is ideal for shortest paths, layer-order processing, and multi-source expansions.
 * - Grid, graph, and tree structures all adapt BFS with minor variations.
 * - Extensions include:
 *   - Bidirectional BFS for optimization
 *   - 0-1 BFS with deque for weighted edges
 *   - Multi-source BFS (enqueue multiple starting points)
 */

/**
 * Problem 1: Number of Islands (LeetCode 200) ✅ (also in DFS)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D grid of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically.
 *
 * 🔍 Example:
 * Input: grid = [
 *   ['1','1','0','0'],
 *   ['1','1','0','0'],
 *   ['0','0','1','0'],
 *   ['0','0','0','1']
 * ]
 * Output: 3
 *
 * 💡 Strategy:
 * Use BFS to explore each island. For every unvisited land cell, run BFS to mark the island.
 *
 * ✨ Explanation:
 * Traverse the grid, when '1' is found, increment count and start BFS from that cell
 * marking all connected '1's as visited by turning them into '0's or using a visited array.
 *
 * 🔁 Transition:
 * - From each '1', push to queue.
 * - BFS 4-directionally and mark visited.
 *
 * 🚨 Edge Cases:
 * - Empty grid → 0 islands
 * - All water → 0 islands
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n) for queue
 */
void BfsIslands(vector<vector<char>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    q.push({i, j});
    grid[i][j] = '0';

    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                q.push({nx, ny});
                grid[nx][ny] = '0';
            }
        }
    }
}

int NumIslands_BFS(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int m = grid.size(), n = grid[0].size(), count = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == '1') {
                ++count;
                BfsIslands(grid, i, j);
            }
    return count;
}

/**
 * Problem 2: Shortest Path in Binary Matrix (LeetCode 1091)
 * ----------------------------------------------------------
 * 🧠 Description:
 * Given a binary matrix, return the length of the shortest path from top-left to bottom-right,
 * moving in 8 directions. 0 = open cell, 1 = blocked.
 *
 * 🔍 Example:
 * Input: grid = [[0,1],[1,0]]
 * Output: 2
 *
 * 💡 Strategy:
 * Perform BFS from (0,0), explore all 8 directions, and stop when reaching (m-1,n-1).
 *
 * ✨ Explanation:
 * Use a queue to perform BFS with layer depth tracking. Each move represents a step.
 *
 * 🔁 Transition:
 * - Enqueue all reachable neighbors with step count +1
 *
 * 🚨 Edge Cases:
 * - Start or end blocked → return -1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int ShortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    if (grid[0][0] != 0 || grid[m-1][n-1] != 0) return -1;

    queue<tuple<int, int, int>> q;
    q.push({0, 0, 1});
    vector<pair<int, int>> directions = {
        {-1,-1}, {-1,0}, {-1,1},
        { 0,-1},         { 0,1},
        { 1,-1}, { 1,0}, { 1,1}
    };

    grid[0][0] = 1; // mark as visited
    while (!q.empty()) {
        auto [x, y, dist] = q.front(); q.pop();
        if (x == m - 1 && y == n - 1) return dist;
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                q.push({nx, ny, dist + 1});
                grid[nx][ny] = 1;
            }
        }
    }
    return -1;
}

/**
 * Problem 3: Rotting Oranges (LeetCode 994) ✅ (also in DFS)
 * -----------------------------------------------------------
 * 🧠 Description:
 * Every minute, any fresh orange adjacent to a rotten one becomes rotten.
 * Return the minimum number of minutes until no fresh oranges remain.
 *
 * 🔍 Example:
 * Input: [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * 💡 Strategy:
 * Multi-source BFS: enqueue all rotten oranges and run BFS layer by layer.
 *
 * ✨ Explanation:
 * At each minute, infect all adjacent fresh oranges and add to the queue.
 * Track the number of layers (minutes) required.
 *
 * 🔁 Transition:
 * - Use queue<pair<int,int>> and process per level
 *
 * 🚨 Edge Cases:
 * - No fresh → return 0
 * - Isolated fresh → return -1
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
int OrangesRotting_BFS(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0, time = 0;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 2) q.push({i, j});
            if (grid[i][j] == 1) ++fresh;
        }

    vector<pair<int, int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    while (!q.empty() && fresh) {
        int size = q.size();
        while (size--) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    q.push({nx, ny});
                    --fresh;
                }
            }
        }
        ++time;
    }

    return fresh ? -1 : time;
}

/**
 * Problem 4: Open the Lock (LeetCode 752)
 * ----------------------------------------
 * 🧠 Description:
 * Given a lock with 4 circular dials (digits 0-9), return the minimum number of turns required
 * to reach the target from "0000", avoiding deadends. Return -1 if not possible.
 *
 * 🔍 Example:
 * Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 * Output: 6
 *
 * 💡 Strategy:
 * Use BFS starting from "0000", and avoid visiting deadends or repeated states.
 *
 * ✨ Explanation:
 * For each state, generate 8 possible moves (each digit +1/-1),
 * and enqueue those that are not in deadends or visited.
 *
 * 🔁 Transition:
 * - Use a queue of strings and unordered_set for visited.
 *
 * 🚨 Edge Cases:
 * - "0000" is a deadend → return -1
 * - Target is "0000" → return 0
 *
 * ⏱ Time: O(10^4), 🧠 Space: O(10^4)
 */
int OpenLock(vector<string>& deadends, string target) {
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000")) return -1;

    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.push({"0000", 0});
    visited.insert("0000");

    while (!q.empty()) {
        auto [state, steps] = q.front(); q.pop();
        if (state == target) return steps;

        for (int i = 0; i < 4; ++i) {
            for (int d : {-1, 1}) {
                string next = state;
                next[i] = (next[i] - '0' + d + 10) % 10 + '0';
                if (!dead.count(next) && !visited.count(next)) {
                    q.push({next, steps + 1});
                    visited.insert(next);
                }
            }
        }
    }
    return -1;
}

/**
 * Problem 5: Walls and Gates (LeetCode 286)
 * ------------------------------------------
 * 🧠 Description:
 * You are given a m x n grid with 3 values:
 * - -1 = wall, 0 = gate, INF (2^31-1) = empty room.
 * Fill each empty room with the distance to its nearest gate.
 *
 * 🔍 Example:
 * Input: rooms = [
 *   [INF, -1,  0, INF],
 *   [INF, INF, INF, -1],
 *   [INF, -1,  INF, -1],
 *   [0,   -1,  INF, INF]
 * ]
 * Output: updated rooms with minimum distances
 *
 * 💡 Strategy:
 * Multi-source BFS from all gate positions (0s).
 *
 * ✨ Explanation:
 * Start BFS from all gates simultaneously, expanding level by level to fill distances.
 *
 * 🔁 Transition:
 * - Push all gates to queue initially
 * - From each cell, try 4 directions
 *
 * 🚨 Edge Cases:
 * - No gates → no updates
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
void WallsAndGates(vector<vector<int>>& rooms) {
    int m = rooms.size(), n = rooms[0].size();
    queue<pair<int, int>> q;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (rooms[i][j] == 0)
                q.push({i, j});

    vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                rooms[nx][ny] == INT_MAX) {
                rooms[nx][ny] = rooms[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

/**
 * Problem 6: Word Ladder (LeetCode 127)
 * --------------------------------------
 * 🧠 Description:
 * Given a beginWord, endWord, and a wordList, return the number of steps in the shortest
 * transformation sequence from beginWord to endWord. Only one letter can be changed at a time,
 * and each intermediate word must exist in the wordList.
 *
 * 🔍 Example:
 * Input:
 *   beginWord = "hit",
 *   endWord = "cog",
 *   wordList = ["hot","dot","dog","lot","log","cog"]
 * Output: 5 (hit → hot → dot → dog → cog)
 *
 * 💡 Strategy:
 * Perform BFS from beginWord, transforming one character at a time,
 * and use a visited set to avoid revisiting.
 *
 * ✨ Explanation:
 * At each level of BFS, we change one character at each position to all possible letters 'a'-'z',
 * and if the resulting word exists in the wordList and hasn't been visited, we enqueue it.
 *
 * 🔁 Transition:
 * - From current word, try all possible one-letter mutations.
 *
 * 🚨 Edge Cases:
 * - If endWord not in wordList → return 0
 * - beginWord == endWord → return 1
 *
 * ⏱ Time: O(N * L^2), 🧠 Space: O(N)
 *    where N = size of wordList, L = length of each word
 */
int LadderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0;

    queue<pair<string, int>> q;
    unordered_set<string> visited;
    q.push({beginWord, 1});
    visited.insert(beginWord);

    while (!q.empty()) {
        auto [word, steps] = q.front(); q.pop();
        if (word == endWord) return steps;

        for (size_t i = 0; i < word.length(); ++i) {
            string next = word;
            for (char c = 'a'; c <= 'z'; ++c) {
                next[i] = c;
                if (wordSet.count(next) && !visited.count(next)) {
                    visited.insert(next);
                    q.push({next, steps + 1});
                }
            }
        }
    }
    return 0;
}

/**
 * Problem 7: Binary Tree Level Order Traversal (LeetCode 102)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the level order traversal of its nodes' values.
 * (i.e., from left to right, level by level).
 *
 * 🔍 Example:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 *
 * 💡 Strategy:
 * Use a queue to traverse level-by-level using BFS.
 *
 * ✨ Explanation:
 * Enqueue the root and process nodes level by level,
 * collecting values for each layer into a vector.
 *
 * 🔁 Transition:
 * - Use queue<TreeNode*> and track current level size.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return empty vector
 *
 * ⏱ Time: O(n), 🧠 Space: O(n)
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> LevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        while (size--) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }

    return result;
}

/**
 * Problem 8: Snakes and Ladders (LeetCode 909)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a board with snakes and ladders, return the minimum number of moves to reach the end.
 * Board cells are numbered from bottom-left to top-right in a zig-zag fashion.
 *
 * 🔍 Example:
 * Input: board = [
 *   [-1,-1,-1,-1,-1,-1],
 *   [-1,-1,-1,-1,-1,-1],
 *   [-1,-1,-1,-1,-1,-1],
 *   [-1,35,-1,-1,13,-1],
 *   [-1,-1,-1,-1,-1,-1],
 *   [-1,15,-1,-1,-1,-1]
 * ]
 * Output: 4
 *
 * 💡 Strategy:
 * Use BFS to simulate all possible die rolls and landings.
 *
 * ✨ Explanation:
 * Map board positions to 2D coordinates, use queue<int> to track player position.
 *
 * 🔁 Transition:
 * - From each square, roll 1-6 and move accordingly
 * - Take ladders/snakes using board[x][y]
 *
 * 🚨 Edge Cases:
 * - Board size 1x1 → return 0
 *
 * ⏱ Time: O(N^2), 🧠 Space: O(N^2)
 */
int SnakesAndLadders(vector<vector<int>>& board) {
    int n = board.size();
    auto getRC = [&](int s) {
        int r = (s - 1) / n, c = (s - 1) % n;
        if (r % 2 == 1) c = n - 1 - c;
        return pair<int,int>{n - 1 - r, c};
    };

    vector<bool> visited(n * n + 1, false);
    queue<pair<int, int>> q;
    q.push({1, 0});
    visited[1] = true;

    while (!q.empty()) {
        auto [s, moves] = q.front(); q.pop();
        for (int i = 1; i <= 6 && s + i <= n * n; ++i) {
            int next = s + i;
            auto [r, c] = getRC(next);
            if (board[r][c] != -1)
                next = board[r][c];
            if (!visited[next]) {
                if (next == n * n) return moves + 1;
                q.push({next, moves + 1});
                visited[next] = true;
            }
        }
    }
    return -1;
}

/**
 * Problem 9: Minimum Knight Moves (LeetCode 1197)
 * ------------------------------------------------
 * 🧠 Description:
 * Given a target point (x, y), return the minimum number of knight moves
 * required to reach from (0,0) to (x,y) on an infinite chessboard.
 *
 * 🔍 Example:
 * Input: x = 2, y = 1
 * Output: 1
 *
 * 💡 Strategy:
 * Use BFS with pruning by symmetry and visited set.
 *
 * ✨ Explanation:
 * Use unordered_set for visited positions and only search in first quadrant due to symmetry.
 *
 * 🔁 Transition:
 * - Knight has 8 moves: ±(2,1) or ±(1,2)
 *
 * 🚨 Edge Cases:
 * - x == 0 and y == 0 → return 0
 *
 * ⏱ Time: O(x*y), 🧠 Space: O(x*y)
 */
int MinKnightMoves(int x, int y) {
    x = abs(x), y = abs(y);
    queue<pair<int, int>> q;
    q.push({0, 0});
    unordered_set<string> visited;
    visited.insert("0,0");

    vector<pair<int,int>> dirs = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
    int steps = 0;

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto [cx, cy] = q.front(); q.pop();
            if (cx == x && cy == y) return steps;
            for (auto [dx, dy] : dirs) {
                int nx = cx + dx, ny = cy + dy;
                if (nx >= -2 && ny >= -2 && nx <= 300 && ny <= 300) {
                    string key = to_string(nx) + "," + to_string(ny);
                    if (!visited.count(key)) {
                        visited.insert(key);
                        q.push({nx, ny});
                    }
                }
            }
        }
        ++steps;
    }
    return -1;
}

/**
 * Problem 10: 01 Matrix (LeetCode 542)
 * -------------------------------------
 * 🧠 Description:
 * Given a matrix of 0s and 1s, return a matrix where each cell contains
 * the distance to the nearest 0.
 *
 * 🔍 Example:
 * Input: mat = [
 *   [0,0,0],
 *   [0,1,0],
 *   [1,1,1]
 * ]
 * Output: [
 *   [0,0,0],
 *   [0,1,0],
 *   [1,2,1]
 * ]
 *
 * 💡 Strategy:
 * Multi-source BFS from all 0s.
 *
 * ✨ Explanation:
 * Start by enqueuing all 0s with distance 0, then expand outward.
 * Update distance for each 1 when visited.
 *
 * 🔁 Transition:
 * - Enqueue each cell as soon as it's reachable from a 0
 *
 * 🚨 Edge Cases:
 * - All 1s → return unchanged
 * - All 0s → result is all 0s
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
vector<vector<int>> UpdateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    queue<pair<int, int>> q;
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
                q.push({i, j});
            }

    vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist;
}

/**
 * Problem 11: Minimum Depth of Binary Tree (LeetCode 111)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return its minimum depth —
 * the number of nodes along the shortest path from the root node
 * down to the nearest leaf node.
 *
 * 🔍 Example:
 * Input: [3,9,20,null,null,15,7]
 * Output: 2
 *
 * 💡 Strategy:
 * Use BFS to find the first leaf node encountered — that’s the minimum depth.
 *
 * ✨ Explanation:
 * Traverse level by level, return depth as soon as a node with no children is found.
 *
 * 🔁 Transition:
 * - Enqueue root with depth = 1
 *
 * 🚨 Edge Cases:
 * - Empty tree → return 0
 *
 * ⏱ Time: O(n), 🧠 Space: O(n)
 */
int MinDepth(TreeNode* root) {
    if (!root) return 0;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 1});

    while (!q.empty()) {
        auto [node, depth] = q.front(); q.pop();
        if (!node->left && !node->right) return depth;
        if (node->left) q.push({node->left, depth + 1});
        if (node->right) q.push({node->right, depth + 1});
    }
    return 0;
}

/**
 * Problem 12: Bus Routes (LeetCode 815)
 * --------------------------------------
 * 🧠 Description:
 * You are given bus routes. Each route is a list of bus stops.
 * Return the minimum number of buses you must take to reach destination.
 *
 * 🔍 Example:
 * Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
 * Output: 2
 *
 * 💡 Strategy:
 * Build a stop → bus map, then use BFS from source stop.
 *
 * ✨ Explanation:
 * Use queue to process stops, and track visited stops + used buses.
 *
 * 🔁 Transition:
 * - For each stop, enqueue all stops reachable by unused buses.
 *
 * 🚨 Edge Cases:
 * - source == target → return 0
 * - No path → return -1
 *
 * ⏱ Time: O(N*M), 🧠 Space: O(N + M)  (N = routes, M = total stops)
 */
int NumBusesToDestination(vector<vector<int>>& routes, int source, int target) {
    if (source == target) return 0;
    unordered_map<int, vector<int>> stop_to_buses;
    for (size_t i = 0; i < routes.size(); ++i)
        for (int stop : routes[i])
            stop_to_buses[stop].push_back(i);

    queue<int> q;
    unordered_set<int> visited_stops = {source};
    unordered_set<int> used_buses;
    q.push(source);

    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        ++level;
        while (size--) {
            int curr_stop = q.front(); q.pop();
            for (int bus : stop_to_buses[curr_stop]) {
                if (used_buses.count(bus)) continue;
                used_buses.insert(bus);
                for (int stop : routes[bus]) {
                    if (stop == target) return level;
                    if (!visited_stops.count(stop)) {
                        visited_stops.insert(stop);
                        q.push(stop);
                    }
                }
            }
        }
    }
    return -1;
}

/**
 * Problem 13: Zigzag Level Order Traversal (LeetCode 103)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes’ values.
 * (i.e., left to right, then right to left for the next level, and so on).
 *
 * 🔍 Example:
 * Input: [3,9,20,null,null,15,7]
 * Output: [[3],[20,9],[15,7]]
 *
 * 💡 Strategy:
 * Perform BFS, track level number and reverse order accordingly.
 *
 * ✨ Explanation:
 * Add elements to a temporary vector, reverse it on odd-numbered levels.
 *
 * 🔁 Transition:
 * - Standard BFS with queue, toggle direction with a boolean flag.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return empty list
 *
 * ⏱ Time: O(n), 🧠 Space: O(n)
 */
vector<vector<int>> ZigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            int index = leftToRight ? i : (size - 1 - i);
            level[index] = node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        leftToRight = !leftToRight;
        result.push_back(level);
    }
    return result;
}

/**
 * Problem 14: Clone Graph (LeetCode 133) ✅ (also in DFS)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a reference of a node in a connected undirected graph,
 * return a deep copy (clone) of the graph.
 *
 * 🔍 Example:
 * Input: Node with val = 1, neighbors = [2,4]
 * Output: New graph with same structure
 *
 * 💡 Strategy:
 * Use BFS with a hashmap: original node → cloned node.
 *
 * ✨ Explanation:
 * Traverse the original graph using queue, clone each node,
 * and link cloned neighbors accordingly.
 *
 * 🔁 Transition:
 * - Use queue<Node*> and unordered_map<Node*, Node*>
 *
 * 🚨 Edge Cases:
 * - Null input → return nullptr
 *
 * ⏱ Time: O(n), 🧠 Space: O(n)
 */

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors({}) {}
    Node(int _val) : val(_val), neighbors({}) {}
};

Node* CloneGraph_BFS(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> cloned;
    queue<Node*> q;

    Node* clone = new Node(node->val);
    cloned[node] = clone;
    q.push(node);

    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        for (Node* neighbor : curr->neighbors) {
            if (!cloned.count(neighbor)) {
                cloned[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            cloned[curr]->neighbors.push_back(cloned[neighbor]);
        }
    }
    return clone;
}

/**
 * Problem 15: Perfect Squares (LeetCode 279)
 * -------------------------------------------
 * 🧠 Description:
 * Given an integer n, return the least number of perfect square numbers (1, 4, 9, ...) that sum to n.
 *
 * 🔍 Example:
 * Input: n = 12
 * Output: 3 (4 + 4 + 4)
 *
 * 💡 Strategy:
 * Use BFS to explore all subtractable square numbers layer by layer.
 *
 * ✨ Explanation:
 * Treat each number as a state. From current state x, move to x - k^2 (if valid).
 *
 * 🔁 Transition:
 * - Start from n, push all n - k^2 into queue
 *
 * 🚨 Edge Cases:
 * - n is already a perfect square → return 1
 *
 * ⏱ Time: O(n * sqrt(n)), 🧠 Space: O(n)
 */
int NumSquares(int n) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    q.push(n);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        ++level;
        while (size--) {
            int curr = q.front(); q.pop();
            for (int i = 1; i * i <= curr; ++i) {
                int next = curr - i * i;
                if (next == 0) return level;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }
    return -1;
}

/**
 * Problem 16: Sliding Puzzle (LeetCode 773)
 * ------------------------------------------
 * 🧠 Description:
 * Solve the 2x3 sliding puzzle. Return the least number of moves to reach target "123450".
 *
 * 🔍 Example:
 * Input: [[1,2,3],[4,0,5]]
 * Output: 1
 *
 * 💡 Strategy:
 * Use BFS on the board state represented as a string.
 *
 * ✨ Explanation:
 * Treat each board config as a node, find neighbors by swapping 0 with adjacent.
 *
 * 🔁 Transition:
 * - Use a map to track adjacent indices of each cell
 *
 * 🚨 Edge Cases:
 * - Already solved → return 0
 *
 * ⏱ Time: O(6!) = 720, 🧠 Space: O(720)
 */
int SlidingPuzzle(vector<vector<int>>& board) {
    string start, target = "123450";
    for (auto& row : board)
        for (int n : row) start += to_string(n);

    unordered_map<int, vector<int>> neighbors = {
        {0,{1,3}}, {1,{0,2,4}}, {2,{1,5}},
        {3,{0,4}}, {4,{1,3,5}}, {5,{2,4}}
    };

    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.push({start, 0});
    visited.insert(start);

    while (!q.empty()) {
        auto [curr, steps] = q.front(); q.pop();
        if (curr == target) return steps;

        int zero = curr.find('0');
        for (int nei : neighbors[zero]) {
            string next = curr;
            swap(next[zero], next[nei]);
            if (!visited.count(next)) {
                visited.insert(next);
                q.push({next, steps + 1});
            }
        }
    }
    return -1;
}

/**
 * Problem 17: Is Graph Bipartite? (LeetCode 785)
 * -----------------------------------------------
 * 🧠 Description:
 * Determine if a graph is bipartite (i.e., can be colored with 2 colors with no adjacent same-color nodes).
 *
 * 🔍 Example:
 * Input: [[1,3],[0,2],[1,3],[0,2]]
 * Output: true
 *
 * 💡 Strategy:
 * BFS coloring: use 0/1 to color nodes. If any adjacent has same color, return false.
 *
 * ✨ Explanation:
 * Traverse each connected component; for unvisited node, assign color and expand.
 *
 * 🔁 Transition:
 * - Use color vector initialized with -1
 *
 * 🚨 Edge Cases:
 * - Disconnected graph → check all components
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V)
 */
bool IsBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);

    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        queue<int> q;
        q.push(i);
        color[i] = 0;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nei : graph[node]) {
                if (color[nei] == -1) {
                    color[nei] = 1 - color[node];
                    q.push(nei);
                } else if (color[nei] == color[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Problem 18: Cheapest Flights Within K Stops (LeetCode 787)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Find the cheapest price from src to dst with at most K stops using given flight list.
 *
 * 🔍 Example:
 * Input: n = 4, flights = [[0,1,100],[1,2,100],[2,3,100],[0,3,500]], src = 0, dst = 3, k = 1
 * Output: 500
 *
 * 💡 Strategy:
 * Modified BFS (or Dijkstra) with state = (city, cost, stops).
 *
 * ✨ Explanation:
 * Use a queue and prune paths with more than K + 1 levels.
 *
 * 🔁 Transition:
 * - From each node, visit all neighbors and track accumulated cost and stops.
 *
 * 🚨 Edge Cases:
 * - No path → return -1
 *
 * ⏱ Time: O(V + E), 🧠 Space: O(V)
 */
int FindCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    unordered_map<int, vector<pair<int, int>>> graph;
    for (auto& f : flights)
        graph[f[0]].emplace_back(f[1], f[2]);

    queue<tuple<int, int, int>> q; // (node, cost, stops)
    q.push({src, 0, 0});
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    while (!q.empty()) {
        auto [u, cost, stops] = q.front(); q.pop();
        if (stops > k) continue;
        for (auto& [v, price] : graph[u]) {
            if (cost + price < dist[v]) {
                dist[v] = cost + price;
                q.push({v, dist[v], stops + 1});
            }
        }
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

/**
 * Problem 19: Shortest Bridge (LeetCode 934)
 * -------------------------------------------
 * 🧠 Description:
 * Given a binary grid with exactly two islands, return the minimum number of 0s to flip
 * to connect the islands (i.e., build a bridge).
 *
 * 🔍 Example:
 * Input: [[0,1],[1,0]]
 * Output: 1
 *
 * 💡 Strategy:
 * 1. DFS to mark the first island.
 * 2. BFS from that island's boundary to reach the second island.
 *
 * ✨ Explanation:
 * Start BFS from all 1s of the first island and expand into water (0) until hitting another 1.
 *
 * 🔁 Transition:
 * - Layer-by-layer BFS expansion
 *
 * 🚨 Edge Cases:
 * - No bridge needed (adjacent islands) → return 1
 *
 * ⏱ Time: O(n^2), 🧠 Space: O(n^2)
 */
void DfsMarkIsland(vector<vector<int>>& grid, int i, int j, queue<pair<int, int>>& q) {
    if (i < 0 || j < 0 || static_cast<size_t>(i) >= grid.size() || static_cast<size_t>(j) >= grid[0].size() || grid[i][j] != 1) return;
    grid[i][j] = 2;
    q.push({i, j});
    DfsMarkIsland(grid, i + 1, j, q);
    DfsMarkIsland(grid, i - 1, j, q);
    DfsMarkIsland(grid, i, j + 1, q);
    DfsMarkIsland(grid, i, j - 1, q);
}

int ShortestBridge(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    bool found = false;

    for (int i = 0; i < m && !found; ++i) {
        for (int j = 0; j < n && !found; ++j) {
            if (grid[i][j] == 1) {
                DfsMarkIsland(grid, i, j, q);
                found = true;
            }
        }
    }

    vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    int steps = 0;
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    if (grid[nx][ny] == 1) return steps;
                    if (grid[nx][ny] == 0) {
                        grid[nx][ny] = 2;
                        q.push({nx, ny});
                    }
                }
            }
        }
        ++steps;
    }
    return -1;
}

/**
 * Problem 20: The Maze (LeetCode 490)
 * ------------------------------------
 * 🧠 Description:
 * Given a ball in a maze, determine if it can reach the destination.
 * The ball rolls in 4 directions until hitting a wall.
 *
 * 🔍 Example:
 * Input: maze = [[0,0,1,0],[0,0,0,0],[0,0,0,1],[1,1,0,0]], start = [0,0], dest = [3,3]
 * Output: true
 *
 * 💡 Strategy:
 * BFS with special rolling rule: roll until wall then enqueue.
 *
 * ✨ Explanation:
 * Use queue to simulate rolling the ball; mark visited stops.
 *
 * 🔁 Transition:
 * - Keep rolling in a direction until hitting wall, then enqueue
 *
 * 🚨 Edge Cases:
 * - Start == dest → return true
 *
 * ⏱ Time: O(m * n), 🧠 Space: O(m * n)
 */
bool HasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({start[0], start[1]});
    visited[start[0]][start[1]] = true;

    vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == dest[0] && y == dest[1]) return true;

        for (auto [dx, dy] : dirs) {
            int nx = x, ny = y;
            while (nx + dx >= 0 && nx + dx < m && ny + dy >= 0 && ny + dy < n &&
                   maze[nx + dx][ny + dy] == 0) {
                nx += dx;
                ny += dy;
            }
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return false;
}


int main() {
    // Problem 1: Number of Islands (BFS)
    vector<vector<char>> grid1 = {
        {'1','1','0','0'},
        {'1','1','0','0'},
        {'0','0','1','0'},
        {'0','0','0','1'}
    };
    cout << "Problem 1: " << NumIslands_BFS(grid1) << endl;

    // Problem 2: Shortest Path in Binary Matrix
    vector<vector<int>> grid2 = {{0,1},{1,0}};
    cout << "Problem 2: " << ShortestPathBinaryMatrix(grid2) << endl;

    // Problem 3: Rotting Oranges
    vector<vector<int>> grid3 = {
        {2,1,1},{1,1,0},{0,1,1}
    };
    cout << "Problem 3: " << OrangesRotting_BFS(grid3) << endl;

    // Problem 4: Open the Lock
    vector<string> deadends4 = {"0201","0101","0102","1212","2002"};
    string target4 = "0202";
    cout << "Problem 4: " << OpenLock(deadends4, target4) << endl;

    // Problem 5: Walls and Gates
    vector<vector<int>> rooms5 = {
        {INT_MAX,-1,0,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,-1},
        {INT_MAX,-1,INT_MAX,-1},
        {0,-1,INT_MAX,INT_MAX}
    };
    WallsAndGates(rooms5);
    cout << "Problem 5: Updated rooms (printed manually)." << endl;

    // Problem 6: Word Ladder
    vector<string> wordList6 = {"hot","dot","dog","lot","log","cog"};
    cout << "Problem 6: " << LadderLength("hit", "cog", wordList6) << endl;

    // Problem 7: Level Order Traversal
    TreeNode* root7 = new TreeNode(3);
    root7->left = new TreeNode(9);
    root7->right = new TreeNode(20);
    root7->right->left = new TreeNode(15);
    root7->right->right = new TreeNode(7);
    auto levels7 = LevelOrder(root7);
    cout << "Problem 7: Level count = " << levels7.size() << endl;

    // Problem 8: Snakes and Ladders
    vector<vector<int>> board8 = {
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,35,-1,-1,13,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,15,-1,-1,-1,-1}
    };
    cout << "Problem 8: " << SnakesAndLadders(board8) << endl;

    // Problem 9: Minimum Knight Moves
    cout << "Problem 9: " << MinKnightMoves(2, 1) << endl;

    // Problem 10: 01 Matrix
    vector<vector<int>> mat10 = {
        {0,0,0},{0,1,0},{1,1,1}
    };
    auto res10 = UpdateMatrix(mat10);
    cout << "Problem 10: Distance at (2,1) = " << res10[2][1] << endl;

    // Problem 11: Minimum Depth of Binary Tree
    TreeNode* root11 = new TreeNode(1);
    root11->left = new TreeNode(2);
    cout << "Problem 11: " << MinDepth(root11) << endl;

    // Problem 12: Bus Routes
    vector<vector<int>> routes12 = {{1,2,7},{3,6,7}};
    cout << "Problem 12: " << NumBusesToDestination(routes12, 1, 6) << endl;

    // Problem 13: Zigzag Level Order
    auto zigzag13 = ZigzagLevelOrder(root7);
    cout << "Problem 13: Zigzag levels = " << zigzag13.size() << endl;

    // Problem 14: Clone Graph
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3);
    Node* d = new Node(4);
    a->neighbors = {b, d};
    b->neighbors = {a, c};
    c->neighbors = {b, d};
    d->neighbors = {a, c};
    auto cloned14 = CloneGraph_BFS(a);
    cout << "Problem 14: Cloned value = " << (cloned14 ? cloned14->val : -1) << endl;

    // Problem 15: Perfect Squares
    cout << "Problem 15: " << NumSquares(12) << endl;

    // Problem 16: Sliding Puzzle
    vector<vector<int>> puzzle16 = {{1,2,3},{4,0,5}};
    cout << "Problem 16: " << SlidingPuzzle(puzzle16) << endl;

    // Problem 17: Is Graph Bipartite
    vector<vector<int>> graph17 = {{1,3},{0,2},{1,3},{0,2}};
    cout << "Problem 17: " << (IsBipartite(graph17) ? "true" : "false") << endl;

    // Problem 18: Cheapest Flights with K Stops
    vector<vector<int>> flights18 = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout << "Problem 18: " << FindCheapestPrice(4, flights18, 0, 3, 1) << endl;

    // Problem 19: Shortest Bridge
    vector<vector<int>> grid19 = {
        {0,1,0},{0,0,0},{0,0,1}
    };
    cout << "Problem 19: " << ShortestBridge(grid19) << endl;

    // Problem 20: Maze
    vector<vector<int>> maze20 = {
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,1,0},
        {1,1,0,1,1},
        {0,0,0,0,0}
    };
    vector<int> start20 = {0,4}, dest20 = {4,4};
    cout << "Problem 20: " << (HasPath(maze20, start20, dest20) ? "true" : "false") << endl;

    return 0;
}
