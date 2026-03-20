#pragma once
#include "IGenerator.hpp"

class CompleteGraphGenerator : public IGraphGenerator {
public:
    explicit CompleteGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        for (int i = 0; i < n_; ++i) {
            for (int j = i + 1; j < n_; ++j) {
                g->addEdge(i, j);
            }
        }
        return g;
    }

    const char* name() const override { return "Complete(Kn)"; }

private:
    int n_;
};
