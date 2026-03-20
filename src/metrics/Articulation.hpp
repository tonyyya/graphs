#pragma once
#include "IMetric.hpp"
#include <vector>

class ArticulationMetric : public IMetric {
private:
    int timer;
    std::vector<int> tin, low;
    std::vector<bool> used;
    std::vector<bool> isCut;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        timer = 0;
        tin.assign(n, -1);
        low.assign(n, -1);
        used.assign(n, false);
        isCut.assign(n, false);

        for (int i = 0; i < n; i++)
            if (!used[i])
                dfs(g, i, -1);
    }

    void dfs(const IGraph& g, int v, int p) {
        used[v] = true;
        tin[v] = low[v] = timer++;
        int children = 0;

        for (int to : g.neighbors(v)) {
            if (to == p) continue;

            if (used[to]) {
                low[v] = std::min(low[v], tin[to]);
            } else {
                dfs(g, to, v);
                low[v] = std::min(low[v], low[to]);

                if (low[to] >= tin[v] && p != -1)
                    isCut[v] = true;

                children++;
            }
        }

        if (p == -1 && children > 1)
            isCut[v] = true;
    }

    std::vector<int> result() const {
        std::vector<int> res;
        for (int i = 0; i < isCut.size(); i++)
            if (isCut[i]) res.push_back(i);
        return res;
    }
};
