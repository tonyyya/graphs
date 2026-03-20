#pragma once
#include "metric.hpp"

class MetricDensity : public metric {
private:
    double result;
    
public:
    void compute(const Graph& g) override {
        int n = g.verticesCount();  // число вершин
        int m = g.edgesCount();     // число рёбер (для неориентированного — реальное количество)
        if (n <= 1) {
            result = 0.0;
            return;
        }
        
        if (n == 2) {
            result = (m > 0) ? 1.0 : 0.0;
            return;
        }
        result = (2.0 * m) / (1.0 * n * (n - 1));
    }
    
    double getDoubleResult() const override { 
        return result; 
    }
};
