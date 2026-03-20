#pragma once
#include "metric.hpp"

class MetricBipartite : public metric { //проверяем через раскраску
private:
    bool result;
  
    bool bfsColor(const Graph& g, int start, int* color) { //раскаска в 2 цвета
        int n = g.verticesCount();
        int* queue = new int[n];
        int head = 0, tail = 0;
        
        color[start] = 0;
        queue[tail++] = start;
        
        while (head < tail) {
            int v = queue[head++];
            int count;
            int* neighbors = g.getNeighbors(v, count);
            
            for (int i = 0; i < count; i++) {
                int to = neighbors[i];
                
                if (color[to] == -1) {
                    color[to] = 1 - color[v];  // противоположный цвет
                    queue[tail++] = to;
                } else if (color[to] == color[v]) {
                    delete[] queue;
                    return false;  // конфликт цветов, тогда не двудольный
                }
            }
        }
        
        delete[] queue;
        return true;
    }
    
public:
    void compute(const Graph& g) override {
        int n = g.verticesCount();
        int* color = new int[n];
        
        for (int i = 0; i < n; i++) color[i] = -1;
        
        result = true;
        for (int i = 0; i < n && result; i++) {
            if (color[i] == -1) {
                result = bfsColor(g, i, color);
            }
        }
        
        delete[] color;
    }
    
    bool getBoolResult() const override { return result; }
};
