#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"
#include <cstdlib>

class RandomGenerator : public IGraphGenerator {
    int n;
    double p;

public:
    RandomGenerator(int n, double p) : n(n), p(p) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if ((double)rand() / RAND_MAX < p)
                    g->addEdge(i, j);

        return g;
    }
};
