#pragma once
#include "IParser.hpp"
#include "../core/AdjListGraph.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

class DimacsParser : public IParser {
public:
    std::unique_ptr<IGraph> parse(const std::string& filename) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        int n = 0, m = 0;
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            if (line[0] == 'c') {
                continue;
            }
            else if (line[0] == 'p') {
                std::istringstream iss(line);
                std::string p, type;
                iss >> p >> type >> n >> m;
                if (type != "edge") {
                    throw std::runtime_error("Invalid DIMACS format");
                }
            }
            else if (line[0] == 'e') {
                break;
            }
        }

        if (n == 0) {
            throw std::runtime_error("No problem line found");
        }

        auto graph = std::make_unique<AdjListGraph>(n);

        std::istringstream iss(line);
        std::string e;
        int u, v;
        iss >> e >> u >> v;
        graph->addEdge(u - 1, v - 1);

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == 'c') continue;

            std::istringstream iss(line);
            std::string e;
            int u, v;
            if (iss >> e >> u >> v) {
                if (e == "e") {
                    graph->addEdge(u - 1, v - 1);
                }
            }
        }

        return graph;
    }
};
