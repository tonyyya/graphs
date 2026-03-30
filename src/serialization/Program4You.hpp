#pragma once
#include <fstream>
#include <string>

class Program4You {
public:
    static void save(const IGraph& g, const std::string& filename) {
        std::ofstream file(filename);
        file << g.verticesCount() << " " << g.edgesCount() << "\n";
        for (int i = 0; i < g.verticesCount(); i++) {
            for (int j : g.neighbors(i)) {
                if (i < j) {
                    file << i << " " << j << "\n";
                }
            }
        }
    }
};
