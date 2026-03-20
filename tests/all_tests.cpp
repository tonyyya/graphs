#include "../src/core/AdjListGraph.hpp"

#include "../src/generators/Complete.hpp"
#include "../src/generators/Cycle.hpp"
#include "../src/generators/Path.hpp"
#include "../src/generators/Star.hpp"
#include "../src/generators/Random.hpp"

#include "../src/metrics/Density.hpp"
#include "../src/metrics/Diameter.hpp"
#include "../src/metrics/Components.hpp"
#include "../src/metrics/Bipartite.hpp"
#include "../src/metrics/Chromatic.hpp"
#include "../src/metrics/Bridges.hpp"
#include "../src/metrics/Articulation.hpp"

#include <cassert>
#include <iostream>

#define TEST(name) void name()
#define RUN_TEST(name) \
    std::cout << #name << "... "; \
    name(); \
    std::cout << "OK\n";

// ======================= GRAPH TESTS =======================

TEST(test_graph_basic) {
    AdjListGraph g(3);

    g.addEdge(0,1);
    g.addEdge(1,2);

    assert(g.edgesCount() == 2);
    assert(g.hasEdge(0,1));
    assert(g.hasEdge(1,2));
    assert(!g.hasEdge(0,2));
}

// ======================= GENERATORS =======================

TEST(test_complete_graph) {
    CompleteGenerator gen(5);
    auto g = gen.generate();

    // K5 → 10 рёбер
    assert(g->edgesCount() == 10);
}

TEST(test_cycle_graph) {
    CycleGenerator gen(6);
    auto g = gen.generate();

    for (int i = 0; i < 6; i++) {
        int size;
        g->neighbors(i, size);
        assert(size == 2);
    }
}

TEST(test_path_graph) {
    PathGenerator gen(5);
    auto g = gen.generate();

    int size0, size4, size2;
    g->neighbors(0, size0);
    g->neighbors(4, size4);
    g->neighbors(2, size2);

    assert(size0 == 1);
    assert(size4 == 1);
    assert(size2 == 2);
}

TEST(test_star_graph) {
    StarGenerator gen(6);
    auto g = gen.generate();

    int size;
    g->neighbors(0, size);

    assert(size == 5);
}

TEST(test_random_graph_variation) {
    RandomGenerator gen(20, 0.5);

    auto g1 = gen.generate();
    auto g2 = gen.generate();

    // вероятность совпадения мала
    assert(g1->edgesCount() != g2->edgesCount());
}

// ======================= METRICS =======================

TEST(test_density_complete) {
    CompleteGenerator gen(5);
    auto g = gen.generate();

    DensityMetric d;
    d.compute(*g);

    assert(d.result() > 0.9);
}

TEST(test_diameter_path) {
    PathGenerator gen(5);
    auto g = gen.generate();

    DiameterMetric d;
    d.compute(*g);

    assert(d.result() == 4);
}

TEST(test_components) {
    AdjListGraph g(4);

    g.addEdge(0,1);
    g.addEdge(2,3);

    ComponentsMetric c;
    c.compute(g);

    assert(c.result() == 2);
}

TEST(test_bipartite) {
    CycleGenerator gen(4); // чётный цикл
    auto g = gen.generate();

    BipartiteMetric b;
    b.compute(*g);

    assert(b.result() == true);
}

TEST(test_not_bipartite) {
    CompleteGenerator gen(3); // треугольник
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

// ======================= BRIDGES / ARTICULATION =======================

TEST(test_bridges_path) {
    PathGenerator gen(5);
    auto g = gen.generate();

    BridgesMetric b;
    b.compute(*g);

    // в пути n-1 мостов
    assert(b.result().size() == 4);
}

TEST(test_articulation_star) {
    StarGenerator gen(6);
    auto g = gen.generate();

    ArticulationMetric a;
    a.compute(*g);

    auto res = a.result();

    // центр должен быть точкой сочленения
    assert(res.size() == 1);
    assert(res[0] == 0);
}

// ======================= MAIN =======================

int main() {
    RUN_TEST(test_graph_basic);

    RUN_TEST(test_complete_graph);
    RUN_TEST(test_cycle_graph);
    RUN_TEST(test_path_graph);
    RUN_TEST(test_star_graph);
    RUN_TEST(test_random_graph_variation);

    RUN_TEST(test_density_complete);
    RUN_TEST(test_diameter_path);
    RUN_TEST(test_components);
    RUN_TEST(test_bipartite);
    RUN_TEST(test_not_bipartite);
    RUN_TEST(test_chromatic_complete);

    RUN_TEST(test_bridges_path);
    RUN_TEST(test_articulation_star);

    std::cout << "\nALL TESTS PASSED\n";
}
