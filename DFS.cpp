#include "DFS.hpp"

DFSAlgorithm::~DFSAlgorithm() {
}

void DFSAlgorithm::onVertexEnter(int v, int depth) {}
void DFSAlgorithm::onVertexLeave(int v, int depth) {}
void DFSAlgorithm::onEdge(int u, int v) {}
void DFSAlgorithm::onTreeEdge(int u, int v) {}
void DFSAlgorithm::onBackEdge(int u, int v) {}

void DFSAlgorithm::run(const Graph& g, int start) {
    graph = &g;
    int n = g.verticesCount();
    
    visited = new bool[n];
    parent = new int[n];
    depth = new int[n];
    tin = new int[n];
    tout = new int[n];
    
    //иициализация
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
        depth[i] = 0;
        tin[i] = -1;
        tout[i] = -1;
    }
    timer = 0;
    
    //запуск
    if (start >= 0 && start < n) {
        dfsRecursive(start, 0);
    }
    
    delete[] visited; //овобождаем память
    delete[] parent;
    delete[] depth;
    delete[] tin;
    delete[] tout;
}

void DFSAlgorithm::runAll(const Graph& g) { //запуск по всем компонента
    graph = &g;
    int n = g.verticesCount();
    
    visited = new bool[n];
    parent = new int[n];
    depth = new int[n];
    tin = new int[n];
    tout = new int[n];
    
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
        depth[i] = 0;
        tin[i] = -1;
        tout[i] = -1;
    }
    timer = 0;
    
    for (int i = 0; i < n; i++) {//обходим все вершины 
        if (!visited[i]) {
            dfsRecursive(i, 0);
        }
    }
    
    delete[] visited;
    delete[] parent;
    delete[] depth;
    delete[] tin;
    delete[] tout;
}

void DFSAlgorithm::dfsRecursive(int v, int d) { //рекурсивный обход
    visited[v] = true;
    depth[v] = d;
    tin[v] = timer++;
    
    onVertexEnter(v, d);
    
    int neighborCount;
    int* neighbors = graph->getNeighbors(v, neighborCount);
    
    for (int i = 0; i < neighborCount; i++) {
        int to = neighbors[i];
        
        onEdge(v, to);
        
        if (!visited[to]) {
            parent[to] = v;
            onTreeEdge(v, to);
            dfsRecursive(to, d + 1);
        } 
        else if (to != parent[v]) {
            onBackEdge(v, to);
        }
    }
    
    tout[v] = timer++;

    onVertexLeave(v, d);
}
