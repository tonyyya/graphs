#include "../src/generators/Complete.hpp"
#include "../src/metrics/Density.hpp"
#include <cassert>

int main() {
    CompleteGenerator gen(4);
    auto g = gen.generate();

    DensityMetric d;
    d.compute(*g);

    assert(d.result() > 0.9);

    return 0;
}
