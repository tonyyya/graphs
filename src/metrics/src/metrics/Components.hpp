#pragma once
#include "IMetric.hpp"
#include "../algorithms/DFS.hpp"

class ComponentsMetric : public IMetric, public DFSVisitor {
private:
    int comp;
    bool newComp;

public:
    void compute(const IGraph& g) override {
        comp = 0;
        newComp = true;
        DFS::run(g, *this);
    }

    void onEnter(int v) override {
        if (newComp) {
            comp++;
            newComp = false;
        }
    }

    int result() const { return comp;


}
};
