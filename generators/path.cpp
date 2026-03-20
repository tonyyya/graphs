#pragma once
#include "IGenerator.hpp"

class PathGraphGenerator : public IGraphGenerator {
public:
    explicit PathGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ < 2) throw std::invalid_argument("Path needs at least 2 vertices");
        auto g = std::make_unique<Graph>(n_);
        for (int i = 0; i < n_ - 1; ++i) {
            g->addEdge(i, i + 1); // Просто цепочка
        }
        return g;
    }

    const char* name() const override { return "Path(Pn)"; }

private:
    int n_;
};
