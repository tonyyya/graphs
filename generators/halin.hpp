#pragma once
#include "IGraphGenerator.hpp"
#include <vector>

class HalinGraphGenerator : public IGraphGenerator {
public:
    explicit HalinGraphGenerator(int n) : n_(n) {}

    std::unique_ptr<Graph> generate() const override {
        if (n_ < 4) throw std::invalid_argument("Halin graph needs at least 4 vertices");
        auto g = std::make_unique<Graph>(n_);
        
        
        for (int i = 1; i < n_; ++i) {
            g->addEdge(0, i);
        }
        
       
        std::vector<int> leaves;
        for (int i = 1; i < n_; ++i) {
            leaves.push_back(i);
        }
      
        for (size_t i = 0; i < leaves.size(); ++i) {
            int u = leaves[i];
            int v = leaves[(i + 1) % leaves.size()];
            g->addEdge(u, v);
        }
        
        return g;
    }

    const char* name() const override { return "Halin"; }

private:
    int n_;
};
