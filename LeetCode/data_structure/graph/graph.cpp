#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <numeric>
using namespace std;

/**
 * Depth-First Search (DFS)
 * Explores the graph by going as deep as possible before backtracking.
 * Useful for solving connectivity problems and graph traversals.
 *
 * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V) due to the recursion stack.
 *
 * @param graph Adjacency list representation of the graph
 * @param node Current node being visited
 * @param visited Vector to track visited nodes
 */
void DepthFirstSearch(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DepthFirstSearch(graph, neighbor, visited);
        }
    }
}

/**
 * Breadth-First Search (BFS)
 * Explores the graph level by level using a queue.
 * Useful for finding shortest paths in unweighted graphs.
 *
 * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V) due to the queue and visited array.
 *
 * @param graph Adjacency list representation of the graph
 * @param start Starting node for BFS traversal
 */
void BreadthFirstSearch(vector<vector<int>>& graph, int start) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

/**
 * Dijkstra's Algorithm - Single Source Shortest Path
 * Finds the shortest paths from the source node to all other nodes in a graph with non-negative weights.
 *
 * Time Complexity: O((V + E) log V), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V), storing the distance vector and priority queue.
 *
 * @param start Starting node
 * @param n Number of nodes in the graph
 * @param graph Adjacency list representation with (neighbor, weight) pairs
 * @return Vector of shortest distances from start node
 */
vector<int> DijkstraShortestPath(int start, int n, vector<vector<pair<int, int>>>& graph) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

/**
 * Bellman-Ford Algorithm - Single Source Shortest Path
 * Handles graphs with negative weights and can detect negative weight cycles.
 *
 * Time Complexity: O(VE), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V), storing the distance vector.
 *
 * @param start Starting node
 * @param n Number of nodes in the graph
 * @param edges List of directed edges with weights
 * @return Vector of shortest distances from start node
 */
vector<int> BellmanFordShortestPath(int start, int n, vector<tuple<int, int, int>>& edges) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    return dist;
}

/**
 * Floyd-Warshall Algorithm - All-Pairs Shortest Path
 * This algorithm finds the shortest paths between all pairs of vertices in a weighted graph.
 * It works by considering each possible intermediate vertex and updating the shortest paths accordingly.
 *
 * Time Complexity: O(V^3), where V is the number of vertices.
 * Space Complexity: O(V^2), since we store all-pair distances.
 *
 * @param n Number of vertices in the graph
 * @param adj Adjacency matrix representation of the graph, where adj[i][j] is the weight of edge i -> j
 * @return Matrix of shortest distances between all pairs of vertices
 */
