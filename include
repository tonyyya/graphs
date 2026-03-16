#pragma once

class Graph {
public:
    
    Graph(int n = 0);
    ~Graph();
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);

    
    int addVertex();
    bool hasVertex(int v) const;
    int verticesCount() const;

    
    void addEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    int edgesCount() const;
    void removeEdge(int u, int v);

    
    int* getNeighbors(int v, int& count) const;
    int getDegree(int v) const;
    bool isLeaf(int v) const;

    
    void clear();

private:
    int** adj;          
    int* degrees;       
    int* capacities;    
    int vertexCount;    
    int edgeCount;      

    
    void resizeNeighbors(int v);
    void clean();
    void copyFrom(const Graph& other);
    void validateVertex(int v) const;
};
