#pragma once
#include <vector>

class IGraph {
public:
    virtual ~IGraph() = default;

    virtual int verticesCount() const = 0;
    virtual int edgesCount() const = 0;

    virtual void addEdge(int u, int v) = 0;
    virtual bool hasEdge(int u, int v) const = 0;

    virtual const std::vector<int>& neighbors(int v) const = 0;
};
