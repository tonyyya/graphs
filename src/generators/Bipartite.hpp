#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class CompleteBipartiteGenerator : public IGraphGenerator {
    int n, m;

public:
    CompleteBipartiteGenerator(int n, int m) : n(n), m(m) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n + m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g->addEdge(i, n + j);
            }
        }
        return g;
    }
};
