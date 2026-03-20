#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class HalinGenerator : public IGraphGenerator {
public:
    std::unique_ptr<IGraph> generate() const override {
        int n = 6;
        auto g = std::make_unique<AdjListGraph>(n);

        g->addEdge(0,1);
        g->addEdge(0,2);
        g->addEdge(1,3);
        g->addEdge(1,4);
        g->addEdge(2,5);

        g->addEdge(3,4);
        g->addEdge(4,5);
        g->addEdge(5,3);

        return g;
    }
};
