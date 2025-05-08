// Graph.cpp
#include "../include/Graph.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <limits>

BaseGraph::BaseGraph(int numVertices) : numVertices_(numVertices), adjacencyList_(numVertices) {}

BaseGraph::~BaseGraph() {}

void BaseGraph::displayGraph() const {
    for (int i = 0; i < numVertices_; ++i) {
        std::cout << "Vertex " << i << " --> ";
        for (auto &edge : adjacencyList_[i]) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}

void BaseGraph::DFS(int startVertex) {
    std::vector<bool> visited(numVertices_, false);
    std::stack<int> stack;

    stack.push(startVertex);

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();

        if (!visited[currentVertex]) {
            std::cout << currentVertex << " ";
            visited[currentVertex] = true;
        }

        for (auto i = adjacencyList_[currentVertex].rbegin(); i != adjacencyList_[currentVertex].rend(); ++i) {
            if (!visited[i->first]) {
                stack.push(i->first);
            }
        }
    }
    std::cout << std::endl;
}

void BaseGraph::BFS(int startVertex) {
    std::vector<bool> visited(numVertices_, false);
    std::queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        std::cout << currentVertex << " ";
        queue.pop();

        for (auto &adjacent : adjacencyList_[currentVertex]) {
            if (!visited[adjacent.first]) {
                visited[adjacent.first] = true;
                queue.push(adjacent.first);
            }
        }
    }
    std::cout << std::endl;
}

