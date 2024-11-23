#include "../include/Graph.h"
#include <iostream>

// Helper function to print all paths
void printAllPaths(const std::vector<std::vector<int>>& allPaths) {
    for (const auto& path : allPaths) {
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

void testBasicInformation(BaseGraph& graph) {
    // Test getInDegree function
    for (int i = 0; i < 5; ++i) {
        std::cout << "In-degree of vertex " << i << ": " << graph.getInDegree(i) << std::endl;
    }

    // Test getOutDegree function
    for (int i = 0; i < 5; ++i) {
        std::cout << "Out-degree of vertex " << i << ": " << graph.getOutDegree(i) << std::endl;
    }

    // Test getPredecessors function
    for (int i = 0; i < 5; ++i) {
        std::vector<int> predecessors = graph.getPredecessors(i);
        std::cout << "Predecessors of vertex " << i << ": ";
        for (int predecessor : predecessors) {
            std::cout << predecessor << " ";
        }
        std::cout << std::endl;
    }

    // Test getSuccessors function
    for (int i = 0; i < 5; ++i) {
        std::vector<int> successors = graph.getSuccessors(i);
        std::cout << "Successors of vertex " << i << ": ";
        for (int successor : successors) {
            std::cout << successor << " ";
        }
        std::cout << std::endl;
    }
}

void testDirectedAcyclicGraph(DirectedAcyclicGraph& dag, int source, int target) {
    std::cout << "Directed Acyclic Graph:" << std::endl;
    dag.displayGraph();

    std::cout << "Does the DAG have a cycle? " << (dag.hasCycle() ? "Yes" : "No") << std::endl;

    auto topSortResult = dag.topologicalSort();
    std::cout << "Topological sorting of the DAG: ";
    for (int vertex : topSortResult) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Find all paths from source to target
    std::vector<std::vector<int>> allPaths = dag.findAllPaths(source, target);
    std::cout << "All paths from vertex " << source << " to vertex " << target << ":" << std::endl;
    printAllPaths(allPaths);
    std::cout << "\n" << std::endl;

    testBasicInformation(dag);
}

void testUndirectedAcyclicGraph(UndirectedAcyclicGraph& uag) {
    std::cout << "Undirected Acyclic Graph:" << std::endl;
    uag.displayGraph();
    std::cout << "Does the UAG have a cycle? " << (uag.hasCycle() ? "Yes" : "No") << std::endl;
}

void testGraphTraversal(BaseGraph& graph) {
    std::cout << "DFS starting from vertex 0: ";
    graph.DFS(0);
    std::cout << "BFS starting from vertex 0: ";
    graph.BFS(0);
    std::cout << std::endl;
}

void testDijkstraAlgorithm(BaseGraph& graph) {
    std::cout << "Dijkstra's shortest path starting from vertex 0: " << std::endl;
    auto distances = graph.dijkstra(0);
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "Vertex " << i << " distance: " << distances[i] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // 测试有向无环图 (DAG)
    DirectedAcyclicGraph dag(5);
    dag.addEdge(0, 1, 1);
    dag.addEdge(0, 2, 1);
    dag.addEdge(1, 3, 1);
    dag.addEdge(1, 4, 1);
    dag.addEdge(2, 3, 1);
    testDirectedAcyclicGraph(dag, 0, 4);

    int source = 0;
    dag.bellmanFordShortestPath(source);



    // 测试无向无环图 (UAG)
    UndirectedAcyclicGraph uag(5);
    uag.addEdge(0, 1, 1);
    uag.addEdge(0, 2, 1);
    uag.addEdge(1, 3, 1);
    uag.addEdge(1, 4, 1);
    testUndirectedAcyclicGraph(uag);

    int startVertex = 0;
    std::vector<std::pair<int, int>> minimumSpanningTree = uag.primMST(startVertex);

    std::cout << "Minimum Spanning Tree Edges:" << std::endl;
    for (const auto &edge : minimumSpanningTree) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }

    // 测试图的遍历
    testGraphTraversal(uag);

    // 测试 Dijkstra 算法
    testDijkstraAlgorithm(dag);

    return 0;
}
