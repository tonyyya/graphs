#pragma once
#include "IMetric.hpp"
#include <vector>

class BipartiteMetric : public IMetric {
    bool isBip;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        std::vector<int> color(n, -1);
        isBip = true;

        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                dfs(g, i, 0, color);
            }
        }
    }

    void dfs(const IGraph& g, int v, int c, std::vector<int>& color) {
        color[v] = c;

        for (int to : g.neighbors(v)) {
            if (color[to] == -1)
                dfs(g, to, 1 - c, color);
            else if (color[to] == c)
                isBip = false;
        }
    }

    bool result() const { return isBip; }
};
