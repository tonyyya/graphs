#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"
#include <random>
#include <stdexcept>

class CubicGenerator : public IGraphGenerator {
    int n;

public:
    CubicGenerator(int n) : n(n) {}

    std::unique_ptr<IGraph> generate() const override {
        if (n < 4 || n % 2 != 0) {
            throw std::runtime_error("Cubic graph requires even n >= 4");
        }

        auto g = std::make_unique<AdjListGraph>(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, n-1);

        for (int i = 0; i < n; i++) {
            g->addEdge(i, (i + 1) % n);
        }

        for (int i = 0; i < n; i++) {
            int degree = g->neighbors(i).size();
            while (degree < 3) {
                int j = dis(gen);
                if (i != j && !g->hasEdge(i, j) && g->neighbors(j).size() < 3) {
                    g->addEdge(i, j);
                    degree++;
                }
            }
        }

        return g;
    }
};
