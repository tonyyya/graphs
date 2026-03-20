#pragma once
#include "IGenerator.hpp"
#include <random>
#include <chrono>

class TreeGraphGenerator : public IGraphGenerator {
public:
    explicit TreeGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ <= 0) throw std::invalid_argument("N must be > 0");
        auto g = std::make_unique<Graph>(n_);
        
        if (n_ == 1) return g;

        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        
        for (int i = 1; i < n_; ++i) {
            std::uniform_int_distribution<int> dist(0, i - 1);
            int parent = dist(rng);
            g->addEdge(parent, i);
        }
        return g;
    }

    const char* name() const override { return "Tree(Tn)"; }

private:
    int n_;
};
