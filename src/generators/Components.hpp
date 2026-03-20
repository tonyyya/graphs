#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class ComponentsGenerator : public IGraphGenerator {
    int n, k;

public:
    ComponentsGenerator(int n, int k) : n(n), k(k) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);

        int size = n / k;
        int cur = 0;

        for (int c = 0; c < k; c++) {
            for (int i = cur; i < cur + size - 1; i++)
                g->addEdge(i, i + 1);

            cur += size;
        }

        return g;
    }
};
