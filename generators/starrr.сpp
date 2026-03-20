#pragma once
#include "IGenerator.hpp"

class StarGraphGenerator : public IGraphGenerator {
public:
    explicit StarGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ < 2) throw std::invalid_argument("Star needs at least 2 vertices");
        auto g = std::make_unique<Graph>(n_);
        for (int i = 1; i < n_; ++i) {
            g->addEdge(0, i); // Центр всегда 0
        }
        return g;
    }

    const char* name() const override { return "Star(Sn)"; }

private:
    int n_;
};
