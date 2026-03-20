#pragma once
#include "Graph.hpp"

class DFSAlgorithm {
public:
    virtual ~DFSAlgorithm();
    
   
    void run(const Graph& g, int start = 0);  //запуск из одной вершины
    void runAll(const Graph& g); //запуск по всем компонентам связности

protected:
    virtual void onVertexEnter(int v, int depth);
    virtual void onVertexLeave(int v, int depth);
    virtual void onEdge(int u, int v);
    virtual void onTreeEdge(int u, int v);
    virtual void onBackEdge(int u, int v);

protected:
    const Graph* graph;
    bool* visited;
    int* parent;
    int* depth;
    int* tin;       
    int* tout;      
    int timer;

    void dfsRecursive(int v, int d); //рекурсивный обход
};
