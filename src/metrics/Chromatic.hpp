#pragma once
#include "IMetric.hpp"
#include <vector>
#include <set>

class ChromaticMetric : public IMetric {
private:
    int chromatic;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        std::vector<int> color(n, -1);

        color[0] = 0;

        for (int v = 1; v < n; v++) {
            std::set<int> used;

            for (int to : g.neighbors(v)) {
                if (color[to] != -1)
                    used.insert(color[to]);
            }

            int c = 0;
            while (used.count(c)) c++;

            color[v] = c;
        }

        chromatic = 0;
        for (int c : color)
            chromatic = std::max(chromatic, c);

        chromatic++;
    }

    int result() const { return chromatic; }
};