std::vector<int> BaseGraph::dijkstra(int source) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;
    std::vector<int> distances(numVertices_, std::numeric_limits<int>::max());

    distances[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        for (auto &i : adjacencyList_[u]) {
            int v = i.first;
            int weight = i.second;
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances;
}

bool BaseGraph::hasCycleUtil(int vertex, std::vector<bool>& visited, std::vector<bool>& recStack) {
    if(!visited[vertex]) {
        visited[vertex] = true;
        recStack[vertex] = true;

        for(auto i = adjacencyList_[vertex].begin(); i != adjacencyList_[vertex].end(); ++i) {
            if ( !visited[i->first] && hasCycleUtil(i->first, visited, recStack) )
                return true;
            else if (recStack[i->first])
                return true;
        }
    }
    recStack[vertex] = false;
    return false;
}

bool BaseGraph::hasCycle() {
    std::vector<bool> visited(numVertices_, false);
    std::vector<bool> recStack(numVertices_, false);

    for(int i = 0; i < numVertices_; i++)
        if (!visited[i] && hasCycleUtil(i, visited, recStack))
            return true;

    return false;
}

std::vector<std::pair<int, int>> BaseGraph::primMST(int startVertex) {
    std::vector<bool> inMST(numVertices_, false);
    std::vector<int> key(numVertices_, std::numeric_limits<int>::max());
    std::vector<int> parent(numVertices_, -1);
    std::vector<std::pair<int, int>> minimumSpanningTree;

    key[startVertex] = 0;

    for (int i = 0; i < numVertices_; i++) {
        int u = -1;
        for (int v = 0; v < numVertices_; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        if (key[u] == std::numeric_limits<int>::max()) {
            break;
        }

        inMST[u] = true;

        for (auto &edge : adjacencyList_[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < numVertices_; i++) {
        minimumSpanningTree.push_back({parent[i], i});
    }

    return minimumSpanningTree;
}

int BaseGraph::getInDegree(int vertex) {
    int inDegree = 0;
    for (int i = 0; i < numVertices_; ++i) {
        for (const auto &edge : adjacencyList_[i]) {
            if (edge.first == vertex) {
                ++inDegree;
            }
        }
    }
    return inDegree;
}

int BaseGraph::getOutDegree(int vertex) {
    return adjacencyList_[vertex].size();
}

std::vector<int> BaseGraph::getPredecessors(int vertex) {
    std::vector<int> predecessors;
    for (int i = 0; i < numVertices_; ++i) {
        for (const auto &edge : adjacencyList_[i]) {
            if (edge.first == vertex) {
                predecessors.push_back(i);
            }
        }
    }
    return predecessors;
}

std::vector<int> BaseGraph::getSuccessors(int vertex) {
    std::vector<int> successors;
    for (const auto &edge : adjacencyList_[vertex]) {
        successors.push_back(edge.first);
    }
    return successors;
}

// DirectedAcyclicGraph member functions
void DirectedAcyclicGraph::addEdge(int source, int destination, int weight) {
    adjacencyList_[source].push_back({destination, weight});
}

std::vector<int> DirectedAcyclicGraph::topologicalSort() {
    std::vector<int> in_degree(numVertices_, 0);
    for (int u = 0; u < numVertices_; u++) {
        for (auto &i : adjacencyList_[u]) {
            in_degree[i.first]++;
        }
    }

    std::queue<int> queue;
    for (int i = 0; i < numVertices_; i++) {
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

        for (auto &i : adjacencyList_[u]) {
            if (--in_degree[i.first] == 0)
                queue.push(i.first);
        }
        cnt++;
    }

    if (cnt != numVertices_) {
        std::cout << "There exists a cycle in the graph\n";
        return {};
    }

    return top_order;
}

std::vector<std::vector<int>> DirectedAcyclicGraph::findAllPaths(int s, int d) {
    // Function to find all paths from 's' to 'd'
    std::vector<bool> visited(numVertices_, false);
    std::vector<int> path;
    std::vector<std::vector<int>> allPaths;
    findAllPathsUtil(s, d, visited, path, allPaths);
    return allPaths;
}

void DirectedAcyclicGraph::findAllPathsUtil(int u, int d, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths) {
    visited[u] = true;
    path.push_back(u);

    if (u == d) {
        allPaths.push_back(path);
    } else {
        for (auto i = adjacencyList_[u].begin(); i != adjacencyList_[u].end(); ++i)
            if (!visited[i->first])
                findAllPathsUtil(i->first, d, visited, path, allPaths);
    }

    path.pop_back();
    visited[u] = false;
}

void DirectedAcyclicGraph::bellmanFordShortestPath(int source) {
    std::vector<int> distance(numVertices_, std::numeric_limits<int>::max());
    distance[source] = 0;

    for (int i = 0; i < numVertices_ - 1; ++i) {
        for (int u = 0; u < numVertices_; ++u) {
            for (auto &edge : adjacencyList_[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < numVertices_; ++u) {
        for (auto &edge : adjacencyList_[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                std::cout << "Graph contains negative-weight cycle." << std::endl;
                return;
            }
        }
    }

    std::cout << "Shortest distances from source vertex " << source << ":\n";
    for (int i = 0; i < numVertices_; ++i) {
        std::cout << "Vertex " << i << ": " << distance[i] << std::endl;
    }
}

// DirectedCyclicGraph member functions
void DirectedCyclicGraph::addEdge(int source, int destination, int weight) {
    adjacencyList_[source].push_back({destination, weight});
}

// UndirectedAcyclicGraph member functions
void UndirectedAcyclicGraph::addEdge(int source, int destination, int weight) {
    adjacencyList_[source].push_back({destination, weight});
    adjacencyList_[destination].push_back({source, weight});
}

bool UndirectedAcyclicGraph::hasCycle() {
    std::vector<bool> visited(numVertices_, false);
    for (int i = 0; i < numVertices_; i++)
        if (!visited[i])
            if (hasCycleUtil(i, visited, -1))
                return true;
    return false;
}

bool UndirectedAcyclicGraph::hasCycleUtil(int v, std::vector<bool> &visited, int parent) {
    visited[v] = true;

    for (auto &i : adjacencyList_[v]) {
        if (!visited[i.first]) {
            if (hasCycleUtil(i.first, visited, v))
                return true;
        }
        else if (i.first != parent)
            return true;
    }
    return false;
}

std::vector<std::pair<int, int>> UndirectedAcyclicGraph::primMST(int startVertex) {
    std::vector<bool> inMST(numVertices_, false);
    std::vector<int> key(numVertices_, std::numeric_limits<int>::max());
    std::vector<int> parent(numVertices_, -1);
    std::vector<std::pair<int, int>> minimumSpanningTree;

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

        for (auto& edge : adjacencyList_[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                minHeap.push({key[v], v});
            }
        }
    }

    for (int i = 1; i < numVertices_; i++) {
        minimumSpanningTree.push_back({parent[i], i});
    }

    return minimumSpanningTree;
}


// UndirectedCyclicGraph member functions
void UndirectedCyclicGraph::addEdge(int source, int destination, int weight) {
    adjacencyList_[source].push_back({destination, weight});
    adjacencyList_[destination].push_back({source, weight});
}

// Other utility functions as necessary
