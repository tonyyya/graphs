#pragma once
#include "IMetric.hpp"
#include <vector>
#include <queue>

class DiameterMetric : public IMetric {
private:
    int diameter;

public:
    void compute(const IGraph& g) override {
        diameter = 0;
        int n = g.verticesCount();

        for (int i = 0; i < n; i++) {
            diameter = std::max(diameter, bfs(g, i));
        }
    }

    int bfs(const IGraph& g, int start) {
        int n = g.verticesCount();
        std::vector<int> dist(n, -1);
        std::queue<int> q;

        dist[start] = 0;
        q.push(start);

        int maxd = 0;

        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (int to : g.neighbors(v)) {
                if (dist[to] == -1) {
                    dist[to] = dist[v] + 1;
                    maxd = std::max(maxd, dist[to]);
                    q.push(to);
                }
            }
        }

        return maxd;
    }

    int result() const { return diameter; }
};
