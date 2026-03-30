#pragma once
#include "IGraphGenerator.hpp"
#include "../core/AdjListGraph.hpp"

class ArticulationGenerator : public IGraphGenerator {
    int n;
    int k;

public:
    ArticulationGenerator(int n, int k) : n(n), k(k) {}

    std::unique_ptr<IGraph> generate() const override {
        auto g = std::make_unique<AdjListGraph>(n);
        
        int vertices_per_articulation = (n - k) / k;
        if (vertices_per_articulation < 2) vertices_per_articulation = 2;
        
        int current_vertex = k;
        
        for (int art = 0; art < k && current_vertex < n; ++art) {
            std::vector<int> component_vertices;
            component_vertices.push_back(art);
            
            for (int i = 0; i < vertices_per_articulation && current_vertex < n; ++i) {
                component_vertices.push_back(current_vertex);
                g->addEdge(art, current_vertex);
                current_vertex++;
            }
            
            for (size_t i = 1; i < component_vertices.size(); ++i) {
                if (i + 1 < component_vertices.size()) {
                    g->addEdge(component_vertices[i], component_vertices[i + 1]);
                }
            }
            
            if (art > 0) {
                g->addEdge(art - 1, art);
            }
        }
        
        return g;
    }
};
