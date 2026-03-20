#pragma once
#include "IMetric.hpp"

class MetricDiameter : public IMetric {
private:
    int result;
    
    int bfsMaxDist(const Graph& g, int start) {   // бфс из одной вершины, возвращает макс расстояние
        int n = g.verticesCount();
        int* dist = new int[n];
        int* queue = new int[n];
        
        for (int i = 0; i < n; i++) dist[i] = -1;
        
        int head = 0, tail = 0;
        dist[start] = 0;
        queue[tail++] = start;
        int maxDist = 0;
        
        while (head < tail) {
            int v = queue[head++];
            int count;
            int* neighbors = g.getNeighbors(v, count);
            
            for (int i = 0; i < count; i++) {
                int to = neighbors[i];
                if (dist[to] == -1) {
                    dist[to] = dist[v] + 1;
                    if (dist[to] > maxDist) maxDist = dist[to];
                    queue[tail++] = to;
                }
            }
        }
        
        delete[] dist;
        delete[] queue;
        return maxDist;
    }
    
public:
    void compute(const Graph& g) override {
        int n = g.verticesCount();
        result = 0;
        for (int i = 0; i < n; i++) {
            int d = bfsMaxDist(g, i);
            if (d > result) result = d;
        }
    }
    
    int getIntResult() const override { return result; }
};
