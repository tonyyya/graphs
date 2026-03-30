#pragma once
#include "../core/IGraph.hpp"
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

class GraphViz {
private:
    static std::vector<std::pair<int, int>> findSpanningTree(const IGraph& g) {
        int n = g.verticesCount();
        if (n == 0) return {};
        std::vector<bool> visited(n, false);
        std::vector<std::pair<int, int>> treeEdges;
        std::vector<int> stack;
        
        stack.push_back(0);
        visited[0] = true;
        
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            
            for (int to : g.neighbors(v)) {
                if (!visited[to]) {
                    visited[to] = true;
                    treeEdges.push_back({v, to});
                    stack.push_back(to);
                }
            }
        }
        
        return treeEdges;
    }

    static std::vector<int> findCycle(const IGraph& g) {
        int n = g.verticesCount();
        if (n == 0) return {};
        std::vector<int> parent(n, -1);
        std::vector<bool> visited(n, false);
        std::vector<int> stack;
        
        for (int start = 0; start < n; start++) {
            if (!visited[start]) {
                stack.push_back(start);
                visited[start] = true;
                parent[start] = -1;
                
                while (!stack.empty()) {
                    int v = stack.back();
                    stack.pop_back();
                    
                    for (int to : g.neighbors(v)) {
                        if (!visited[to]) {
                            visited[to] = true;
                            parent[to] = v;
                            stack.push_back(to);
                        }
                        else if (to != parent[v]) {
                            std::vector<int> cycle;
                            cycle.push_back(to);
                            for (int cur = v; cur != to; cur = parent[cur]) {
                                cycle.push_back(cur);
                            }
                            cycle.push_back(to);
                            return cycle;
                        }
                    }
                }
            }
        }
        
        return {};
    }

public:
    static void save(const IGraph& g, const std::string& filename,
                     bool highlightSpanningTree = false,
                     bool highlightCycle = false,
                     const std::vector<std::vector<int>>& clusters = {}) {
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        file << "graph G {\n";
        file << "  rankdir=LR;\n";
        file << "  node [shape=circle];\n";
        
        std::vector<std::pair<int, int>> treeEdges;
        std::vector<int> cycle;
        
        if (highlightSpanningTree) {
            treeEdges = findSpanningTree(g);
        }
        
        if (highlightCycle) {
            cycle = findCycle(g);
        }
        
        for (int i = 0; i < g.verticesCount(); i++) {
            bool inCycle = std::find(cycle.begin(), cycle.end(), i) != cycle.end();
            if (inCycle) {
                file << "  " << i << " [color=red, style=bold];\n";
            }
            else if (!clusters.empty()) {
                int clusterIdx = -1;
                for (size_t c = 0; c < clusters.size(); c++) {
                    if (std::find(clusters[c].begin(), clusters[c].end(), i) != clusters[c].end()) {
                        clusterIdx = c;
                        break;
                    }
                }
                if (clusterIdx != -1) {
                    const char* colors[] = {"blue", "green", "orange", "purple", "cyan", "magenta", "yellow"};
                    file << "  " << i << " [color=" << colors[clusterIdx % 7] << "];\n";
                }
            }
        }
        
        for (int i = 0; i < g.verticesCount(); i++) {
            for (int j : g.neighbors(i)) {
                if (i < j) {
                    bool isTreeEdge = highlightSpanningTree && 
                                     std::find(treeEdges.begin(), treeEdges.end(), 
                                             std::make_pair(i, j)) != treeEdges.end();
                    bool isCycleEdge = highlightCycle && false;
                    
                    for (size_t k = 0; k < cycle.size() - 1; k++) {
                        if ((cycle[k] == i && cycle[k+1] == j) ||
                            (cycle[k] == j && cycle[k+1] == i)) {
                            isCycleEdge = true;
                            break;
                        }
                    }
                    
                    if (isTreeEdge) {
                        file << "  " << i << " -- " << j << " [color=blue, style=bold];\n";
                    }
                    else if (isCycleEdge) {
                        file << "  " << i << " -- " << j << " [color=red, style=bold];\n";
                    }
                    else {
                        file << "  " << i << " -- " << j << ";\n";
                    }
                }
            }
        }
        
        if (!clusters.empty()) {
            for (size_t c = 0; c < clusters.size(); c++) {
                file << "  subgraph cluster_" << c << " {\n";
                file << "    label=\"Cluster " << c << "\";\n";
                file << "    style=dashed;\n";
                file << "    color=" << (c % 2 == 0 ? "gray" : "lightgray") << ";\n";
                for (int v : clusters[c]) {
                    file << "    " << v << ";\n";
                }
                file << "  }\n";
            }
        }
        
        file << "}\n";
    }
};
