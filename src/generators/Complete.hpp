#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class CompleteGenerator : public IGraphGenerator {
    int n;

public:
    CompleteGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                g->addEdge(i, j);

        return g;
    }
};
