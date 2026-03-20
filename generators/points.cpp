
#pragma once
#include "IGraphGenerator.hpp"

class ArticulationPointsGenerator : public IGraphGenerator {
public:
    ArticulationPointsGenerator(int n, int k) : n_(n), k_(k) {
        if (k >= n) throw std::invalid_argument("k must be less than n");
        if (k < 0) throw std::invalid_argument("k cannot be negative");
    }

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        
        if (k_ == 0) {
            
            for (int i = 0; i < n_; i++) {
                g->addEdge(i, (i + 1) % n_);
            }
            return g;
        }
        
       
        int verticesNeeded = k_ + 2;  
        if (n_ < verticesNeeded) {
            throw std::invalid_argument("Not enough vertices for k articulation points");
        }
        
        
        int currentVertex = 0;
        
       
        g->addEdge(0, 1);
        g->addEdge(1, 2);
        g->addEdge(0, 2);
        currentVertex = 2;
        / Остальные k блоков, каждый добавляет одну точку сочленения
        for (int i = 0; i < k_ && currentVertex < n_ - 1; i++) {
            
            int articulationPoint = currentVertex;
            
            
            int newV1 = currentVertex + 1;
            int newV2 = (currentVertex + 2 < n_) ? currentVertex + 2 : 1;
            
            g->addEdge(articulationPoint, newV1);
            g->addEdge(newV1, newV2);
            g->addEdge(articulationPoint, newV2);
            
            currentVertex += 2;
        }
        
       
        while (currentVertex < n_) {
            g->addEdge(currentVertex - 1, currentVertex);
            currentVertex++;
        }
        
        return g;
    }

    const char* name() const override { return "ArticulationPoints(k)"; }

private:
    int n_, k_;
};
