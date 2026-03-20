#pragma once
#include "metric.hpp"

class MetricChromatic : public metric { //верхняя оценка хроматического числа через жадную расскаску
private:
    int result;
    
public:
    void compute(const Graph& g) override {
        int n = g.verticesCount();
        int* colors = new int[n];
        
        for (int i = 0; i < n; i++) colors[i] = -1;
        
        result = 0;
        
        for (int v = 0; v < n; v++) {
            bool* used = new bool[n + 1];
            for (int i = 0; i <= n; i++) used[i] = false;
            
            int count; // смотрим цвета соседей
            int* neighbors = g.getNeighbors(v, count);
            for (int i = 0; i < count; i++) {
                int to = neighbors[i];
                if (colors[to] != -1) {
                    used[colors[to]] = true;
                }
            }
            int c = 0;   // берём первый свободный цвет
            while (used[c]) c++;
            colors[v] = c;
            
            if (c + 1 > result) result = c + 1;
            delete[] used;
        }
        
        delete[] colors;
    }
    
    int getIntResult() const override { return result; }
};