vector<vector<int>> FloydWarshallShortestPaths(int n, vector<vector<int>>& adj) {
    vector<vector<int>> dist = adj;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

/**
 * Kruskal's Algorithm - Minimum Spanning Tree (MST)
 * This algorithm finds the MST of a weighted, undirected graph.
 * It uses the greedy method to select the smallest edge that does not form a cycle.
 *
 * Steps:
 * 1. Sort all edges by weight.
 * 2. Initialize a Disjoint Set Union (DSU) to keep track of connected components.
 * 3. Iterate through the edges and add them to the MST if they do not form a cycle.
 *
 * Time Complexity: O(E log E), where E is the number of edges (due to sorting).
 * Space Complexity: O(V), where V is the number of vertices (for DSU storage).
 */
struct DisjointSetUnion {
    vector<int> parent, rank;
    DisjointSetUnion(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int Find(int x) { return parent[x] == x ? x : parent[x] = Find(parent[x]); }
    bool Unite(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) return false;
        if (rank[x] > rank[y]) swap(x, y);
        parent[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
        return true;
    }
};
int KruskalMinimumSpanningTree(int n, vector<tuple<int, int, int>>& edges) {
    sort(edges.begin(), edges.end());
    DisjointSetUnion dsu(n);
    int total_cost = 0;
    for (auto [w, u, v] : edges)
        if (dsu.Unite(u, v))
            total_cost += w;
    return total_cost;
}

/**
 * Topological Sorting - Kahn's Algorithm (BFS-based)
 * Orders vertices in a Directed Acyclic Graph (DAG).
 * Useful for scheduling tasks or resolving dependencies.
 *
 * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V), storing in-degree and queue.
 *
 * @param num_vertices Number of vertices in the graph
 * @param graph Adjacency list representation of the graph
 * @return A vector containing the topological order
 */
vector<int> TopologicalSort(int num_vertices, vector<vector<int>>& graph) {
    vector<int> in_degree(num_vertices, 0);
    for (const auto& edges : graph) {
        for (int v : edges) {
            in_degree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < num_vertices; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (int neighbor : graph[node]) {
            if (--in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return (order.size() == static_cast<size_t>(num_vertices)) ? order : vector<int>();
}

/**
 * Prim's Algorithm - Minimum Spanning Tree (MST)
 * This algorithm finds the MST using a priority queue (min-heap).
 * It starts from an arbitrary node and greedily selects the smallest edge that connects to an unvisited node.
 *
 * Steps:
 * 1. Start with an arbitrary node and initialize a min-heap.
 * 2. At each step, extract the minimum weight edge and add its endpoint to the MST.
 * 3. Continue until all vertices are included.
 *
 * Time Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
 * Space Complexity: O(V + E), to store the graph and min-heap.
 */
int PrimMinimumSpanningTree(int n, vector<vector<pair<int, int>>>& graph) {
    vector<bool> in_mst(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0}); // {weight, vertex}
    int total_cost = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top(); pq.pop();
        if (in_mst[u]) continue;

        in_mst[u] = true;
        total_cost += weight;

        for (auto [v, w] : graph[u]) {
            if (!in_mst[v]) {
                pq.push({w, v});
            }
        }
    }
    return total_cost;
}

/**
 * Problem 1: Number of Islands (LC 200)
 * Description:
 * Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * Example:
 * Input: grid = [
 *   ['1', '1', '0', '0', '0'],
 *   ['1', '1', '0', '0', '0'],
 *   ['0', '0', '1', '0', '0'],
 *   ['0', '0', '0', '1', '1']
 * ]
 * Output: 3
 */

void Dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || static_cast<size_t>(i) >= grid.size() || j < 0 || static_cast<size_t>(j) >= grid[0].size() || grid[i][j] == '0') {
        return;
    }
    grid[i][j] = '0';
    Dfs(grid, i + 1, j);
    Dfs(grid, i - 1, j);
    Dfs(grid, i, j + 1);
    Dfs(grid, i, j - 1);
}

int NumIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '1') {
                ++count;
                Dfs(grid, i, j);
            }
        }
    }
    return count;
}

