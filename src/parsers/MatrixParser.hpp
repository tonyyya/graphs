#pragma once
#include "IParser.hpp"
#include "../core/AdjListGraph.hpp"
#include <fstream>
#include <vector>

class MatrixParser : public IParser {
public:
    std::unique_ptr<IGraph> parse(const std::string& file) override {
        std::ifstream in(file);

        int n;
        in >> n;

        auto g = std::make_unique<AdjListGraph>(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x;
                in >> x;
                if (x && i < j)
                    g->addEdge(i, j);
            }
        }

        return g;
    }
};
