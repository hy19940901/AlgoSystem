#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
/**
 * Problem: Max Area of Island (LC 695)
 * ------------------------------------
 * Description:
 * Given a 2D grid of 0's and 1's, where 1 represents land and 0 represents water, 
 * an island is formed by connecting adjacent lands horizontally or vertically.
 * Find the maximum area of an island in the given grid. If there is no island, return 0.
 *
 * Example:
 * Input: grid = [[0,0,1,0,0],
 *                [0,1,1,1,0],
 *                [0,0,1,0,0],
 *                [1,1,0,0,0]]
 * Output: 5
 *
 * Approach: DFS (Depth-First Search)
 * - For each cell (i, j) in the grid:
 *   - If grid[i][j] == 1, start a DFS to explore the connected component (the island).
 *   - In DFS:
 *     - Mark the cell as visited by setting grid[i][j] = 0.
 *     - Recursively check all 4 directions (up, down, left, right).
 *     - Accumulate the size of the current island.
 * - Track and update the maximum island area during traversal.
 *
 * Time Complexity: O(m * n) — each cell is visited at most once
 * Space Complexity: O(m * n) — recursion stack in worst case
 */

// Normal function-based DFS
int dfs(vector<vector<int>>& grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0)
        return 0;
    
    grid[i][j] = 0; // Mark as visited
    int area = 1;
    area += dfs(grid, i + 1, j);
    area += dfs(grid, i - 1, j);
    area += dfs(grid, i, j + 1);
    area += dfs(grid, i, j - 1);
    return area;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = 0;
    int m = grid.size();
    int n = grid[0].size();
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                maxArea = max(maxArea, dfs(grid, i, j));
            }
        }
    }
    return maxArea;
}

/**
 *
 * Approach: Iterative DFS using Stack
 * - For each cell (i, j) in the grid:
 *   - If grid[i][j] == 1, start an iterative DFS using a stack to explore the island.
 *   - Push the starting cell into the stack.
 *   - While the stack is not empty:
 *     - Pop the top cell, mark it as visited, and expand into its 4 neighbors.
 *   - Accumulate the area of the island.
 * - Track and update the maximum island area during traversal.
 *
 * Time Complexity: O(m * n) — each cell is visited at most once
 * Space Complexity: O(m * n) — stack space in worst case
 */

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = 0;
    int m = grid.size();
    int n = grid[0].size();
    stack<pair<int, int>> stk;
    
    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                int area = 0;
                stk.push({i, j});
                grid[i][j] = 0; // Mark as visited immediately after pushing

                while (!stk.empty()) {
                    auto [x, y] = stk.top();
                    stk.pop();
                    area++;

                    for (auto& dir : directions) {
                        int nx = x + dir.first;
                        int ny = y + dir.second;
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                            stk.push({nx, ny});
                            grid[nx][ny] = 0; // Mark as visited immediately after pushing
                        }
                    }
                }
                maxArea = max(maxArea, area);
            }
        }
    }
    return maxArea;
}

/**
 *
 * Approach: BFS (Breadth-First Search)
 * - For each cell (i, j) in the grid:
 *   - If grid[i][j] == 1, start a BFS to explore the connected component (the island).
 *   - In BFS:
 *     - Use a queue to store the current cells to visit.
 *     - Mark visited cells by setting grid[i][j] = 0.
 *     - Explore all 4 directions (up, down, left, right) for each cell.
 *     - Count the size of the current island.
 * - Track and update the maximum island area during traversal.
 *
 * Time Complexity: O(m * n) — each cell is visited at most once
 * Space Complexity: O(m * n) — queue space in worst case
 */
int maxAreaOfIsland_BFS(vector<vector<int>>& grid) {
    int maxArea = 0;
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    
    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                grid[i][j] = 0;
                q.push({i, j});
                int area = 0;
                
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    area++;
                    
                    for (auto& dir : directions) {
                        int nx = x + dir.first;
                        int ny = y + dir.second;
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                            grid[nx][ny] = 0;
                            q.push({nx, ny});
                        }
                    }
                }
                maxArea = max(maxArea, area);
            }
        }
    }
    return maxArea;
}

/**
 * Problem: Move Zeroes (LC 283)
 * -----------------------------
 * Description:
 * Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
 * You must do this in-place without making a copy of the array.
 *
 * Example:
 * Input: nums = [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 *
 * Approach: Two Pointers
 * - Maintain a pointer `insertPos` to track the position where the next non-zero should be placed.
 * - Iterate through the array:
 *   - If the current element is non-zero, assign it to nums[insertPos] and increment insertPos.
 * - After all non-zeros are moved to the front, fill the rest of the array with 0's starting from insertPos.
 *
 * Time Complexity: O(n) — single pass through the array
 * Space Complexity: O(1) — in-place modification
 */
void moveZeroes(vector<int>& nums) {
    int insertPos = 0;
    for (int num : nums) {
        if (num != 0) {
            nums[insertPos++] = num;
        }
    }
    while (insertPos < nums.size()) {
        nums[insertPos++] = 0;
    }
}
