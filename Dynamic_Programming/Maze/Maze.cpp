#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * Problem: Maze Paths (DFS and DP with Path Details)
 *
 * Description:
 * - Given a 2D maze where 1 represents a valid cell and 0 represents a blocked cell,
 *   find all possible paths from the top-left corner to the bottom-right corner using DFS.
 * - Additionally, calculate the total number of unique paths using dynamic programming (DP),
 *   and print the specific path details for each valid path.
 */

// DFS to find all paths and print their specific coordinates
void dfsMaze(vector<vector<int>>& maze, int x, int y, string path, vector<string>& allPaths) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Out of bounds or invalid cell
    if (x < 0 || y < 0 || x >= rows || y >= cols || maze[x][y] == 0) {
        return;
    }

    // Append current cell to the path
    if (!path.empty()) {
        path += " -> ";
    }
    path += "[" + to_string(x) + ", " + to_string(y) + "]";

    // If the bottom-right corner is reached, store the path and backtrack
    if (x == rows - 1 && y == cols - 1) {
        allPaths.push_back(path);
        return;
    }

    // Mark the current cell as visited
    maze[x][y] = 0;

    // Explore all four directions
    dfsMaze(maze, x - 1, y, path, allPaths); // Up
    dfsMaze(maze, x + 1, y, path, allPaths); // Down
    dfsMaze(maze, x, y - 1, path, allPaths); // Left
    dfsMaze(maze, x, y + 1, path, allPaths); // Right

    // Unmark the current cell for backtracking
    maze[x][y] = 1;
}

// DP to count paths and print specific path details
vector<string> findPathsInMazeDP(vector<vector<int>>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    // If the maze is empty or the starting point is blocked, return an empty result
    if (rows == 0 || cols == 0 || maze[0][0] == 0) return {};

    // DP table to store paths
    vector<vector<vector<string>>> dp(rows, vector<vector<string>>(cols));

    // Initialize the starting cell
    dp[0][0] = {"[0, 0]"};

    // Fill the first column
    for (int i = 1; i < rows; ++i) {
        if (maze[i][0] == 1 && !dp[i - 1][0].empty()) {
            for (const auto& path : dp[i - 1][0]) {
                dp[i][0].push_back(path + " -> [" + to_string(i) + ", 0]");
            }
        }
    }

    // Fill the first row
    for (int j = 1; j < cols; ++j) {
        if (maze[0][j] == 1 && !dp[0][j - 1].empty()) {
            for (const auto& path : dp[0][j - 1]) {
                dp[0][j].push_back(path + " -> [0, " + to_string(j) + "]");
            }
        }
    }

    // Fill the rest of the DP table
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (maze[i][j] == 1) {
                // Paths from the top cell
                for (const auto& path : dp[i - 1][j]) {
                    dp[i][j].push_back(path + " -> [" + to_string(i) + ", " + to_string(j) + "]");
                }
                // Paths from the left cell
                for (const auto& path : dp[i][j - 1]) {
                    dp[i][j].push_back(path + " -> [" + to_string(i) + ", " + to_string(j) + "]");
                }
            }
        }
    }

    // Return all paths to the bottom-right corner
    return dp[rows - 1][cols - 1];
}

int main() {
    // Maze grid: 1 represents a valid cell, 0 represents a blocked cell
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    // DFS to find all possible paths with formatted strings
    vector<string> dfsPaths;
    dfsMaze(maze, 0, 0, "", dfsPaths);

    // Output DFS paths
    cout << "All possible paths (DFS):" << endl;
    for (const auto& path : dfsPaths) {
        cout << path << endl;
    }

    // DP to find paths and print their details
    cout << "All unique paths (DP):" << endl;
    vector<string> dpPaths = findPathsInMazeDP(maze);
    for (const auto& path : dpPaths) {
        cout << path << endl;
    }

    return 0;
}
