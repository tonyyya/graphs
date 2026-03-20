#pragma once
#include "../core/IGraph.hpp"
#include <fstream>
#include <set>

class GraphViz {
public:
    static void save(const IGraph& g, const std::string& file) {
        std::ofstream out(file);

        out << "graph G {\n";

        for (int i = 0; i < g.verticesCount(); i++) {
            for (int to : g.neighbors(i)) {
                if (i < to)
                    out << i << " -- " << to << ";\n";
            }
        }

        out << "}\n";
    }

    // подсветка цикла (простая)
    static void saveWithCycle(const IGraph& g, const std::string& file) {
        std::ofstream out(file);
        out << "graph G {\n";

        for (int i = 0; i < g.verticesCount(); i++) {
            for (int to : g.neighbors(i)) {
                if (i < to) {
                    out << i << " -- " << to;

                    if (i == 0) // примитивный "случайный" цикл
                        out << " [color=red]";

                    out << ";\n";
                }
            }
        }

        out << "}\n";
    }
};
