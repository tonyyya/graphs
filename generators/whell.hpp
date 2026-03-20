#pragma once
#include "IGenerator.hpp"

class WheelGraphGenerator : public IGraphGenerator {
public:
    explicit WheelGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ < 4) throw std::invalid_argument("Wheel needs at least 4 vertices");
        auto g = std::make_unique<Graph>(n_);
        
        int center = 0; 
        int rimStart = 1; 
        int rimSize = n_ - 1;

        for (int i = 0; i < rimSize; ++i) {
            int u = rimStart + i;
            int v = rimStart + (i + 1) % rimSize;
            g->addEdge(u, v);              
            g->addEdge(center, u);
        }
        return g;
    }

    const char* name() const override { return "Wheel(Wn)"; }

private:
    int n_;
};
