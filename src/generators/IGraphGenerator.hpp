#pragma once
#include "../core/IGraph.hpp"
#include <memory>

class IGraphGenerator {
public:
    virtual ~IGraphGenerator() = default;
    virtual std::unique_ptr<IGraph> generate() const = 0;
};
