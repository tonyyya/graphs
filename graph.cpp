#include "Graph.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstring>

Graph::Graph(int n) {
    vertexCount = n;
    edgeCount = 0;
    
    if (n == 0) {
        adj = nullptr;
        degrees = nullptr;
        capacities = nullptr;
    } else {
        adj = new int*[n];
        degrees = new int[n];
        capacities = new int[n];
        
        for (int i = 0; i < n; i++) {
            adj[i] = new int[1];
            degrees[i] = 0;
            capacities[i] = 1;
        }
    }
}

Graph::~Graph() {
    clean();
}

void Graph::clean() {
    if (adj != nullptr) {
        for (int i = 0; i < vertexCount; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        delete[] degrees;
        delete[] capacities;
        adj = nullptr;
        degrees = nullptr;
        capacities = nullptr;
    }
    vertexCount = 0;
    edgeCount = 0;
}
