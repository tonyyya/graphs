#pragma once
#include "IMetric.hpp"

class DensityMetric : public IMetric {
    double res;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        int m = g.edgesCount();

        if (n <= 1) res = 0;
        else res = (2.0 * m) / (n * (n - 1));
    }

    double result() const { return res; }
};
