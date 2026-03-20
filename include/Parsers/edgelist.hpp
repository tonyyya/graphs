#pragma once
#include "IParser.hpp"
#include <fstream>
#include <sstream>

class EdgeListParser : public IGraphParser {
public:
    std::unique_ptr<Graph> parse(const std::string& filename) const override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        int maxVertex = -1;
        std::vector<std::pair<int, int>> edges;
        
        int u, v;
        while (file >> u >> v) {
            edges.push_back({u, v});
            maxVertex = std::max(maxVertex, std::max(u, v));
        }
        
        auto g = std::make_unique<Graph>(maxVertex + 1);
        for (const auto& edge : edges) {
            g->addEdge(edge.first, edge.second);
        }
        
        return g;
    }

    const char* name() const override { return "EdgeList"; }
};
