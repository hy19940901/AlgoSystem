// Graph.cpp
#include "../include/graph.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <limits>

namespace graph {

BaseGraph::BaseGraph(int num_vertices) : num_vertices_(num_vertices), adjacency_list_(num_vertices) {}

BaseGraph::~BaseGraph() {}

void BaseGraph::DisplayGraph() const {
    for (int i = 0; i < num_vertices_; ++i) {
        std::cout << "Vertex " << i << " --> ";
        for (auto &edge : adjacency_list_[i]) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}

void BaseGraph::Dfs(int start_vertex) {
    std::vector<bool> visited(num_vertices_, false);
    std::stack<int> stack;

    stack.push(start_vertex);

    while (!stack.empty()) {
        int current_vertex = stack.top();
        stack.pop();

        if (!visited[current_vertex]) {
            std::cout << current_vertex << " ";
            visited[current_vertex] = true;
        }

        for (auto i = adjacency_list_[current_vertex].rbegin(); i != adjacency_list_[current_vertex].rend(); ++i) {
            if (!visited[i->first]) {
                stack.push(i->first);
            }
        }
    }
    std::cout << std::endl;
}

void BaseGraph::Bfs(int start_vertex) {
    std::vector<bool> visited(num_vertices_, false);
    std::queue<int> queue;

    visited[start_vertex] = true;
    queue.push(start_vertex);

    while (!queue.empty()) {
        int current_vertex = queue.front();
        std::cout << current_vertex << " ";
        queue.pop();

        for (auto &adjacent : adjacency_list_[current_vertex]) {
            if (!visited[adjacent.first]) {
                visited[adjacent.first] = true;
                queue.push(adjacent.first);
            }
        }
    }
    std::cout << std::endl;
}

std::vector<int> BaseGraph::Dijkstra(int source) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
    std::vector<int> distances(num_vertices_, std::numeric_limits<int>::max());

    distances[source] = 0;
    min_heap.push({0, source});

    while (!min_heap.empty()) {
        int u = min_heap.top().second;
        min_heap.pop();

        for (auto &i : adjacency_list_[u]) {
            int v = i.first;
            int weight = i.second;
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                min_heap.push({distances[v], v});
            }
        }
    }

    return distances;
}

std::vector<std::pair<int, int>> BaseGraph::KruskalMST() {
    std::vector<std::tuple<int, int, int>> edges; // (weight, u, v)

    // Convert adjacency list to edge list
    for (int u = 0; u < num_vertices_; ++u) {
        for (const auto& [v, w] : adjacency_list_[u]) {
            if (u < v) { // avoid duplicates for undirected graph
                edges.emplace_back(w, u, v);
            }
        }
    }

    // Sort edges by weight
    std::sort(edges.begin(), edges.end());

    std::vector<std::pair<int, int>> result;
    DisjointSet ds(num_vertices_);

    for (const auto& [w, u, v] : edges) {
        if (ds.Find(u) != ds.Find(v)) {
            ds.Unite(u, v);
            result.emplace_back(u, v);
        }
    }

    return result;
}

bool BaseGraph::HasCycleUtil(int vertex, std::vector<bool>& visited, std::vector<bool>& rec_stack) {
    if(!visited[vertex]) {
        visited[vertex] = true;
        rec_stack[vertex] = true;

        for(auto i = adjacency_list_[vertex].begin(); i != adjacency_list_[vertex].end(); ++i) {
            if ( !visited[i->first] && HasCycleUtil(i->first, visited, rec_stack) )
                return true;
            else if (rec_stack[i->first])
                return true;
        }
    }
    rec_stack[vertex] = false;
    return false;
}

bool BaseGraph::HasCycle() {
    std::vector<bool> visited(num_vertices_, false);
    std::vector<bool> rec_stack(num_vertices_, false);

    for(int i = 0; i < num_vertices_; i++)
        if (!visited[i] && HasCycleUtil(i, visited, rec_stack))
            return true;

    return false;
}

