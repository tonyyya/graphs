#pragma once
#include "../core/IGraph.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

class GraphViz {
public:
    static void save(const IGraph& g, const std::string& filename,
                     bool highlightSpanningTree = false,
                     bool highlightCycle = false) {
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        int n = g.verticesCount();
        if (n == 0) {
            file << "graph G {\n}\n";
            return;
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
        
        for (int i = 0; i < n; i++) {
            bool inCycle = std::find(cycle.begin(), cycle.end(), i) != cycle.end();
            if (inCycle) {
                file << "  " << i << " [color=red, style=bold];\n";
            }
        }
        
        std::vector<std::pair<int, int>> addedEdges;
        for (int i = 0; i < n; i++) {
            const auto& neighbors = g.neighbors(i);
            for (int j : neighbors) {
                if (i < j) {
                    bool alreadyAdded = false;
                    for (const auto& edge : addedEdges) {
                        if ((edge.first == i && edge.second == j) ||
                            (edge.first == j && edge.second == i)) {
                            alreadyAdded = true;
                            break;
                        }
                    }
                    
                    if (!alreadyAdded) {
                        addedEdges.push_back({i, j});
                        
                        bool isTreeEdge = highlightSpanningTree && 
                                         std::find(treeEdges.begin(), treeEdges.end(), 
                                                 std::make_pair(i, j)) != treeEdges.end();
                        bool isCycleEdge = false;
                        
                        if (highlightCycle) {
                            for (size_t k = 0; k + 1 < cycle.size(); k++) {
                                if ((cycle[k] == i && cycle[k+1] == j) ||
                                    (cycle[k] == j && cycle[k+1] == i)) {
                                    isCycleEdge = true;
                                    break;
                                }
                            }
                        }
                        
                        if (isTreeEdge) {
                            file << "  " << i << " -- " << j << " [color=blue, style=bold];\n";
                        } else if (isCycleEdge) {
                            file << "  " << i << " -- " << j << " [color=red, style=bold];\n";
                        } else {
                            file << "  " << i << " -- " << j << ";\n";
                        }
                    }
                }
            }
        }
        
        file << "}\n";
    }

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
            
            const auto& neighbors = g.neighbors(v);
            for (int to : neighbors) {
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
                    
                    const auto& neighbors = g.neighbors(v);
                    for (int to : neighbors) {
                        if (!visited[to]) {
                            visited[to] = true;
                            parent[to] = v;
                            stack.push_back(to);
                        }
                        else if (to != parent[v] && parent[v] != -1) {
                            std::vector<int> cycle;
                            cycle.push_back(to);
                            for (int cur = v; cur != to && cur != -1; cur = parent[cur]) {
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
};
