#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Problem 1: Binary Tree Preorder Traversal (Non-Recursive) (LC 144)
 * Description:
 * Given the root of a binary tree, return its preorder traversal (root-left-right) without recursion.
 * Example:
 * Input: root = [1,null,2,3]
 * Output: [1,2,3]
 */
vector<int> PreorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();
        result.push_back(node->val);
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }
    return result;
}

/**
 * Problem 2: Binary Tree Inorder Traversal (Non-Recursive) (LC 94)
 * Description:
 * Given the root of a binary tree, return its inorder traversal (left-root-right) without recursion.
 * Example:
 * Input: root = [1,null,2,3]
 * Output: [1,3,2]
 */
vector<int> InorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    while (curr || !stk.empty()) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    return result;
}

/**
 * Problem 3: Binary Tree Postorder Traversal (Non-Recursive) (LC 145)
 * Description:
 * Given the root of a binary tree, return its postorder traversal (left-right-root) without recursion.
 * Example:
 * Input: root = [1,null,2,3]
 * Output: [3,2,1]
 */
vector<int> PostorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> stk1, stk2;
    stk1.push(root);
    while (!stk1.empty()) {
        TreeNode* node = stk1.top();
        stk1.pop();
        stk2.push(node);
        if (node->left) stk1.push(node->left);
        if (node->right) stk1.push(node->right);
    }
    while (!stk2.empty()) {
        result.push_back(stk2.top()->val);
        stk2.pop();
    }
    return result;
}

/**
 * Problem 4: Binary Tree Level Order Traversal (BFS) (LC 102)
 * Description:
 * Given the root of a binary tree, return the level order traversal of its nodes' values.
 * Example:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 */
vector<vector<int>> LevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

/**
 * Problem 5: Evaluate Reverse Polish Notation (LC 150)
 * Description:
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * Example:
 * Input: tokens = ["2", "1", "+", "3", "*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9
 */
int EvalRPN(vector<string>& tokens) {
    stack<int> stk;
    for (string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();
            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else if (token == "/") stk.push(a / b);
        } else {
            stk.push(stoi(token));
        }
    }
    return stk.top();
}

/**
 * Problem 6: Basic Calculator II (LC 227)
 * Description:
 * Given a string s which represents an expression, evaluate the expression and return its value.
 * Example:
 * Input: s = "3+2*2"
 * Output: 7
 */
int Calculate(string s) {
    stack<int> stk;
    int num = 0;
    char sign = '+';
    for (size_t i = 0; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        }
        if ((!isdigit(s[i]) && s[i] != ' ') || (static_cast<size_t>(i) == s.size() - 1)) {
            if (sign == '+') stk.push(num);
            else if (sign == '-') stk.push(-num);
            else if (sign == '*') {
                int top = stk.top(); stk.pop();
                stk.push(top * num);
            } else if (sign == '/') {
                int top = stk.top(); stk.pop();
                stk.push(top / num);
            }
            sign = s[i];
            num = 0;
        }
    }
    int result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    return result;
}

/**
 * Problem 7: Rotten Oranges (LC 994)
 * Description:
 * Given a 2D grid where 0 represents empty, 1 represents fresh oranges, and 2 represents rotten oranges, 
 * return the minimum time required to rot all oranges. If it is impossible, return -1.
 * Example:
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 */
int OrangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int, int>> q;
    int fresh_count = 0, minutes = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 2) {
                q.push({r, c});
            } else if (grid[r][c] == 1) {
                fresh_count++;
            }
        }
    }

    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty() && fresh_count > 0) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            auto [r, c] = q.front();
            q.pop();
            for (auto [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    q.push({nr, nc});
                    fresh_count--;
                }
            }
        }
        minutes++;
    }
    return fresh_count == 0 ? minutes : -1;
}

/**
 * Problem 8: Course Schedule II (LC 210)
 * Description:
 * There are a total of `num_courses` courses to take. Some courses may have prerequisites, where prerequisites[i] = [ai, bi] 
 * indicates that you must take course `bi` before course `ai`. Return a list of courses in a valid order to finish all.
 *
 * Example:
 * Input: num_courses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,2,1,3] or [0,1,2,3]
 */