/**
 * Problem 2: Clone Graph (LC 133)
 * Description:
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 * Each node in the graph contains a val and a list of its neighbors.
 * Example:
 * Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
 * Output: [[2,4],[1,3],[2,4],[1,3]]
 */
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors(vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(vector<Node*>()) {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

unordered_map<Node*, Node*> visited;

Node* CloneGraph(Node* node) {
    if (!node) return nullptr;
    if (visited.count(node)) return visited[node];

    Node* clone = new Node(node->val);
    visited[node] = clone;
    for (Node* neighbor : node->neighbors) {
        clone->neighbors.push_back(CloneGraph(neighbor));
    }
    return clone;
}

/**
 * Problem 3: Course Schedule (LC 207)
 * Description:
 * There are a total of num_courses courses you have to take, labeled from 0 to num_courses-1.
 * Prerequisites are represented as a 2D array. Determine if you can finish all courses.
 * Example:
 * Input: num_courses = 2, prerequisites = [[1, 0]]
 * Output: true
 */
bool CanFinish(int num_courses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(num_courses);
    vector<int> in_degree(num_courses, 0);
    for (const auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        in_degree[pre[0]]++;
    }

    queue<int> q;
    for (size_t i = 0; i < static_cast<size_t>(num_courses); ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    int count = 0;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        ++count;
        for (int neighbor : graph[course]) {
            if (--in_degree[neighbor] == 0) q.push(neighbor);
        }
    }
    return count == num_courses;
}

/**
 * Problem 4: Course Schedule II (LC 210)
 * Description:
 * Return the ordering of courses you should take to finish all courses.
 * Example:
 * Input: num_courses = 4, prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]]
 * Output: [0, 1, 2, 3] or [0, 2, 1, 3]
 */
vector<int> FindOrder(int num_courses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(num_courses);
    vector<int> in_degree(num_courses, 0);
    for (const auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        in_degree[pre[0]]++;
    }

    queue<int> q;
    for (size_t i = 0; i < static_cast<size_t>(num_courses); ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        order.push_back(course);
        for (int neighbor : graph[course]) {
            if (--in_degree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (order.size() == static_cast<size_t>(num_courses)) return order;
    return {};
}

/**
 * Problem 5: Network Delay Time (LC 743)
 * Description:
 * There are N network nodes, and each node is labeled 1 to N. Times[i] = (u, v, w) represents a directed edge
 * from node u to node v with time cost w. Return the time it takes for all nodes to receive the signal.
 * Example:
 * Input: times = [[2, 1, 1], [2, 3, 1], [3, 4, 1]], n = 4, k = 2
 * Output: 2
 */
int NetworkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> graph(n + 1);
    for (const auto& time : times) {
        graph[time[0]].emplace_back(time[1], time[2]);
    }

    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, k);

    while (!pq.empty()) {
        auto [time, node] = pq.top();
        pq.pop();

        if (time > dist[node]) continue;

        for (const auto& [neighbor, weight] : graph[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }

    int max_time = *max_element(dist.begin() + 1, dist.end());
    return max_time == INT_MAX ? -1 : max_time;
}

/**
 * Problem 6: Word Ladder (LC 127)
 * Description:
 * Given two words (beginWord and endWord), and a dictionary's word list, return the length of the shortest transformation sequence
 * from beginWord to endWord, such that only one letter can be changed at a time and each transformed word must exist in the word list.
 * Example:
 * Input: beginWord = "hit", endWord = "cog", wordList = ["hot", "dot", "dog", "lot", "log", "cog"]
 * Output: 5
 */
int LadderLength(string begin_word, string end_word, vector<string>& word_list) {
    unordered_set<string> word_set(word_list.begin(), word_list.end());
    if (word_set.find(end_word) == word_set.end()) return 0;

    queue<pair<string, int>> q;
    q.push({begin_word, 1});

    while (!q.empty()) {
        auto [word, steps] = q.front();
        q.pop();

        if (word == end_word) return steps;

        for (size_t i = 0; i < word.size(); ++i) {
            string new_word = word;
            for (char c = 'a'; c <= 'z'; ++c) {
                new_word[i] = c;
                if (word_set.find(new_word) != word_set.end()) {
                    q.push({new_word, steps + 1});
                    word_set.erase(new_word);
                }
            }
        }
    }

    return 0;
}

/**
 * Problem 7: Critical Connections in a Network (LC 1192)
 * Description:
 * Find all critical connections in the network, such that removing any of them will disconnect the network.
 * Example:
 * Input: n = 4, connections = [[0, 1], [1, 2], [2, 0], [1, 3]]
 * Output: [[1, 3]]
 */
void Dfs(int node, int parent, int& time, vector<int>& disc, vector<int>& low, vector<vector<int>>& graph, vector<vector<int>>& result) {
    disc[node] = low[node] = ++time;
    for (int neighbor : graph[node]) {
        if (neighbor == parent) continue;
        if (disc[neighbor] == -1) {
            Dfs(neighbor, node, time, disc, low, graph, result);
            low[node] = min(low[node], low[neighbor]);
            if (low[neighbor] > disc[node]) {
                result.push_back({node, neighbor});
            }
        } else {
            low[node] = min(low[node], disc[neighbor]);
        }
    }
}

vector<vector<int>> CriticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    for (const auto& conn : connections) {
        graph[conn[0]].push_back(conn[1]);
        graph[conn[1]].push_back(conn[0]);
    }

    vector<int> disc(n, -1), low(n, -1);
    vector<vector<int>> result;
    int time = 0;

    for (int i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            Dfs(i, -1, time, disc, low, graph, result);
        }
    }

    return result;
}

/**
 * Problem 8: Alien Dictionary (LC 269)
 * Description:
 * Given a list of words from the alien dictionary, derive the order of letters in the alien language.
 * Example:
 * Input: words = ["wrt", "wrf", "er", "ett", "rftt"]
 * Output: "wertf"
 */
string AlienOrder(vector<string>& words) {
    unordered_map<char, int> in_degree;
    unordered_map<char, unordered_set<char>> graph;

    for (const string& word : words) {
        for (char c : word) {
            in_degree[c] = 0;
        }
    }

    for (size_t i = 0; i < words.size() - 1; ++i) {
        string w1 = words[i], w2 = words[i + 1];
        int len = min(w1.size(), w2.size());
        bool found_difference = false;
        for (int j = 0; j < len; ++j) {
            if (w1[j] != w2[j]) {
                if (!graph[w1[j]].count(w2[j])) {
                    graph[w1[j]].insert(w2[j]);
                    in_degree[w2[j]]++;
                }
                found_difference = true;
                break;
            }
        }
        if (!found_difference && w1.size() > w2.size()) {
            return "";
        }
    }

    queue<char> q;
    for (const auto& [node, degree] : in_degree) {
        if (degree == 0) q.push(node);
    }

    string result;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        result += c;
        for (char neighbor : graph[c]) {
            if (--in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return result.size() == in_degree.size() ? result : "";
}

/**
 * Problem 9: Shortest Path in Binary Matrix (LC 1091)
 * Description:
 * Given an n x n binary grid, return the length of the shortest clear path in the grid.
 * The path may only travel through cells that are 0 and moves 8-directionally.
 * Example:
 * Input: grid = [[0, 1], [1, 0]]
 * Output: 2
 */
int ShortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;

    vector<vector<int>> directions = {{0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}};
    queue<pair<int, int>> q;
    q.push({0, 0});
    grid[0][0] = 1;

    int path_length = 1;
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto [x, y] = q.front();
            q.pop();
            if (x == n - 1 && y == n - 1) return path_length;
            for (const auto& dir : directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 0) {
                    q.push({nx, ny});
                    grid[nx][ny] = 1;
                }
            }
        }
        ++path_length;
    }

    return -1;
}

/**
 * Problem 10: Strongly Connected Components (Tarjan's Algorithm) (LC 1192 - variant)
 * Description:
 * Given a directed graph, find all Strongly Connected Components (SCCs).
 * Example:
 * Input: n = 5, edges = [[0,1], [1,2], [2,0], [1,3], [3,4]]
 * Output: [[0,1,2], [3], [4]]
 */

 void TarjanDFS(int node, int& time, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, vector<vector<int>>& graph, vector<vector<int>>& sccs) {
    disc[node] = low[node] = time++;
    st.push(node);
    in_stack[node] = true;

    for (int neighbor : graph[node]) {
        if (disc[neighbor] == -1) {  // If neighbor is not visited
            TarjanDFS(neighbor, time, disc, low, st, in_stack, graph, sccs);
            low[node] = min(low[node], low[neighbor]);
        } else if (in_stack[neighbor]) {  // If neighbor is in stack, it's part of SCC
            low[node] = min(low[node], disc[neighbor]);
        }
    }

    if (disc[node] == low[node]) {  // If node is root of SCC
        vector<int> scc;
        while (true) {
            int v = st.top(); st.pop();
            in_stack[v] = false;
            scc.push_back(v);
            if (v == node) break;
        }
        sccs.push_back(scc);
    }
}

vector<vector<int>> FindSCCs(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
    }

    vector<int> disc(n, -1), low(n, -1);
    vector<vector<int>> sccs;
    stack<int> st;
    vector<bool> in_stack(n, false);
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            TarjanDFS(i, time, disc, low, st, in_stack, graph, sccs);
        }
    }
    return sccs;
}

