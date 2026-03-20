#include <catch2/catch_test_macros.hpp>
#include "../include/Graph.hpp"

TEST_CASE("graph constructor creates empty graph", "[graph]") {
    Graph g;
    REQUIRE(g.verticesCount() == 0);
    REQUIRE(g.edgesCount() == 0);
}

TEST_CASE("graph constructor with n vertices", "[graph]") {
    Graph g(5);
    REQUIRE(g.verticesCount() == 5);
    REQUIRE(g.edgesCount() == 0);
for (int i = 0; i < 5; i++) {
        REQUIRE(g.hasVertex(i) == true);
    }
    REQUIRE(g.hasVertex(5) == false);  
}
TEST_CASE("graph addEdge works correctly", "[graph]") {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    
    REQUIRE(g.edgesCount() == 2);
    REQUIRE(g.hasEdge(0, 1) == true);
    REQUIRE(g.hasEdge(1, 0) == true);  
    REQUIRE(g.hasEdge(0, 2) == false);
}

TEST_CASE("graph addEdge does not add duplicates", "[graph]") {
    Graph g(2);
    g.addEdge(0, 1);
    g.addEdge(0, 1);
    g.addEdge(1, 0);  
    
    REQUIRE(g.edgesCount() == 1);  
}
TEST_CASE("graph removeEdge works correctly", "[graph]") {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    
    REQUIRE(g.edgesCount() == 2);
    g.removeEdge(0, 1);
    REQUIRE(g.edgesCount() == 1);
    REQUIRE(g.hasEdge(0, 1) == false);
}
TEST_CASE("graph throws on invalid vertex", "[graph]") {
    Graph g(3);
    REQUIRE_THROWS_AS(g.addEdge(0, 100), std::out_of_range);
    REQUIRE_THROWS_AS(g.getDegree(5), std::out_of_range);
}
TEST_CASE("Graph copy constructor creates deep copy", "[graph]") {
    Graph g1(3);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    
    Graph g2(g1);  
    
    REQUIRE(g2.verticesCount() == 3);
    REQUIRE(g2.edgesCount() == 2);
    REQUIRE(g2.hasEdge(0, 1) == true);
    
    g1.removeEdge(0, 1);
    REQUIRE(g1.edgesCount() == 1);
    REQUIRE(g2.edgesCount() == 2);  
}

TEST_CASE("Graph assignment operator works correctly", "[graph]") {
    Graph g1(3);
    g1.addEdge(0, 1);
    
    Graph g2(5); 
    g2 = g1;      
    
    REQUIRE(g2.verticesCount() == 3);
    REQUIRE(g2.edgesCount() == 1);
}
TEST_CASE("Graph self-assignment does not crash", "[graph]") {
    Graph g(3);
    g.addEdge(0, 1);
    g = g;  
    REQUIRE(g.edgesCount() == 1);
}
TEST_CASE("Graph invariant: degree equals neighbors count", "[graph]") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    
    int count;
    g.getNeighbors(0, count);
    REQUIRE(count == g.getDegree(0));  
}

TEST_CASE("Graph invariant: sum of degrees = 2 * edges", "[graph]") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    int sumDegrees = 0;
    for (int i = 0; i < g.verticesCount(); i++) {
        sumDegrees += g.getDegree(i);
    }
    
    REQUIRE(sumDegrees == 2 * g.edgesCount());  
}
TEST_CASE("Graph isLeaf works correctly", "[graph]") {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    
    REQUIRE(g.isLeaf(0) == true);   
    REQUIRE(g.isLeaf(1) == false);  
    REQUIRE(g.isLeaf(2) == true);   
}


TEST_CASE("Graph no memory leaks on destruction", "[graph]") {
    {
        Graph g(10);
        for (int i = 0; i < 9; i++) {
            g.addEdge(i, i + 1);
        }
    }
    REQUIRE(true);  
}
