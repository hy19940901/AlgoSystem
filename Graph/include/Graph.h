// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <limits>

class BaseGraph {
protected:
    int numVertices_;
    std::vector<std::list<std::pair<int, int>>> adjacencyList_;
    std::vector<std::pair<int, int>> minimumSpanningTree_;

public:
    BaseGraph(int numVertices);
    virtual ~BaseGraph();
    virtual void addEdge(int source, int destination, int weight) = 0;
    virtual std::vector<std::pair<int, int>> primMST(int startVertex);
    void displayGraph() const;
    void DFS(int startVertex);
    void BFS(int startVertex);
    std::vector<int> dijkstra(int source);
    bool hasCycle();
    bool hasCycleUtil(int vertex, std::vector<bool>& visited, std::vector<bool>& recStack);
    int getInDegree(int vertex);
    int getOutDegree(int vertex);
    std::vector<int> getPredecessors(int vertex);
    std::vector<int> getSuccessors(int vertex);
};

class DirectedAcyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph; // Inherit constructor
    void addEdge(int source, int destination, int weight) override;
    std::vector<int> topologicalSort();
    std::vector<std::vector<int>> findAllPaths(int s, int d);
    void findAllPathsUtil(int v, int d, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths);
    void bellmanFordShortestPath(int source);
};

class DirectedCyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph; // Inherit constructor
    void addEdge(int source, int destination, int weight) override;
};

class UndirectedAcyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph; // Inherit constructor
    void addEdge(int source, int destination, int weight) override;
    bool hasCycle();
    bool hasCycleUtil(int v, std::vector<bool> &visited, int parent);
    std::vector<std::pair<int, int>> primMST(int startVertex) override;
};

class UndirectedCyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph; // Inherit constructor
    void addEdge(int source, int destination, int weight) override;
};

#endif // GRAPH_H
