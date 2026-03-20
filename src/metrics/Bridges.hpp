#pragma once
#include "IMetric.hpp"
#include <vector>

class BridgesMetric : public IMetric {
private:
    int timer;
    std::vector<int> tin, low;
    std::vector<std::pair<int,int>> bridges;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        timer = 0;
        tin.assign(n, -1);
        low.assign(n, -1);
        bridges.clear();

        for (int i = 0; i < n; i++) {
            if (tin[i] == -1)
                dfs(g, i, -1);
        }
    }

    void dfs(const IGraph& g, int v, int p) {
        tin[v] = low[v] = timer++;

        for (int to : g.neighbors(v)) {
            if (to == p) continue;

            if (tin[to] != -1) {
                low[v] = std::min(low[v], tin[to]);
            } else {
                dfs(g, to, v);
                low[v] = std::min(low[v], low[to]);

                if (low[to] > tin[v]) {
                    bridges.emplace_back(v, to);
                }
            }
        }
    }

    const std::vector<std::pair<int,int>>& result() const {
        return bridges;
    }
};
