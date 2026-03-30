#include "../generators/Complete.hpp"
#include "../generators/Random.hpp"
#include "../metrics/Diameter.hpp"
#include "../metrics/Density.hpp"
#include "../metrics/Components.hpp"
#include "../serialization/GraphViz.hpp"
#include "../parsers/EdgeListParser.hpp"

#include <iostream>
#include <string>
#include <memory>

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  generate complete N\n";
    std::cout << "  generate random N P\n";
    std::cout << "  parse file.txt\n";
    std::cout << "  metric diameter\n";
    std::cout << "  metric density\n";
    std::cout << "  metric components\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage();
        return 0;
    }

    std::unique_ptr<IGraph> g;
    bool graphCreated = false;
    bool saveGraph = true;

    for (int i = 1; i < argc; i++) {
        std::string cmd = argv[i];

        if (cmd == "generate" && i + 1 < argc) {
            std::string type = argv[i + 1];
            
            if (type == "complete" && i + 2 < argc) {
                int n = std::stoi(argv[i + 2]);
                CompleteGenerator gen(n);
                g = gen.generate();
                graphCreated = true;
                i += 2;
            }
            else if (type == "random" && i + 3 < argc) {
                int n = std::stoi(argv[i + 2]);
                double p = std::stod(argv[i + 3]);
                RandomGenerator gen(n, p);
                g = gen.generate();
                graphCreated = true;
                i += 3;
            }
        }
        else if (cmd == "parse" && i + 1 < argc) {
            EdgeListParser parser;
            g = parser.parse(argv[i + 1]);
            if (g) {
                graphCreated = true;
            }
            i += 1;
        }
        else if (cmd == "metric" && i + 1 < argc) {
            if (!graphCreated) {
                std::cout << "Error: graph not created\n";
                return 1;
            }

            std::string metricName = argv[i + 1];

            if (metricName == "diameter") {
                DiameterMetric d;
                d.compute(*g);
                std::cout << "Diameter: " << d.result() << "\n";
                saveGraph = false;
            }
            else if (metricName == "density") {
                DensityMetric d;
                d.compute(*g);
                std::cout << "Density: " << d.result() << "\n";
                saveGraph = false;
            }
            else if (metricName == "components") {
                ComponentsMetric c;
                c.compute(*g);
                std::cout << "Components: " << c.result() << "\n";
                saveGraph = false;
            }
            i += 1;
        }
    }

    if (graphCreated && saveGraph) {
        GraphViz::save(*g, "graph.dot");
        std::cout << "Graph saved to graph.dot\n";
    }

    if (!graphCreated) {
        printUsage();
    }

    return 0;
}
