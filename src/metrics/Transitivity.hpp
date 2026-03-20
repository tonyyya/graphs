#pragma once
#include "IMetric.hpp"

class TransitivityMetric : public IMetric {
private:
    double res;

public:
    void compute(const IGraph& g) override {
        int n = g.verticesCount();
        int triangles = 0;
        int triples = 0;

        for (int i = 0; i < n; i++) {
            const auto& ni = g.neighbors(i);

            for (int j = 0; j < ni.size(); j++) {
                for (int k = j + 1; k < ni.size(); k++) {
                    triples++;

                    if (g.hasEdge(ni[j], ni[k]))
                        triangles++;
                }
            }
        }

        if (triples == 0) res = 0;
        else res = (double)triangles / triples;
    }

    double result() const { return res; }
};
