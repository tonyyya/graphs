#include "../generators/Complete.hpp"
#include "../generators/Random.hpp"
#include "../metrics/Diameter.hpp"
#include "../metrics/Density.hpp"
#include "../metrics/Components.hpp"
#include "../serialization/GraphViz.hpp"
#include "../parsers/EdgeListParser.hpp"

#include <iostream>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << " generate complete N\n";
        std::cout << " generate random N P\n";
        std::cout << " metric diameter\n";
        std::cout << " parse file.txt\n";
        return 0;
    }

    std::string mode = argv[1];

    std::unique_ptr<IGraph> g;

    if (mode == "generate") {
        std::string type = argv[2];

        if (type == "complete") {
            int n = std::stoi(argv[3]);
            CompleteGenerator gen(n);
            g = gen.generate();
        }

        if (type == "random") {
            int n = std::stoi(argv[3]);
            double p = std::stod(argv[4]);
            RandomGenerator gen(n, p);
            g = gen.generate();
        }
    }

    if (mode == "parse") {
        EdgeListParser parser;
        g = parser.parse(argv[2]);
    }

    if (!g) {
        std::cout << "Graph not created\n";
        return 0;
    }

    // метрики
    if (argc > 2 && std::string(argv[1]) == "metric") {
        std::string m = argv[2];

        if (m == "diameter") {
            DiameterMetric d;
            d.compute(*g);
            std::cout << d.result() << "\n";
        }

        if (m == "density") {
            DensityMetric d;
            d.compute(*g);
            std::cout << d.result() << "\n";
        }

        if (m == "components") {
            ComponentsMetric c;
            c.compute(*g);
            std::cout << c.result() << "\n";
        }
    }

    GraphViz::save(*g, "graph.dot");

    std::cout << "Graph saved to graph.dot\n";
}