vector<int> FindOrder(int num_courses, vector<vector<int>>& prerequisites) {
    vector<int> indegree(num_courses, 0);
    vector<vector<int>> graph(num_courses);
    vector<int> result;

    for (const auto& p : prerequisites) {
        graph[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < num_courses; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int course = q.front();
        q.pop();
        result.push_back(course);

        for (int next : graph[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return result.size() == static_cast<size_t>(num_courses) ? result : vector<int>();
}

/**
 * Problem 9: Open the Lock (LC 752)
 * Description:
 * Given a lock represented by a string of four digits, you start at "0000". You are given a list of deadends, 
 * representing combinations that cannot be used. Return the minimum number of turns to open the lock, or -1 if impossible.
 *
 * Example:
 * Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 * Output: 6
 */
int OpenLock(vector<string>& deadends, string target) {
    unordered_set<string> dead(deadends.begin(), deadends.end());
    unordered_set<string> visited;
    queue<pair<string, int>> q;

    if (dead.count("0000")) return -1;

    q.push({"0000", 0});
    visited.insert("0000");

    while (!q.empty()) {
        auto [current, turns] = q.front();
        q.pop();

        if (current == target) return turns;

        for (int i = 0; i < 4; ++i) {
            string up = current;
            string down = current;

            up[i] = (up[i] - '0' + 1) % 10 + '0';
            down[i] = (down[i] - '0' + 9) % 10 + '0';

            if (!dead.count(up) && !visited.count(up)) {
                q.push({up, turns + 1});
                visited.insert(up);
            }
            if (!dead.count(down) && !visited.count(down)) {
                q.push({down, turns + 1});
                visited.insert(down);
            }
        }
    }

    return -1;
}

/**
 * Problem 10: Number of Islands (LC 200)
 * Description:
 * Given a 2D grid of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water 
 * and is formed by connecting adjacent lands horizontally or vertically.
 *
 * Example:
 * Input: grid = [
 *   ["1","1","1","1","0"],
 *   ["1","1","0","1","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","0","0","0"]
 * ]
 * Output: 1
 */
int NumIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    auto bfs = [&](int r, int c) {
        queue<pair<int, int>> q;
        q.push({r, c});
        grid[r][c] = '0';

        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) {
                int nr = row + dr;
                int nc = col + dc;

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                    q.push({nr, nc});
                    grid[nr][nc] = '0';
                }
            }
        }
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '1') {
                count++;
                bfs(r, c);
            }
        }
    }

    return count;
}

int main() {
    // Test Binary Tree Traversals
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> pre = PreorderTraversal(root);
    vector<int> in = InorderTraversal(root);
    vector<int> post = PostorderTraversal(root);
    vector<vector<int>> level = LevelOrder(root);

    cout << "Preorder Traversal: ";
    for (int val : pre) cout << val << " ";
    cout << endl;

    cout << "Inorder Traversal: ";
    for (int val : in) cout << val << " ";
    cout << endl;

    cout << "Postorder Traversal: ";
    for (int val : post) cout << val << " ";
    cout << endl;

    cout << "Level Order Traversal: ";
    for (auto& l : level) {
        for (int val : l) cout << val << " ";
        cout << endl;
    }

    // Test Evaluate Reverse Polish Notation
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << "Evaluate RPN: " << EvalRPN(tokens) << endl;

    // Test Basic Calculator II
    string expr = "3+2*2";
    cout << "Basic Calculator II Result: " << Calculate(expr) << endl;

    // Test Rotten Oranges
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << "Rotten Oranges Minimum Time: " << OrangesRotting(grid) << endl;

    // Test Problem 8: Course Schedule II
    vector<vector<int>> prerequisites1 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    int num_courses1 = 4;
    vector<int> order = FindOrder(num_courses1, prerequisites1);
    cout << "Course Schedule II Order: ";
    for (int course : order) cout << course << " ";
    cout << endl;

    // Test Problem 9: Open the Lock
    vector<string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    string target = "0202";
    cout << "Open Lock Minimum Turns: " << OpenLock(deadends, target) << endl;

    // Test Problem 10: Number of Islands
    vector<vector<char>> grid_10 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << "Number of Islands: " << NumIslands(grid_10) << endl;

    return 0;
}
