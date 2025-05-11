#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

/**
 * @class DisjointSet
 * @brief Implements Union-Find (Disjoint Set Union) with path compression and union by rank.
 */
class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    /// Initialize n disjoint sets (0 to n-1).
    DisjointSet(int n);

    /// Find the representative (root) of the set containing x.
    int find(int x);

    /// Merge the sets that contain x and y.
    void unite(int x, int y);
};

#endif
