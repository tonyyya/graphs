#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class TwoBridgesGenerator : public IGraphGenerator {
    int n;

public:
    TwoBridgesGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n - 2; i++)
            g->addEdge(i, i + 1);

        g->addEdge(0, 2); // убираем часть мостов

        return g;
    }
};
