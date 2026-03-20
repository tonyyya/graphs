#pragma once
#include "../core/IGraph.hpp"
#include <memory>
#include <string>

class IParser {
public:
    virtual ~IParser() = default;
    virtual std::unique_ptr<IGraph> parse(const std::string& file) = 0;
};
