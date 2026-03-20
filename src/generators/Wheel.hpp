#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class WheelGenerator : public IGraphGenerator {
    int n;

public:
    WheelGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 1; i < n; i++)
            g->addEdge(0, i);

        for (int i = 1; i < n; i++)
            g->addEdge(i, (i % (n - 1)) + 1);

        return g;
    }
};