/**
 * Problem 11: Detect Bipartite Graph (LC 785)
 * Description:
 * Given an undirected graph, determine if it is bipartite.
 * Example:
 * Input: n = 4, edges = [[1,2], [2,3], [3,4], [4,1], [1,3]]
 * Output: false
 */

bool IsBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> colors(n, -1);

    for (int start = 0; start < n; start++) {
        if (colors[start] != -1) continue;
        queue<int> q;
        q.push(start);
        colors[start] = 0;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int neighbor : graph[node]) {
                if (colors[neighbor] == -1) {
                    colors[neighbor] = colors[node] ^ 1;
                    q.push(neighbor);
                } else if (colors[neighbor] == colors[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Problem 12: Eulerian Path in Directed Graph (LC 332 - variant)
 * Description:
 * Find an Eulerian Path in a directed graph, if it exists.
 * Example:
 * Input: edges = [["JFK", "SFO"], ["JFK", "ATL"], ["SFO", "ATL"], ["ATL", "JFK"], ["ATL", "SFO"]]
 * Output: ["JFK", "ATL", "JFK", "SFO", "ATL", "SFO"]
 */

unordered_map<string, priority_queue<string, vector<string>, greater<>>> graph_euler;
vector<string> euler_path;

void DfsEuler(string node) {
    while (!graph_euler[node].empty()) {
        string next = graph_euler[node].top();
        graph_euler[node].pop();
        DfsEuler(next);
    }
    euler_path.push_back(node);
}

vector<string> FindEulerianPath(vector<vector<string>>& tickets) {
    for (auto& ticket : tickets) {
        graph_euler[ticket[0]].push(ticket[1]);
    }

    DfsEuler("JFK");
    reverse(euler_path.begin(), euler_path.end());
    return euler_path;
}

/**
 * Problem 13: Hamiltonian Path (Backtracking)
 * Description:
 * Determine if there exists a Hamiltonian Path in a given graph.
 * Example:
 * Input: n = 4, edges = [[0,1], [1,2], [2,3], [3,0]]
 * Output: true
 */

bool HamiltonianDFS(int node, vector<vector<int>>& graph, vector<bool>& visited, int count) {
    if (static_cast<size_t>(count) == graph.size()) return true;
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor] && HamiltonianDFS(neighbor, graph, visited, count + 1)) {
            return true;
        }
    }
    visited[node] = false;
    return false;
}

