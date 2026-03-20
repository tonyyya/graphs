#pragma once
#include "../Graph.hpp"
#include <memory>

class IGraphGenerator {
public:
    virtual ~IGraphGenerator() = default;
    
    virtual std::unique_ptr<Graph> generate() const = 0;
    
    virtual const char* name() const = 0;
};