std::vector<std::pair<int, int>> BaseGraph::PrimMST(int start_vertex) {
    std::vector<bool> in_mst(num_vertices_, false);
    std::vector<int> key(num_vertices_, std::numeric_limits<int>::max());
    std::vector<int> parent(num_vertices_, -1);
    std::vector<std::pair<int, int>> minimum_spanning_tree;

    key[start_vertex] = 0;

    for (int i = 0; i < num_vertices_; i++) {
        int u = -1;
        for (int v = 0; v < num_vertices_; v++) {
            if (!in_mst[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        if (key[u] == std::numeric_limits<int>::max()) {
            break;
        }

        in_mst[u] = true;

        for (auto &edge : adjacency_list_[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!in_mst[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < num_vertices_; i++) {
        minimum_spanning_tree.push_back({parent[i], i});
    }

    return minimum_spanning_tree;
}

int BaseGraph::GetInDegree(int vertex) {
    int in_degree = 0;
    for (int i = 0; i < num_vertices_; ++i) {
        for (const auto &edge : adjacency_list_[i]) {
            if (edge.first == vertex) {
                ++in_degree;
            }
        }
    }
    return in_degree;
}

int BaseGraph::GetOutDegree(int vertex) {
    return adjacency_list_[vertex].size();
}

std::vector<int> BaseGraph::GetPredecessors(int vertex) {
    std::vector<int> predecessors;
    for (int i = 0; i < num_vertices_; ++i) {
        for (const auto &edge : adjacency_list_[i]) {
            if (edge.first == vertex) {
                predecessors.push_back(i);
            }
        }
    }
    return predecessors;
}

std::vector<int> BaseGraph::GetSuccessors(int vertex) {
    std::vector<int> successors;
    for (const auto &edge : adjacency_list_[vertex]) {
        successors.push_back(edge.first);
    }
    return successors;
}

// DirectedAcyclicGraph member functions
void DirectedAcyclicGraph::AddEdge(int source, int destination, int weight) {
    adjacency_list_[source].push_back({destination, weight});
}

std::vector<int> DirectedAcyclicGraph::TopologicalSort() {
    std::vector<int> in_degree(num_vertices_, 0);
    for (int u = 0; u < num_vertices_; u++) {
        for (auto &i : adjacency_list_[u]) {
            in_degree[i.first]++;
        }
    }

    std::queue<int> queue;
    for (int i = 0; i < num_vertices_; i++) {
        if (in_degree[i] == 0) {
            queue.push(i);
        }
    }

    int cnt = 0;
    std::vector<int> top_order;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        top_order.push_back(u);

        for (auto &i : adjacency_list_[u]) {
            if (--in_degree[i.first] == 0)
                queue.push(i.first);
        }
        cnt++;
    }

    if (cnt != num_vertices_) {
        std::cout << "There exists a cycle in the graph\n";
        return {};
    }

    return top_order;
}

std::vector<std::vector<int>> DirectedAcyclicGraph::FindAllPaths(int s, int d) {
    // Function to find all paths from 's' to 'd'
    std::vector<bool> visited(num_vertices_, false);
    std::vector<int> path;
    std::vector<std::vector<int>> all_paths;
    FindAllPathsUtil(s, d, visited, path, all_paths);
    return all_paths;
}

void DirectedAcyclicGraph::FindAllPathsUtil(int u, int d, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& all_paths) {
    visited[u] = true;
    path.push_back(u);

    if (u == d) {
        all_paths.push_back(path);
    } else {
        for (auto i = adjacency_list_[u].begin(); i != adjacency_list_[u].end(); ++i)
            if (!visited[i->first])
                FindAllPathsUtil(i->first, d, visited, path, all_paths);
    }

    path.pop_back();
    visited[u] = false;
}

void DirectedAcyclicGraph::BellmanFordShortestPath(int source) {
    std::vector<int> distance(num_vertices_, std::numeric_limits<int>::max());
    distance[source] = 0;

    for (int i = 0; i < num_vertices_ - 1; ++i) {
        for (int u = 0; u < num_vertices_; ++u) {
            for (auto &edge : adjacency_list_[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < num_vertices_; ++u) {
        for (auto &edge : adjacency_list_[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                std::cout << "Graph contains negative-weight cycle." << std::endl;
                return;
            }
        }
    }

    std::cout << "Shortest distances from source vertex " << source << ":\n";
    for (int i = 0; i < num_vertices_; ++i) {
        std::cout << "Vertex " << i << ": " << distance[i] << std::endl;
    }
}

// DirectedCyclicGraph member functions
void DirectedCyclicGraph::AddEdge(int source, int destination, int weight) {
    adjacency_list_[source].push_back({destination, weight});
}

// UndirectedAcyclicGraph member functions
void UndirectedAcyclicGraph::AddEdge(int source, int destination, int weight) {
    adjacency_list_[source].push_back({destination, weight});
    adjacency_list_[destination].push_back({source, weight});
}

bool UndirectedAcyclicGraph::HasCycle() {
    std::vector<bool> visited(num_vertices_, false);
    for (int i = 0; i < num_vertices_; i++)
        if (!visited[i])
            if (HasCycleUtil(i, visited, -1))
                return true;
    return false;
}

bool UndirectedAcyclicGraph::HasCycleUtil(int v, std::vector<bool> &visited, int parent) {
    visited[v] = true;

    for (auto &i : adjacency_list_[v]) {
        if (!visited[i.first]) {
            if (HasCycleUtil(i.first, visited, v))
                return true;
        }
        else if (i.first != parent)
            return true;
    }
    return false;
}

std::vector<std::pair<int, int>> UndirectedAcyclicGraph::PrimMST(int startVertex) {
    std::vector<bool> inMST(num_vertices_, false);
    std::vector<int> key(num_vertices_, std::numeric_limits<int>::max());
    std::vector<int> parent(num_vertices_, -1);
    std::vector<std::pair<int, int>> minimum_spanning_tree;

    key[startVertex] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;
    minHeap.push({0, startVertex});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;

        for (auto& edge : adjacency_list_[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                minHeap.push({key[v], v});
            }
        }
    }

    for (int i = 1; i < num_vertices_; i++) {
        minimum_spanning_tree.push_back({parent[i], i});
    }

    return minimum_spanning_tree;
}


// UndirectedCyclicGraph member functions
void UndirectedCyclicGraph::AddEdge(int source, int destination, int weight) {
    adjacency_list_[source].push_back({destination, weight});
    adjacency_list_[destination].push_back({source, weight});
}

}


// Other utility functions as necessary
