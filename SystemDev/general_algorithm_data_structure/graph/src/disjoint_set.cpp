#include "../include/disjoint_set.h"

DisjointSet::DisjointSet(int n) : parent_(n), rank_(n, 0) {
    for (int i = 0; i < n; ++i)
        parent_[i] = i;
}

int DisjointSet::Find(int x) {
    if (parent_[x] != x)
        parent_[x] = Find(parent_[x]);  // Path compression
    return parent_[x];
}

void DisjointSet::Unite(int x, int y) {
    int x_root = Find(x);
    int y_root = Find(y);
    if (x_root == y_root) return;

    if (rank_[x_root] < rank_[y_root])
        parent_[x_root] = y_root;
    else if (rank_[x_root] > rank_[y_root])
        parent_[y_root] = x_root;
    else {
        parent_[y_root] = x_root;
        rank_[x_root]++;
    }
}
