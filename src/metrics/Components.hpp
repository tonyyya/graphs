#pragma once

#include "IMetric.hpp"
#include <vector>
#include <queue>

class ComponentsMetric : public IMetric {

private:
    int components_count;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        std::vector<bool> visited(n, false);
        components_count = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bfs(g, i, visited);
                components_count++;
            }
        }
    }

    void bfs(const IGraph& g, int start, std::vector<bool>& visited) {
        std::queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : g.neighbors(v)) {
                if (!visited[to]) {
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
    }

    int result() const { return components_count; }
};
