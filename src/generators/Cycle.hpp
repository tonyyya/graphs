#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class CycleGenerator : public IGraphGenerator {
    int n;

public:
    CycleGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n; i++)
            g->addEdge(i, (i + 1) % n);

        return g;
    }
};
