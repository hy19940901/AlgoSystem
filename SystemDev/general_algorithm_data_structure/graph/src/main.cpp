#include "../include/graph.h"
#include <iostream>

// Helper function to print all paths
void PrintAllPaths(const std::vector<std::vector<int>>& all_paths) {
    for (const auto& path : all_paths) {
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

void TestBasicInformation(graph::BaseGraph& graph) {
    // Test GetInDegree function
    for (int i = 0; i < 5; ++i) {
        std::cout << "In-degree of vertex " << i << ": " << graph.GetInDegree(i) << std::endl;
    }

    // Test GetOutDegree function
    for (int i = 0; i < 5; ++i) {
        std::cout << "Out-degree of vertex " << i << ": " << graph.GetOutDegree(i) << std::endl;
    }

    // Test getPredecessors function
    for (int i = 0; i < 5; ++i) {
        std::vector<int> predecessors = graph.GetPredecessors(i);
        std::cout << "Predecessors of vertex " << i << ": ";
        for (int predecessor : predecessors) {
            std::cout << predecessor << " ";
        }
        std::cout << std::endl;
    }

    // Test GetSuccessors function
    for (int i = 0; i < 5; ++i) {
        std::vector<int> successors = graph.GetSuccessors(i);
        std::cout << "Successors of vertex " << i << ": ";
        for (int successor : successors) {
            std::cout << successor << " ";
        }
        std::cout << std::endl;
    }
}

void TestDirectedAcyclicGraph(graph::DirectedAcyclicGraph& dag, int source, int target) {
    std::cout << "Directed Acyclic Graph:" << std::endl;
    dag.DisplayGraph();

    std::cout << "Does the DAG have a cycle? " << (dag.HasCycle() ? "Yes" : "No") << std::endl;

    auto top_sort_result = dag.TopologicalSort();
    std::cout << "Topological sorting of the DAG: ";
    for (int vertex : top_sort_result) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Find all paths from source to target
    std::vector<std::vector<int>> all_paths = dag.FindAllPaths(source, target);
    std::cout << "All paths from vertex " << source << " to vertex " << target << ":" << std::endl;
    PrintAllPaths(all_paths);
    std::cout << "\n" << std::endl;

    TestBasicInformation(dag);
}

void TestUndirectedAcyclicGraph(graph::UndirectedAcyclicGraph& uag) {
    std::cout << "Undirected Acyclic Graph:" << std::endl;
    uag.DisplayGraph();
    std::cout << "Does the UAG have a cycle? " << (uag.HasCycle() ? "Yes" : "No") << std::endl;
}

void TestGraphTraversal(graph::BaseGraph& graph) {
    std::cout << "DFS starting from vertex 0: ";
    graph.Dfs(0);
    std::cout << "BFS starting from vertex 0: ";
    graph.Bfs(0);
    std::cout << std::endl;
}

void TestDijkstraAlgorithm(graph::BaseGraph& graph) {
    std::cout << "Dijkstra's shortest path starting from vertex 0: " << std::endl;
    auto distances = graph.Dijkstra(0);
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "Vertex " << i << " distance: " << distances[i] << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    graph::DirectedAcyclicGraph dag(5);
    dag.AddEdge(0, 1, 1);
    dag.AddEdge(0, 2, 1);
    dag.AddEdge(1, 3, 1);
    dag.AddEdge(1, 4, 1);
    dag.AddEdge(2, 3, 1);
    TestDirectedAcyclicGraph(dag, 0, 4);

    int source = 0;
    dag.BellmanFordShortestPath(source);

    graph::UndirectedAcyclicGraph uag(5);
    uag.AddEdge(0, 1, 1);
    uag.AddEdge(0, 2, 1);
    uag.AddEdge(1, 3, 1);
    uag.AddEdge(1, 4, 1);
    TestUndirectedAcyclicGraph(uag);

    int start_vertex = 0;
    std::vector<std::pair<int, int>> minimum_spanning_tree = uag.PrimMST(start_vertex);

    std::cout << "Minimum Spanning Tree Edges:" << std::endl;
    for (const auto &edge : minimum_spanning_tree) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }

    TestGraphTraversal(uag);

    TestDijkstraAlgorithm(dag);

    std::cout << "Kruskal MST Edges (Undirected Acyclic Graph):" << std::endl;
    auto kruskal_result = uag.KruskalMST();
    for (const auto& edge : kruskal_result) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
