#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class StarGenerator : public IGraphGenerator {
    int n;

public:
    StarGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 1; i < n; i++)
            g->addEdge(0, i);

        return g;
    }
};
