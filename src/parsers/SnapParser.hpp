#pragma once
#include "IParser.hpp"
#include "../core/AdjListGraph.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>

class SnapParser : public IParser {
public:
    std::unique_ptr<IGraph> parse(const std::string& filename) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::set<int> vertices;
        std::vector<std::pair<int, int>> edges;

        std::string line;
        int maxVertex = -1;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            std::istringstream iss(line);
            int u, v;
            if (iss >> u >> v) {
                vertices.insert(u);
                vertices.insert(v);
                edges.push_back({u, v});
                maxVertex = std::max(maxVertex, std::max(u, v));
            }
        }

        int n = maxVertex + 1;
        auto graph = std::make_unique<AdjListGraph>(n);

        for (const auto& edge : edges) {
            graph->addEdge(edge.first, edge.second);
        }

        return graph;
    }
};