bool HasHamiltonianPath(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (HamiltonianDFS(i, graph, visited, 1)) return true;
    }
    return false;
}

/**
 * Problem 14: Topological Sort (DFS) (LC 210 - variant)
 * Description:
 * Given a Directed Acyclic Graph (DAG), return its topological ordering.
 * Example:
 * Input: num_courses = 4, prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]]
 * Output: [0, 1, 2, 3] or [0, 2, 1, 3]
 */

 void TopologicalSortDFS(int node, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            TopologicalSortDFS(neighbor, graph, visited, st);
        }
    }
    st.push(node);
}

vector<int> TopologicalSortDFSWrapper(int num_vertices, vector<vector<int>>& edges) {
    vector<vector<int>> graph(num_vertices);
    for (auto& edge : edges) {
        graph[edge[1]].push_back(edge[0]);
    }

    vector<bool> visited(num_vertices, false);
    stack<int> st;
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            TopologicalSortDFS(i, graph, visited, st);
        }
    }

    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}

/**
 * Problem 15: Articulation Points (LC 1192 - variant)
 * Description:
 * Find all articulation points (critical nodes) in a graph.
 * Example:
 * Input: n = 5, edges = [[0,1], [1,2], [2,0], [1,3], [3,4]]
 * Output: [1, 3]
 */

void FindArticulationDFS(int node, int parent, int& time, vector<int>& disc, vector<int>& low, vector<bool>& visited, vector<vector<int>>& graph, unordered_set<int>& articulation_points) {
    disc[node] = low[node] = time++;
    visited[node] = true;
    int children = 0;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            children++;
            FindArticulationDFS(neighbor, node, time, disc, low, visited, graph, articulation_points);
            low[node] = min(low[node], low[neighbor]);

            if (parent != -1 && low[neighbor] >= disc[node]) {
                articulation_points.insert(node);
            }
        } else if (neighbor != parent) {
            low[node] = min(low[node], disc[neighbor]);
        }
    }

    if (parent == -1 && children > 1) {
        articulation_points.insert(node);
    }
}

vector<int> FindArticulationPoints(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<int> disc(n, -1), low(n, -1);
    vector<bool> visited(n, false);
    unordered_set<int> articulation_points;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            FindArticulationDFS(i, -1, time, disc, low, visited, graph, articulation_points);
        }
    }

    return vector<int>(articulation_points.begin(), articulation_points.end());
}

