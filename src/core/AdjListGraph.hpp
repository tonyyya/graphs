#pragma once
#include "IGraph.hpp"
#include <vector>
#include <stdexcept>

class AdjListGraph : public IGraph {
private:
    std::vector<std::vector<int>> adj;
    int edgeCount = 0;

public:
    AdjListGraph(int n = 0) : adj(n) {}

    int verticesCount() const override {
        return adj.size();
    }

    int edgesCount() const override {
        return edgeCount;
    }

    void addEdge(int u, int v) override {
        if (u >= verticesCount() || v >= verticesCount())
            throw std::out_of_range("Invalid vertex");

        if (hasEdge(u, v)) return;

        adj[u].push_back(v);
        adj[v].push_back(u);
        edgeCount++;
    }

    bool hasEdge(int u, int v) const override {
        if (u < 0 || v < 0 || u >= verticesCount() || v >= verticesCount())
            return false;
        for (int x : adj[u])
            if (x == v) return true;
        return false;
    }

    const std::vector<int>& neighbors(int v) const override {
        return adj[v];
    }
};
