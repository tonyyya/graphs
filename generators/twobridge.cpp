
#pragma once
#include "IGraphGenerator.hpp"

class TwoBridgesGenerator : public IGraphGenerator {
public:
    TwoBridgesGenerator(int n, int k) : n_(n), k_(k) {
        if (k < 0) throw std::invalid_argument("k cannot be negative");
        if (n < 3 * k + 3) throw std::invalid_argument("Not enough vertices for k 2-bridges");
    }

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        
        if (k_ == 0) {
            for (int i = 0; i < n_; i++) {
                g->addEdge(i, (i + 1) % n_);
            }
            return g;
        }
        
        
        int currentVertex = 0;
        
        for (int i = 0; i < k_; i++) {
            
            int a = currentVertex;
            int b = currentVertex + 1;
            int c = currentVertex + 2;

            if (a + 2 < n_) {
                g->addEdge(a, a + 1);
                g->addEdge(a + 1, a + 2);
                g->addEdge(a, a + 2);
            }
            
           
            if (b < n_ && c < n_) {
                g->addEdge(b, c);
            }
            
           
            if (c + 1 < n_) {
                g->addEdge(c, c + 1);
                if (c + 2 < n_) {
                    g->addEdge(c + 1, c + 2);
                    g->addEdge(c, c + 2);
                }
            }
            
            currentVertex += 3;
        }
        
        
        while (currentVertex < n_) {
            g->addEdge(currentVertex - 1, currentVertex);
            currentVertex++;
        }
        
        return g;
    }

    const char* name() const override { return "TwoBridges(k)"; }
private:
    int n_, k_;
};