/**
 * Problem 16: Bridges in a Graph (LC 1192 - variant)
 * Description:
 * Find all bridges (critical edges) in a graph.
 * Example:
 * Input: n = 5, edges = [[0,1], [1,2], [2,0], [1,3], [3,4]]
 * Output: [[1,3], [3,4]]
 */

void FindBridgesDFS(int node, int parent, int& time, vector<int>& disc, vector<int>& low, vector<bool>& visited, vector<vector<int>>& graph, vector<vector<int>>& bridges) {
    disc[node] = low[node] = time++;
    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            FindBridgesDFS(neighbor, node, time, disc, low, visited, graph, bridges);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] > disc[node]) {
                bridges.push_back({node, neighbor});
            }
        } else if (neighbor != parent) {
            low[node] = min(low[node], disc[neighbor]);
        }
    }
}

vector<vector<int>> FindBridges(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    vector<int> disc(n, -1), low(n, -1);
    vector<bool> visited(n, false);
    vector<vector<int>> bridges;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            FindBridgesDFS(i, -1, time, disc, low, visited, graph, bridges);
        }
    }

    return bridges;
}

/**
 * Problem 17: Find the Town Judge (LC 997)
 * Description:
 * In a town, there are `n` people labeled from `1` to `n`. One person is the town judge.
 * The town judge trusts nobody, and everybody (except for the judge) trusts the judge.
 * Example:
 * Input: n = 3, trust = [[1,3], [2,3]]
 * Output: 3
 */

 int FindJudge(int n, vector<vector<int>>& trust) {
    vector<int> trust_count(n + 1, 0);

    for (auto& t : trust) {
        trust_count[t[0]]--; // Person trusts someone, cannot be judge
        trust_count[t[1]]++; // Person is trusted
    }

    for (int i = 1; i <= n; i++) {
        if (trust_count[i] == n - 1) return i;
    }

    return -1;
}

/**
 * Problem 18: Cheapest Flights Within K Stops (LC 787)
 * Description:
 * Given `n` cities and flights represented as `[from, to, price]`, find the cheapest price
 * from `src` to `dst` with at most `k` stops.
 * Example:
 * Input: n = 3, flights = [[0,1,100], [1,2,100], [0,2,500]], src = 0, dst = 2, k = 1
 * Output: 200
 */

int FindCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> graph(n);
    for (auto& flight : flights) {
        graph[flight[0]].emplace_back(flight[1], flight[2]);
    }

    vector<int> dist(n, INT_MAX);
    queue<pair<int, pair<int, int>>> q; // {stops, {node, cost}}
    q.push({0, {src, 0}});
    dist[src] = 0;

    while (!q.empty()) {
        auto [stops, info] = q.front(); q.pop();
        int node = info.first, cost = info.second;
        if (stops > k) continue;

        for (auto [neighbor, price] : graph[node]) {
            if (cost + price < dist[neighbor]) {
                dist[neighbor] = cost + price;
                q.push({stops + 1, {neighbor, dist[neighbor]}});
            }
        }
    }

    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

/**
 * Problem 19: Reconstruct Itinerary (LC 332)
 * Description:
 * Given a list of airline tickets represented as `[from, to]`, reconstruct the itinerary
 * in lexical order starting from `"JFK"`.
 * Example:
 * Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
 * Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
 */

unordered_map<string, priority_queue<string, vector<string>, greater<>>> graph;
vector<string> itinerary;

void DfsItinerary(string node) {
    while (!graph[node].empty()) {
        string next = graph[node].top();
        graph[node].pop();
        DfsItinerary(next);
    }
    itinerary.push_back(node);
}

vector<string> FindItinerary(vector<vector<string>>& tickets) {
    for (auto& ticket : tickets) {
        graph[ticket[0]].push(ticket[1]);
    }

    DfsItinerary("JFK");
    reverse(itinerary.begin(), itinerary.end());
    return itinerary;
}

/**
 * Problem 20: Minimum Height Trees (LC 310)
 * Description:
 * A tree with `n` nodes (undirected) is given as an edge list.
 * Find all roots that result in a tree with the minimum height.
 * Example:
 * Input: n = 4, edges = [[1,0], [1,2], [1,3]]
 * Output: [1]
 */

