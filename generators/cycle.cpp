#pragma once
#include "IGenerator.hpp"

class CycleGraphGenerator : public IGraphGenerator {
public:
    explicit CycleGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ < 3) throw std::invalid_argument("Cycle needs at least 3 vertices");
        auto g = std::make_unique<Graph>(n_);
        for (int i = 0; i < n_; ++i) {
            g->addEdge(i, (i + 1) % n_); 
        }
        return g;
    }

    const char* name() const override { return "Cycle(Cn)"; }

private:
    int n_;
};
