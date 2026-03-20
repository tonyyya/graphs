#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"
#include <cstdlib>

class TreeGenerator : public IGraphGenerator {
    int n;

public:
    TreeGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 1; i < n; i++) {
            int parent = rand() % i;
            g->addEdge(i, parent);
        }

        return g;
    }
};
