#pragma once
#include "IGenerator.hpp"
#include <random>

class RandomGraphGenerator : public IGraphGenerator {
public:
    RandomGraphGenerator(int n, double probability) 
        : n_(n), prob_(probability) {}

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        std::mt19937 rng(42); // Фиксированный seed для воспроизводимости тестов
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < n_; ++i) {
            for (int j = i + 1; j < n_; ++j) {
                if (dist(rng) < prob_) {
                    g->addEdge(i, j);
                }
            }
        }
        return g;
    }

    const char* name() const override { return "Random(Gnp)"; }

private:
    int n_;
    double prob_;
};
