#pragma once
#include "IGraphGenerator.hpp"

class BridgesGenerator : public IGraphGenerator {
public:
    BridgesGenerator(int n, int k) : n_(n), k_(k) {
        if (k >= n) throw std::invalid_argument("k must be less than n");
        if (k < 0) throw std::invalid_argument("k cannot be negative");
    }

    std::unique_ptr<Graph> generate() const override {
        auto g = std::make_unique<Graph>(n_);
        
        if (k_ == 0) {
            // Граф без мостов — создаём цикл
            for (int i = 0; i < n_; i++) {
                g->addEdge(i, (i + 1) % n_);
            }
            return g;
        }
        
        // Создаём k+1 блок, соединённых k мостами
        int verticesPerBlock = n_ / (k_ + 1);
        int remainder = n_ % (k_ + 1);
        
        int currentVertex = 0;
        int prevBlockLastVertex = -1;
        
        for (int block = 0; block <= k_; block++) {
            int blockSize = verticesPerBlock + (block < remainder ? 1 : 0);
            int startVertex = currentVertex;
            
            // Создаём блок (цикл для связности внутри блока)
            if (blockSize >= 3) {
                for (int i = 0; i < blockSize; i++) {
                    int u = startVertex + i;
                    int v = startVertex + (i + 1) % blockSize;
                    g->addEdge(u, v);
                }
            } else if (blockSize == 2) {
                g->addEdge(startVertex, startVertex + 1);
            }
            // blockSize == 1: изолированная вершина в блоке
            
            // Соединяем с предыдущим блоком мостом
            if (block > 0 && prevBlockLastVertex >= 0) {
                g->addEdge(prevBlockLastVertex, startVertex);
            }
            
            prevBlockLastVertex = startVertex + blockSize - 1;
            currentVertex += blockSize;
        }
        
        return g;
    }
const char* name() const override { return "Bridges(k)"; }

private:
    int n_, k_;
};
