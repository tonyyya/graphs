#pragma once
#include "DFS.hpp"

class MetricArticulationPoints : public DFSAlgorithm, public IMetric {
private:
    int* low;
    int count;
    int timer;
    
public:
    MetricArticulationPoints() : low(nullptr), count(0), timer(0) {}
    
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
        
        for (int i = 0; i < n; i++) {  // обходим все компоненты
            if (!visited[i]) {
                dfsAP(g, i);
            }
        }
        
        delete[] low;
        delete[] visited;
        delete[] parent;
        delete[] tin;
    }
    
    void dfsAP(const Graph& g, int v) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children = 0;
        
        int count;
        int* neighbors = g.getNeighbors(v, count);
        
        for (int i = 0; i < count; i++) {
            int to = neighbors[i];
            
            if (visited[to]) {
                if (tin[to] < low[v]) low[v] = tin[to];  //обратное ребро
            } else {
                parent[to] = v;
                children++;
                dfsAP(g, to);
                
                if (low[to] < low[v]) low[v] = low[to];
              
                if (parent[v] != -1 && low[to] >= tin[v]) {
                    count++;
                }
            }
        }
        if (parent[v] == -1 && children > 1) {     //корень -точка сочленения, если у него >= 2 детей
            count++;
        }
    }
    
    int getIntResult() const override { return count; }
};
