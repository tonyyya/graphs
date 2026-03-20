#pragma once
#include "DFS.hpp"

class MetricComponents : public DFSAlgorithm, public IMetric {
private:
    int count;
    
public:
    MetricComponents() : count(0) {}
    
    void compute(const Graph& g) override {
        count = 0;
        runAll(g);  // запускаем обход для каждой компоненты
    }
    void onVertexEnter(int v, int d) override {
        if (d == 0) count++;
    }
    
    int getIntResult() const override { return count; }
};
