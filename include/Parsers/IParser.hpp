#pragma once
#include "../Graph.hpp"
#include <memory>
#include <string>

class IGraphParser {
public:
    virtual ~IGraphParser() = default;
    virtual std::unique_ptr<Graph> parse(const std::string& filename) const = 0;
    virtual const char* name() const = 0;
};
