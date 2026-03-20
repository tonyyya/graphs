#pragma once
#include "IParser.hpp"
#include "../core/AdjListGraph.hpp"
#include <fstream>
#include <vector>

class EdgeListParser : public IParser {
public:
    std::unique_ptr<IGraph> parse(const std::string& file) override {
        std::ifstream in(file);

        int u, v, maxV = -1;
        std::vector<std::pair<int,int>> edges;

        while (in >> u >> v) {
            edges.push_back({u,v});
            maxV = std::max(maxV, std::max(u,v));
        }

        auto g = std::make_unique<AdjListGraph>(maxV + 1);

        for (auto& e : edges)
            g->addEdge(e.first, e.second);

        return g;
    }
};
