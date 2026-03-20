#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class BridgesGenerator : public IGraphGenerator {
    int n;

public:
    BridgesGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n - 1; i++)
            g->addEdge(i, i + 1); // цепь → все ребра мосты

        return g;
    }
};
