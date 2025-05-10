#include "../include/DisjointSet.h"

DisjointSet::DisjointSet(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int DisjointSet::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // Path compression
    return parent[x];
}

void DisjointSet::unite(int x, int y) {
    int xRoot = find(x);
    int yRoot = find(y);
    if (xRoot == yRoot) return;

    if (rank[xRoot] < rank[yRoot])
        parent[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}
