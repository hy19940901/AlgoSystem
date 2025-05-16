#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include "../include/disjoint_set.h"

namespace graph {

/**
 * @class BaseGraph
 * @brief Abstract base class for graph representations (directed/undirected).
 *
 * This class defines the fundamental interface and data structures
 * for graph operations such as adding edges, traversals (DFS/BFS),
 * cycle detection, shortest path computation (Dijkstra), and Minimum Spanning Tree (Prim).
 *
 * It uses an adjacency list structure where each vertex maps to a list of
 * (neighbor, weight) pairs. Derived classes implement graph-type-specific logic
 * for edge addition and cycle detection.
 */
class BaseGraph {
protected:
    int num_vertices_;  ///< Total number of vertices in the graph.
    std::vector<std::list<std::pair<int, int>>> adjacency_list_; ///< Adjacency list storing (neighbor, weight) pairs.
    std::vector<std::pair<int, int>> minimum_spanning_tree_; ///< Stores computed Minimum Spanning Tree edges.

public:
    /**
     * @brief Constructs a graph with a specified number of vertices.
     * @param num_vertices The number of vertices in the graph.
     */
    BaseGraph(int num_vertices);

    /**
     * @brief Virtual destructor for safe cleanup in derived classes.
     */
    virtual ~BaseGraph();

    /**
     * @brief Pure virtual function to add an edge to the graph.
     * @param source The starting vertex of the edge.
     * @param destination The ending vertex of the edge.
     * @param weight The weight/cost associated with the edge.
     */
    virtual void AddEdge(int source, int destination, int weight) = 0;

    /**
     * @brief Computes the Minimum Spanning Tree (MST) using Prim's algorithm.
     * @param startVertex The vertex to start the MST from.
     * @return A vector of edges (source, destination) included in the MST.
     */
    virtual std::vector<std::pair<int, int>> PrimMST(int startVertex);

    /**
     * @brief Displays the adjacency list of the graph to the console.
     */
    void DisplayGraph() const;

    /**
     * @brief Performs Depth-First Search (DFS) traversal from a starting vertex.
     * @param start_vertex The vertex to begin DFS traversal from.
     */
    void Dfs(int start_vertex);

    /**
     * @brief Performs Breadth-First Search (BFS) traversal from a starting vertex.
     * @param start_vertex The vertex to begin BFS traversal from.
     */
    void Bfs(int start_vertex);

    /**
     * @brief Computes the shortest distances from a source vertex to all others using Dijkstra’s algorithm.
     * @param source The vertex to start the shortest path computation from.
     * @return A vector of distances where result[i] represents the shortest distance from source to vertex i.
     */
    std::vector<int> Dijkstra(int source);

    /**
     * @brief Computes Minimum Spanning Tree using Kruskal's algorithm.
     * @return A list of MST edges in the form (source, destination).
     */
    std::vector<std::pair<int, int>> KruskalMST();

    /**
     * @brief Determines whether the directed graph contains any cycles.
     * @return true if a cycle exists, false otherwise.
     */
    bool HasCycle();

    /**
     * @brief Helper function for cycle detection using recursion and backtracking.
     * @param vertex The current vertex being explored.
     * @param visited A boolean vector marking visited vertices.
     * @param rec_stack A boolean vector marking vertices in the recursion stack.
     * @return true if a cycle is detected during the recursive path.
     */
    bool HasCycleUtil(int vertex, std::vector<bool>& visited, std::vector<bool>& rec_stack);

    /**
     * @brief Returns the number of edges incoming to the given vertex.
     * @param vertex The vertex whose in-degree is to be calculated.
     * @return The in-degree count of the vertex.
     */
    int GetInDegree(int vertex);

    /**
     * @brief Returns the number of edges outgoing from the given vertex.
     * @param vertex The vertex whose out-degree is to be calculated.
     * @return The out-degree count of the vertex.
     */
    int GetOutDegree(int vertex);

    /**
     * @brief Retrieves all predecessor vertices pointing to the given vertex.
     * @param vertex The vertex whose predecessors are to be retrieved.
     * @return A vector of vertex indices representing predecessors.
     */
    std::vector<int> GetPredecessors(int vertex);

    /**
     * @brief Retrieves all successor vertices that the given vertex points to.
     * @param vertex The vertex whose successors are to be retrieved.
     * @return A vector of vertex indices representing successors.
     */
    std::vector<int> GetSuccessors(int vertex);
};

/**
 * @class DirectedAcyclicGraph
 * @brief A specialized graph representing a Directed Acyclic Graph (DAG).
 *
 * Extends BaseGraph and implements functionality specific to DAGs, such as
 * topological sorting, all-paths discovery, and Bellman-Ford shortest paths.
 */
class DirectedAcyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph;

    /**
     * @brief Adds a directed edge from source to destination with a given weight.
     */
    void AddEdge(int source, int destination, int weight) override;

    /**
     * @brief Performs topological sort using Kahn's algorithm.
     * @return A vector of vertices sorted in topological order.
     */
    std::vector<int> TopologicalSort();

    /**
     * @brief Finds all paths from source vertex s to destination vertex d.
     * @param s The source vertex.
     * @param d The destination vertex.
     * @return A vector of paths, where each path is represented as a vector of vertex indices.
     */
    std::vector<std::vector<int>> FindAllPaths(int s, int d);

    /**
     * @brief Utility recursive function to help find all paths from s to d.
     */
    void FindAllPathsUtil(int v, int d, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& all_paths);

    /**
     * @brief Computes shortest paths from a source using the Bellman-Ford algorithm.
     * @param source The vertex from which to calculate shortest paths.
     */
    void BellmanFordShortestPath(int source);
};

/**
 * @class DirectedCyclicGraph
 * @brief A directed graph that may contain cycles.
 *
 * Only implements directed edge addition. Cycle detection is inherited from BaseGraph.
 */
class DirectedCyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph;

    /**
     * @brief Adds a directed edge with weight, allowing potential cycles.
     */
    void AddEdge(int source, int destination, int weight) override;
};

/**
 * @class UndirectedAcyclicGraph
 * @brief Represents an undirected graph that is guaranteed to be acyclic (i.e., a forest).
 *
 * Includes additional logic for detecting cycles in undirected graphs using DFS with parent tracking.
 */
class UndirectedAcyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph;

    /**
     * @brief Adds an undirected edge with weight between two vertices.
     */
    void AddEdge(int source, int destination, int weight) override;

    /**
     * @brief Checks if the undirected graph contains a cycle.
     * @return true if a cycle is found, false otherwise.
     */
    bool HasCycle();

    /**
     * @brief Utility function for undirected cycle detection via DFS.
     * @param v The current vertex.
     * @param visited Tracks visited vertices.
     * @param parent The parent vertex in the DFS tree.
     * @return true if a cycle is found.
     */
    bool HasCycleUtil(int v, std::vector<bool>& visited, int parent);

    /**
     * @brief Computes the MST using Prim's algorithm for undirected acyclic graphs.
     * @param startVertex Starting vertex for Prim's algorithm.
     * @return A vector of MST edges.
     */
    std::vector<std::pair<int, int>> PrimMST(int startVertex) override;
};

/**
 * @class UndirectedCyclicGraph
 * @brief Represents an undirected graph that may contain cycles.
 *
 * Implements edge addition for undirected graphs without cycle constraints.
 */
class UndirectedCyclicGraph : public BaseGraph {
public:
    using BaseGraph::BaseGraph;

    /**
     * @brief Adds an undirected edge between two vertices, cycles allowed.
     */
    void AddEdge(int source, int destination, int weight) override;
};

}

#endif // GRAPH_H
