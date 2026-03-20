#pragma once
#include "../core/IGraph.hpp"
#include "DFSVisitor.hpp"
#include <vector>

class DFS {
public:
    static void run(const IGraph& g, DFSVisitor& vis) {
        int n = g.verticesCount();
        std::vector<bool> used(n, false);

        for (int i = 0; i < n; i++)
            if (!used[i])
                dfs(g, i, used, vis);
    }

private:
    static void dfs(const IGraph& g, int v,
                    std::vector<bool>& used,
                    DFSVisitor& vis) {

        used[v] = true;
        vis.onEnter(v);

        for (int to : g.neighbors(v)) {
            vis.onEdge(v, to);
            if (!used[to])
                dfs(g, to, used, vis);
        }

        vis.onExit(v);
    }
};
