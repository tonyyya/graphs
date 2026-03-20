
#pragma once
#include "IGraphGenerator.hpp"

class ConnectedComponentsGenerator : public IGraphGenerator {
public:
    ConnectedComponentsGenerator(int n, int k) : n_(n), k_(k) {
        if (k > n) throw std::invalid_argument("k cannot be greater than n");
    }

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        
        int verticesPerComponent = n_ / k_;
        int remainder = n_ % k_;
        
        int currentVertex = 0;
        for (int comp = 0; comp < k_; comp++) {
            
            int compSize = verticesPerComponent + (comp < remainder ? 1 : 0);
            
            if (compSize == 1) {
                
                currentVertex++;
                continue;
            }
            
            int startVertex = currentVertex;
            for (int i = 0; i < compSize; i++) {
                int u = startVertex + i;
                int v = startVertex + (i + 1) % compSize;
                g->addEdge(u, v);
            }
            
            currentVertex += compSize;
        }
        
        return g;
    }

    const char* name() const override { return "ConnectedComponents(k)"; }

private:
    int n_, k_;
};
