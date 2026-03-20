#pragma once
#include "metric.hpp"
//мера треугольности графа
class MetricTransitivity : public metric {
private:
    double result;
    
public:
    void compute(const Graph& g) override {
        int n = g.verticesCount();
        int triangles = 0;  // количество треугольников
        int triads = 0;     // количество пар соседей
        
        for (int v = 0; v < n; v++) {
            int count;
            int* neighbors = g.getNeighbors(v, count);
          
            int* neigh = new int[count];
            for (int i = 0; i < count; i++) neigh[i] = neighbors[i];
            triads += count * (count - 1) / 2;
    
            for (int i = 0; i < count; i++) { // соединены ли соседи между собой (треугольники)
                for (int j = i + 1; j < count; j++) {
                    if (g.hasEdge(neigh[i], neigh[j])) {
                        triangles++;
                    }
                }
            }
            delete[] neigh;
        }
        
        // Транзитивность = 3*треугольники / триады
        result = (triads > 0) ? (3.0 * triangles / triads) : 0.0;
    }
    
    double getDoubleResult() const override { return result; }
};
