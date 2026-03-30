#include "../src/core/AdjListGraph.hpp"
#include "../src/generators/Complete.hpp"
#include "../src/generators/CompleteBipartite.hpp"
#include "../src/generators/Cycle.hpp"
#include "../src/generators/Path.hpp"
#include "../src/generators/Star.hpp"
#include "../src/generators/Tree.hpp"
#include "../src/generators/Wheel.hpp"
#include "../src/generators/Random.hpp"
#include "../src/generators/Cubic.hpp"
#include "../src/generators/Components.hpp"
#include "../src/generators/Bridges.hpp"
#include "../src/generators/Articulation.hpp"
#include "../src/generators/TwoBridges.hpp"
#include "../src/generators/Halin.hpp"
#include "../src/metrics/Density.hpp"
#include "../src/metrics/Diameter.hpp"
#include "../src/metrics/Transitivity.hpp"
#include "../src/metrics/Components.hpp"
#include "../src/metrics/Articulation.hpp"
#include "../src/metrics/Bridges.hpp"
#include "../src/metrics/Bipartite.hpp"
#include "../src/metrics/Chromatic.hpp"

#include <cassert>
#include <iostream>

#define TEST(name) void name()
#define RUN_TEST(name) \
    std::cout << #name << "... "; \
    name(); \
    std::cout << "OK\n";

TEST(test_complete_graph) {
    CompleteGenerator gen(5);
    auto g = gen.generate();
    assert(g->edgesCount() == 10);
}

TEST(test_complete_bipartite_graph) {
    CompleteBipartiteGenerator gen(3, 4);
    auto g = gen.generate();
    assert(g->verticesCount() == 7);
    assert(g->edgesCount() == 12);
}

TEST(test_cycle_graph) {
    CycleGenerator gen(6);
    auto g = gen.generate();
    assert(g->edgesCount() == 6);
    for (int i = 0; i < 6; i++) {
        assert(g->neighbors(i).size() == 2);
    }
}

TEST(test_path_graph) {
    PathGenerator gen(5);
    auto g = gen.generate();
    assert(g->edgesCount() == 4);
    assert(g->neighbors(0).size() == 1);
    assert(g->neighbors(4).size() == 1);
    assert(g->neighbors(2).size() == 2);
}

TEST(test_star_graph) {
    StarGenerator gen(6);
    auto g = gen.generate();
    assert(g->edgesCount() == 5);
    assert(g->neighbors(0).size() == 5);
}

TEST(test_tree_graph) {
    TreeGenerator gen(7);
    auto g = gen.generate();
    assert(g->edgesCount() == 6);
}

TEST(test_wheel_graph) {
    WheelGenerator gen(6);
    auto g = gen.generate();
    assert(g->edgesCount() == 10);
    assert(g->neighbors(0).size() == 5);
}

TEST(test_random_graph) {
    RandomGenerator gen(20, 0.3);
    auto g = gen.generate();
    assert(g->verticesCount() == 20);
}

TEST(test_cubic_graph) {
    CubicGenerator gen(10);
    auto g = gen.generate();
    assert(g->verticesCount() == 10);
    for (int i = 0; i < 10; i++) {
        assert(g->neighbors(i).size() == 3);
    }
}

TEST(test_components_generator) {
    ComponentsGenerator gen(10, 3);
    auto g = gen.generate();
    ComponentsMetric c;
    c.compute(*g);
    assert(c.result() == 3);
}

TEST(test_density_complete) {
    CompleteGenerator gen(5);
    auto g = gen.generate();
    DensityMetric d;
    d.compute(*g);
    assert(d.result() > 0.9);
}

TEST(test_density_sparse) {
    AdjListGraph g(5);
    g.addEdge(0,1);
    g.addEdge(1,2);
    DensityMetric d;
    d.compute(*g);
    assert(d.result() < 0.5);
}

TEST(test_diameter_path) {
    PathGenerator gen(5);
    auto g = gen.generate();
    DiameterMetric d;
    d.compute(*g);
    assert(d.result() == 4);
}

TEST(test_diameter_complete) {
    CompleteGenerator gen(6);
    auto g = gen.generate();
    DiameterMetric d;
    d.compute(*g);
    assert(d.result() == 1);
}

TEST(test_transitivity_complete) {
    CompleteGenerator gen(5);
    auto g = gen.generate();
    TransitivityMetric t;
    t.compute(*g);
    assert(t.result() > 0.9);
}

TEST(test_components_metric) {
    AdjListGraph g(6);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(3,4);
    ComponentsMetric c;
    c.compute(*g);
    assert(c.result() == 3);
}

TEST(test_bipartite_even_cycle) {
    CycleGenerator gen(4);
    auto g = gen.generate();
    BipartiteMetric b;
    b.compute(*g);
    assert(b.result() == true);
}

TEST(test_bipartite_odd_cycle) {
    CycleGenerator gen(5);
    auto g = gen.generate();
    BipartiteMetric b;
    b.compute(*g);
    assert(b.result() == false);
}

TEST(test_bipartite_complete) {
    CompleteGenerator gen(3);
    auto g = gen.generate();
    BipartiteMetric b;
    b.compute(*g);
    assert(b.result() == false);
}

TEST(test_chromatic_complete) {
    CompleteGenerator gen(4);
    auto g = gen.generate();
    ChromaticMetric c;
    c.compute(*g);
    assert(c.result() == 4);
}

TEST(test_bridges_path) {
    PathGenerator gen(5);
    auto g = gen.generate();
    BridgesMetric b;
    b.compute(*g);
    assert(b.result().size() == 4);
}

TEST(test_bridges_cycle) {
    CycleGenerator gen(5);
    auto g = gen.generate();
    BridgesMetric b;
    b.compute(*g);
    assert(b.result().size() == 0);
}

TEST(test_articulation_star) {
    StarGenerator gen(6);
    auto g = gen.generate();
    ArticulationMetric a;
    a.compute(*g);
    assert(a.result().size() == 1);
    assert(a.result()[0] == 0);
}

TEST(test_articulation_path) {
    PathGenerator gen(4);
    auto g = gen.generate();
    ArticulationMetric a;
    a.compute(*g);
    assert(a.result().size() == 2);
}

int main() {
    RUN_TEST(test_complete_graph);
    RUN_TEST(test_complete_bipartite_graph);
    RUN_TEST(test_cycle_graph);
    RUN_TEST(test_path_graph);
    RUN_TEST(test_star_graph);
    RUN_TEST(test_tree_graph);
    RUN_TEST(test_wheel_graph);
    RUN_TEST(test_random_graph);
    RUN_TEST(test_cubic_graph);
    RUN_TEST(test_components_generator);
    RUN_TEST(test_density_complete);
    RUN_TEST(test_density_sparse);
    RUN_TEST(test_diameter_path);
    RUN_TEST(test_diameter_complete);
    RUN_TEST(test_transitivity_complete);
    RUN_TEST(test_components_metric);
    RUN_TEST(test_bipartite_even_cycle);
    RUN_TEST(test_bipartite_odd_cycle);
    RUN_TEST(test_bipartite_complete);
    RUN_TEST(test_chromatic_complete);
    RUN_TEST(test_bridges_path);
    RUN_TEST(test_bridges_cycle);
    RUN_TEST(test_articulation_star);
    RUN_TEST(test_articulation_path);
    
    std::cout << "\nALL METRICS TESTS PASSED\n";
    return 0;
}
