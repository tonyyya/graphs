#pragma once
#include "DFS.hpp"

class MetricBridges : public DFSAlgorithm, public metric {
private:
    int* low;
    int count;
    int timer;
    
public:
    MetricBridges() : low(nullptr), count(0), timer(0) {}
    
    void compute(const Graph& g) override {
        int n = g.verticesCount();
        
        low = new int[n];
        visited = new bool[n];
        parent = new int[n];
        tin = new int[n];
        
        for (int i = 0; i < n; i++) {
            visited[i] = false;
            parent[i] = -1;
            tin[i] = -1;
            low[i] = -1;
        }
        
        timer = 0;
        count = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfsBridge(g, i);
            }
        }
        
        delete[] low;
        delete[] visited;
        delete[] parent;
        delete[] tin;
    }
    
    void dfsBridge(const Graph& g, int v) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        
        int count;
        int* neighbors = g.getNeighbors(v, count);
        
        for (int i = 0; i < count; i++) {
            int to = neighbors[i];
            
            if (to == parent[v]) continue;  // ребро к родителю
            
            if (visited[to]) {
                // Обратное ребро
                if (tin[to] < low[v]) low[v] = tin[to];
            } else {
                parent[to] = v;
                dfsBridge(g, to);
                
                if (low[to] < low[v]) low[v] = low[to];
                
                if (low[to] > tin[v]) {
                    this->count++;
                }
            }
        }
    }
    
    int getIntResult() const override { return count; }
};
