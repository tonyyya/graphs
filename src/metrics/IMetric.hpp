#pragma once
#include "../core/IGraph.hpp"

class IMetric {
public:
    virtual ~IMetric() = default;
    virtual void compute(const IGraph& g) = 0;
};
