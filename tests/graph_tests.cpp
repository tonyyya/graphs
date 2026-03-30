#include "../src/core/AdjListGraph.hpp"
#include "../src/parsers/EdgeListParser.hpp"
#include "../src/parsers/MatrixParser.hpp"
#include "../src/parsers/DimacsParser.hpp"
#include "../src/parsers/SnapParser.hpp"
#include "../src/serialization/GraphViz.hpp"
#include "../src/serialization/Program4You.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

#define TEST(name) void name()
#define RUN_TEST(name) \
    std::cout << #name << "... "; \
    name(); \
    std::cout << "OK\n";

TEST(test_graph_basic) {
    AdjListGraph g(3);
    g.addEdge(0,1);
    g.addEdge(1,2);
    assert(g.edgesCount() == 2);
    assert(g.hasEdge(0,1));
    assert(g.hasEdge(1,2));
    assert(!g.hasEdge(0,2));
}

TEST(test_graph_add_vertex) {
    AdjListGraph g(2);
    g.addEdge(0,1);
    assert(g.verticesCount() == 2);
    assert(g.edgesCount() == 1);
}

TEST(test_edge_list_parser) {
    std::ofstream file("test_edges.txt");
    file << "3\n";
    file << "0 1\n";
    file << "1 2\n";
    file << "2 0\n";
    file.close();

    EdgeListParser parser;
    auto g = parser.parse("test_edges.txt");
    
    assert(g->verticesCount() == 3);
    assert(g->edgesCount() == 3);
    assert(g->hasEdge(0,1));
    assert(g->hasEdge(1,2));
    assert(g->hasEdge(2,0));
    
    std::remove("test_edges.txt");
}

TEST(test_matrix_parser) {
    std::ofstream file("test_matrix.txt");
    file << "4\n";
    file << "0 1 0 1\n";
    file << "1 0 1 0\n";
    file << "0 1 0 1\n";
    file << "1 0 1 0\n";
    file.close();

    MatrixParser parser;
    auto g = parser.parse("test_matrix.txt");
    
    assert(g->verticesCount() == 4);
    assert(g->edgesCount() == 4);
    assert(g->hasEdge(0,1));
    assert(g->hasEdge(1,2));
    assert(g->hasEdge(2,3));
    assert(g->hasEdge(3,0));
    
    std::remove("test_matrix.txt");
}

TEST(test_dimacs_parser) {
    std::ofstream file("test.dimacs");
    file << "c Test\n";
    file << "p edge 4 4\n";
    file << "e 1 2\n";
    file << "e 2 3\n";
    file << "e 3 4\n";
    file << "e 4 1\n";
    file.close();

    DimacsParser parser;
    auto g = parser.parse("test.dimacs");
    
    assert(g->verticesCount() == 4);
    assert(g->edgesCount() == 4);
    assert(g->hasEdge(0,1));
    assert(g->hasEdge(1,2));
    assert(g->hasEdge(2,3));
    assert(g->hasEdge(3,0));
    
    std::remove("test.dimacs");
}

TEST(test_snap_parser) {
    std::ofstream file("test.snap");
    file << "# Test\n";
    file << "0 1\n";
    file << "0 2\n";
    file << "1 2\n";
    file << "2 3\n";
    file.close();

    SnapParser parser;
    auto g = parser.parse("test.snap");
    
    assert(g->verticesCount() == 4);
    assert(g->edgesCount() == 4);
    assert(g->hasEdge(0,1));
    assert(g->hasEdge(0,2));
    assert(g->hasEdge(1,2));
    assert(g->hasEdge(2,3));
    
    std::remove("test.snap");
}

TEST(test_graphviz_save) {
    AdjListGraph g(4);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    
    GraphViz::save(g, "test_graph.dot");
    
    std::ifstream file("test_graph.dot");
    assert(file.is_open());
    
    std::string line;
    bool foundDigraph = false;
    while (std::getline(file, line)) {
        if (line.find("digraph") != std::string::npos) {
            foundDigraph = true;
            break;
        }
    }
    file.close();
    
    assert(foundDigraph);
    std::remove("test_graph.dot");
}

TEST(test_graphviz_spanning_tree) {
    AdjListGraph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    
    GraphViz::save(g, "test_tree.dot", true, false);
    
    std::ifstream file("test_tree.dot");
    assert(file.is_open());
    file.close();
    std::remove("test_tree.dot");
}

TEST(test_graphviz_cycle) {
    AdjListGraph g(5);
    for (int i = 0; i < 5; i++) {
        g.addEdge(i, (i+1) % 5);
    }
    
    GraphViz::save(g, "test_cycle.dot", false, true);
    
    std::ifstream file("test_cycle.dot");
    assert(file.is_open());
    file.close();
    std::remove("test_cycle.dot");
}

TEST(test_program4you_save) {
    AdjListGraph g(3);
    g.addEdge(0,1);
    g.addEdge(1,2);
    
    Program4You::save(g, "test.edges");
    
    std::ifstream file("test.edges");
    assert(file.is_open());
    
    int n, m;
    file >> n >> m;
    assert(n == 3);
    assert(m == 2);
    
    file.close();
    std::remove("test.edges");
}

int main() {
    RUN_TEST(test_graph_basic);
    RUN_TEST(test_graph_add_vertex);
    RUN_TEST(test_edge_list_parser);
    RUN_TEST(test_matrix_parser);
    RUN_TEST(test_dimacs_parser);
    RUN_TEST(test_snap_parser);
    RUN_TEST(test_graphviz_save);
    RUN_TEST(test_graphviz_spanning_tree);
    RUN_TEST(test_graphviz_cycle);
    RUN_TEST(test_program4you_save);
    
    std::cout << "\nALL GRAPH TESTS PASSED\n";
    return 0;
}