vector<int> FindMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};

    vector<vector<int>> graph(n);
    vector<int> degree(n, 0);

    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        degree[edge[0]]++;
        degree[edge[1]]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1) q.push(i);
    }

    while (n > 2) {
        int size = q.size();
        n -= size;
        for (int i = 0; i < size; i++) {
            int node = q.front(); q.pop();
            for (int neighbor : graph[node]) {
                if (--degree[neighbor] == 1) q.push(neighbor);
            }
        }
    }

    vector<int> result;
    while (!q.empty()) {
        result.push_back(q.front());
        q.pop();
    }

    return result;
}

int main() {
    // Test DFS
    vector<vector<int>> test_graph = {{1, 2}, {3}, {3}, {}};
    vector<bool> visited(test_graph.size(), false);
    cout << "DFS Traversal: ";
    DepthFirstSearch(test_graph, 0, visited);
    cout << endl;

    // Test BFS
    cout << "BFS Traversal: ";
    BreadthFirstSearch(test_graph, 0);
    cout << endl;

    // Graph for Topological Sort (DAG)
    vector<vector<int>> dag = {
        {1, 2}, {3}, {3}, {4, 5}, {}, {}
    };
    vector<int> topo_order = TopologicalSort(6, dag);
    cout << "Topological Sort Order: ";
    for (int node : topo_order) cout << node << " ";
    cout << endl;

    // Test Dijkstra
    vector<vector<pair<int, int>>> graph = {{{1, 1}, {2, 4}}, {{2, 2}, {3, 5}}, {{3, 1}}, {}};
    vector<int> dijkstra_result = DijkstraShortestPath(0, 4, graph);
    cout << "Dijkstra Shortest Paths: ";
    for (int dist : dijkstra_result) cout << dist << " ";
    cout << endl;

    // Test Bellman-Ford
    vector<tuple<int, int, int>> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 1}, {0, 2, 4}, {1, 3, 5}};
    vector<int> bellman_ford_result = BellmanFordShortestPath(0, 4, edges);
    cout << "Bellman-Ford Shortest Paths: ";
    for (int dist : bellman_ford_result) cout << dist << " ";
    cout << endl;

    // Test Kruskal
    int mstCost = KruskalMinimumSpanningTree(4, edges);
    cout << "Kruskal MST Cost: " << mstCost << endl;

    // Weighted Graph for Prim's MST Algorithm
    vector<vector<pair<int, int>>> weighted_graph = {
        {{1, 1}, {2, 4}}, {{0, 1}, {2, 2}, {3, 5}}, {{0, 4}, {1, 2}, {3, 1}}, {{1, 5}, {2, 1}}
    };

    int prim_result = PrimMinimumSpanningTree(4, weighted_graph);
    cout << "Prim's MST Cost: " << prim_result << endl;

    // Problem 1: Number of Islands
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << "Number of Islands: " << NumIslands(grid1) << endl;

    // Problem 2: Clone Graph
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};
    Node* cloned_graph = CloneGraph(node1);
    cout << "Graph cloned: " << (cloned_graph != nullptr ? "Success" : "Failure") << endl;

    // Problem 3: Course Schedule
    vector<vector<int>> prerequisites3 = {{1, 0}, {2, 1}, {3, 2}};
    cout << "Can Finish Courses: " << (CanFinish(4, prerequisites3) ? "Yes" : "No") << endl;

    // Problem 4: Course Schedule II
    vector<int> order4 = FindOrder(4, prerequisites3);
    cout << "Course Order: ";
    for (int course : order4) cout << course << " ";
    cout << endl;

    // Problem 5: Network Delay Time
    vector<vector<int>> times5 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    cout << "Network Delay Time: " << NetworkDelayTime(times5, 4, 2) << endl;

    // Problem 6: Word Ladder
    vector<string> wordList6 = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << "Word Ladder Length: " << LadderLength("hit", "cog", wordList6) << endl;

    // Problem 7: Critical Connections in a Network
    vector<vector<int>> connections7 = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    vector<vector<int>> result7 = CriticalConnections(4, connections7);
    cout << "Critical Connections: ";
    for (const auto& conn : result7) {
        cout << "[" << conn[0] << ", " << conn[1] << "] ";
    }
    cout << endl;

    // Problem 8: Alien Dictionary
    vector<string> words8 = {"wrt", "wrf", "er", "ett", "rftt"};
    cout << "Alien Dictionary Order: " << AlienOrder(words8) << endl;

    // Problem 9: Shortest Path in Binary Matrix
    vector<vector<int>> grid9 = {{0, 1}, {1, 0}};
    cout << "Shortest Path in Binary Matrix: " << ShortestPathBinaryMatrix(grid9) << endl;

    // Test Problem 10: Strongly Connected Components (Tarjan's Algorithm)
    vector<vector<int>> edges10 = {{0,1}, {1,2}, {2,0}, {1,3}, {3,4}};
    vector<vector<int>> sccs = FindSCCs(5, edges10);
    cout << "SCCs: ";
    for (auto& scc : sccs) {
        cout << "[ ";
        for (int node : scc) cout << node << " ";
        cout << "] ";
    }
    cout << endl;

    // Test Problem 11: Detect Bipartite Graph
    vector<vector<int>> edges11 = {{1,2}, {2,3}, {3,4}, {4,1}, {1,3}};
    cout << "Is Bipartite: " << (IsBipartite(edges11) ? "Yes" : "No") << endl;

    // Test Problem 12: Eulerian Path
    vector<vector<string>> edges12 = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    vector<string> euler_path_result = FindEulerianPath(edges12);
    cout << "Eulerian Path: ";
    for (const string& airport : euler_path_result) cout << airport << " ";
    cout << endl;

    // Test Problem 13: Hamiltonian Path
    vector<vector<int>> edges13 = {{0,1}, {1,2}, {2,3}, {3,0}};
    cout << "Has Hamiltonian Path: " << (HasHamiltonianPath(4, edges13) ? "Yes" : "No") << endl;

    // Test Problem 14: Topological Sort (DFS)
    vector<vector<int>> edges14 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    vector<int> topo_sort_result = TopologicalSortDFSWrapper(4, edges14);
    cout << "Topological Sort (DFS): ";
    for (int node : topo_sort_result) cout << node << " ";
    cout << endl;

    // Test Problem 15: Articulation Points
    vector<vector<int>> edges15 = {{0,1}, {1,2}, {2,0}, {1,3}, {3,4}};
    vector<int> articulation_points = FindArticulationPoints(5, edges15);
    cout << "Articulation Points: ";
    for (int node : articulation_points) cout << node << " ";
    cout << endl;

    // Test Problem 16: Bridges in a Graph
    vector<vector<int>> edges16 = {{0,1}, {1,2}, {2,0}, {1,3}, {3,4}};
    vector<vector<int>> bridges = FindBridges(5, edges16);
    cout << "Bridges: ";
    for (const auto& edge : bridges) {
        cout << "[" << edge[0] << ", " << edge[1] << "] ";
    }
    cout << endl;

    // Test Problem 17: Find the Town Judge
    vector<vector<int>> trust17 = {{1, 3}, {2, 3}};
    cout << "Town Judge: " << FindJudge(3, trust17) << endl;

    // Test Problem 18: Cheapest Flights Within K Stops
    vector<vector<int>> flights18 = {{0,1,100}, {1,2,100}, {0,2,500}};
    cout << "Cheapest Flight Price: " << FindCheapestPrice(3, flights18, 0, 2, 1) << endl;

    // Test Problem 19: Reconstruct Itinerary
    vector<vector<string>> tickets19 = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    vector<string> itinerary19 = FindItinerary(tickets19);
    cout << "Reconstructed Itinerary: ";
    for (const string& airport : itinerary19) cout << airport << " ";
    cout << endl;

    // Test Problem 20: Minimum Height Trees
    vector<vector<int>> edges20 = {{1,0}, {1,2}, {1,3}};
    vector<int> min_height_roots = FindMinHeightTrees(4, edges20);
    cout << "Minimum Height Trees: ";
    for (int root : min_height_roots) cout << root << " ";
    cout << endl;

    return 0;
}
