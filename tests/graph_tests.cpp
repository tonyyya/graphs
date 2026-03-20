#include "../src/core/AdjListGraph.hpp"
#include <cassert>

int main() {
    AdjListGraph g(3);

    g.addEdge(0,1);
    g.addEdge(1,2);

    assert(g.hasEdge(0,1));
    assert(g.hasEdge(1,2));
    assert(!g.hasEdge(0,2));

    return 0;
}
