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
Graph::Graph(const Graph& other) {
    adj = nullptr;
    degrees = nullptr;
    capacities = nullptr;
    copyFrom(other);
}
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        clean();
        copyFrom(other);
    }
    return *this;
}
void Graph::copyFrom(const Graph& other) {
    vertexCount = other.vertexCount;
    edgeCount = other.edgeCount;
    
    if (vertexCount == 0) {
        adj = nullptr;
        degrees = nullptr;
        capacities = nullptr;
        return;
    }
adj = new int*[vertexCount];
    degrees = new int[vertexCount];
    capacities = new int[vertexCount];
    
    for (int i = 0; i < vertexCount; i++) {
        capacities[i] = other.capacities[i];
        degrees[i] = other.degrees[i];
        adj[i] = new int[capacities[i]];
        for (int j = 0; j < degrees[i]; j++) {
            adj[i][j] = other.adj[i][j];
        }
    }
}
void Graph::validateVertex(int v) const {
    if (v < 0 || v >= vertexCount) {
        throw std::out_of_range("Vertex " + std::to_string(v) + " does not exist");
    }
}
int Graph::addVertex() {
    int newV = vertexCount;
    vertexCount++;
}
int** newAdj = new int*[vertexCount];
    int* newDegrees = new int[vertexCount];
    int* newCapacities = new int[vertexCount];
}

for (int i = 0; i < newV; i++) {
        newAdj[i] = adj[i];
        newDegrees[i] = degrees[i];
        newCapacities[i] = capacities[i];
    }
newAdj[newV] = new int[1];
    newDegrees[newV] = 0;
    newCapacities[newV] = 1;

if (adj != nullptr) {
        delete[] adj;
        delete[] degrees;
        delete[] capacities;
}
    
adj = newAdj;
    degrees = newDegrees;
    capacities = newCapacities;
    
    return newV;
}

bool Graph::hasVertex(int v) const {
    return v >= 0 && v < vertexCount;
}
