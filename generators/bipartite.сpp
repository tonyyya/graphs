#pragma once
#include "IGenerator.hpp"

class BipartiteGraphGenerator : public IGraphGenerator {
public:
    BipartiteGraphGenerator(int n, int m) : n_(n), m_(m) {}

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_ + m_);
        
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < m_; ++j) {
                g->addEdge(i, n_ + j);
            }
        }
        return g;
    }

    const char* name() const override { return "Bipartite(Knm)"; }

private:
    int n_, m_;
};
