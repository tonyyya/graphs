#include "../generators/Complete.hpp"
#include "../generators/CompleteBipartite.hpp"
#include "../generators/Tree.hpp"
#include "../generators/Star.hpp"
#include "../generators/Cycle.hpp"
#include "../generators/Path.hpp"
#include "../generators/Wheel.hpp"
#include "../generators/Random.hpp"
#include "../generators/Cubic.hpp"
#include "../generators/Components.hpp"
#include "../generators/Bridges.hpp"
#include "../generators/Articulation.hpp"
#include "../generators/TwoBridges.hpp"
#include "../generators/Halin.hpp"

#include "../parsers/EdgeListParser.hpp"
#include "../parsers/MatrixParser.hpp"
#include "../parsers/DimacsParser.hpp"
#include "../parsers/SnapParser.hpp"

#include "../metrics/Density.hpp"
#include "../metrics/Diameter.hpp"
#include "../metrics/Transitivity.hpp"
#include "../metrics/Components.hpp"
#include "../metrics/Articulation.hpp"
#include "../metrics/Bridges.hpp"
#include "../metrics/Bipartite.hpp"
#include "../metrics/Chromatic.hpp"

#include "../serialization/GraphViz.hpp"
#include "../serialization/Program4You.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

void printHelp() {
    std::cout << "Usage: graph.exe [command] [args...] [options]\n\n";
    std::cout << "Generation commands:\n";
    std::cout << "  gen complete <n>\n";
    std::cout << "  gen bipartite <n> <m>\n";
    std::cout << "  gen tree <n>\n";
    std::cout << "  gen star <n>\n";
    std::cout << "  gen cycle <n>\n";
    std::cout << "  gen path <n>\n";
    std::cout << "  gen wheel <n>\n";
    std::cout << "  gen random <n> <p>\n";
    std::cout << "  gen cubic <n>\n";
    std::cout << "  gen components <n> <k>\n";
    std::cout << "  gen bridges <n> <k>\n";
    std::cout << "  gen articulation <n> <k>\n";
    std::cout << "  gen twobridges <n> <k>\n";
    std::cout << "  gen halin <n>\n\n";
    
    std::cout << "Parse commands:\n";
    std::cout << "  parse-edge <file>\n";
    std::cout << "  parse-matrix <file>\n";
    std::cout << "  parse-dimacs <file>\n";
    std::cout << "  parse-snap <file>\n\n";
    
    std::cout << "Metrics:\n";
    std::cout << "  metric density\n";
    std::cout << "  metric diameter\n";
    std::cout << "  metric transitivity\n";
    std::cout << "  metric components\n";
    std::cout << "  metric articulation\n";
    std::cout << "  metric bridges\n";
    std::cout << "  metric bipartite\n";
    std::cout << "  metric chromatic\n\n";
    
    std::cout << "Serialization:\n";
    std::cout << "  save-dot <file>\n";
    std::cout << "  save-dot-tree <file>\n";
    std::cout << "  save-dot-cycle <file>\n";
    std::cout << "  save-p4y <file>\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    std::unique_ptr<IGraph> graph;
    bool graphLoaded = false;

    for (int i = 1; i < argc; ++i) {
        std::string cmd = argv[i];

        if (cmd == "gen" && i + 1 < argc) {
            std::string type = argv[++i];
            try {
                if (type == "complete" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    CompleteGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                } 
                else if (type == "bipartite" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    int m = std::stoi(argv[++i]);
                    CompleteBipartiteGenerator gen(n, m);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "tree" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    TreeGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "star" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    StarGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "cycle" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    CycleGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "path" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    PathGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "wheel" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    WheelGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "random" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    double p = std::stod(argv[++i]);
                    RandomGenerator gen(n, p);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "cubic" && i + 1 < argc) {
                    int n = std::stoi(argv[++i]);
                    CubicGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "components" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    int k = std::stoi(argv[++i]);
                    ComponentsGenerator gen(n, k);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "bridges" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    BridgesGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "articulation" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    ArticulationGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "twobridges" && i + 2 < argc) {
                    int n = std::stoi(argv[++i]);
                    TwoBridgesGenerator gen(n);
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else if (type == "halin" && i + 1 < argc) {
                    HalinGenerator gen;
                    graph = gen.generate();
                    graphLoaded = true;
                }
                else {
                    std::cout << "Unknown generator or missing arguments: " << type << "\n";
                }
            } catch (...) {
                std::cout << "Error generating graph. Check arguments.\n";
            }
        }
        else if (cmd == "parse-edge" && i + 1 < argc) {
            EdgeListParser p;
            graph = p.parse(argv[++i]);
            if (graph) graphLoaded = true;
        }
        else if (cmd == "parse-matrix" && i + 1 < argc) {
            MatrixParser p;
            graph = p.parse(argv[++i]);
            if (graph) graphLoaded = true;
        }
        else if (cmd == "parse-dimacs" && i + 1 < argc) {
            DimacsParser p;
            graph = p.parse(argv[++i]);
            if (graph) graphLoaded = true;
        }
        else if (cmd == "parse-snap" && i + 1 < argc) {
            SnapParser p;
            graph = p.parse(argv[++i]);
            if (graph) graphLoaded = true;
        }
        else if (cmd == "metric" && i + 1 < argc) {
            if (!graphLoaded) {
                std::cout << "Error: No graph loaded.\n";
                return 1;
            }
            std::string mType = argv[++i];
            try {
                if (mType == "density") {
                    DensityMetric m; m.compute(*graph);
                    std::cout << "Density: " << m.result() << "\n";
                }
                else if (mType == "diameter") {
                    DiameterMetric m; m.compute(*graph);
                    std::cout << "Diameter: " << m.result() << "\n";
                }
                else if (mType == "transitivity") {
                    TransitivityMetric m; m.compute(*graph);
                    std::cout << "Transitivity: " << m.result() << "\n";
                }
                else if (mType == "components") {
                    ComponentsMetric m; m.compute(*graph);
                    std::cout << "Components: " << m.result() << "\n";
                }
                else if (mType == "articulation") {
                    ArticulationMetric m; m.compute(*graph);
                    std::cout << "Articulation points: " << m.result().size() << "\n";
                }
                else if (mType == "bridges") {
                    BridgesMetric m; m.compute(*graph);
                    std::cout << "Bridges: " << m.result().size() << "\n";
                }
                else if (mType == "bipartite") {
                    BipartiteMetric m; m.compute(*graph);
                    std::cout << "Bipartite: " << (m.result() ? "Yes" : "No") << "\n";
                }
                else if (mType == "chromatic") {
                    ChromaticMetric m; m.compute(*graph);
                    std::cout << "Chromatic number: " << m.result() << "\n";
                }
                else {
                    std::cout << "Unknown metric: " << mType << "\n";
                }
            } catch (...) {
                std::cout << "Error computing metric.\n";
            }
        }
        else if (cmd == "save-dot" && graphLoaded) {
            std::string fname = (i + 1 < argc && argv[i+1][0] != '-') ? argv[++i] : "graph.dot";
            GraphViz::save(*graph, fname);
            std::cout << "Saved to " << fname << "\n";
        }
        else if (cmd == "save-dot-tree" && graphLoaded) {
            std::string fname = (i + 1 < argc && argv[i+1][0] != '-') ? argv[++i] : "graph_tree.dot";
            GraphViz::save(*graph, fname, true, false);
            std::cout << "Saved spanning tree to " << fname << "\n";
        }
        else if (cmd == "save-dot-cycle" && graphLoaded) {
            std::string fname = (i + 1 < argc && argv[i+1][0] != '-') ? argv[++i] : "graph_cycle.dot";
            GraphViz::save(*graph, fname, false, true);
            std::cout << "Saved cycle to " << fname << "\n";
        }
        else if (cmd == "save-p4y" && graphLoaded) {
            std::string fname = (i + 1 < argc && argv[i+1][0] != '-') ? argv[++i] : "graph.edges";
            Program4You::save(*graph, fname);
            std::cout << "Saved to " << fname << "\n";
        }
    }

    if (!graphLoaded) {
        std::cout << "No graph was created or loaded.\n";
        printHelp();
    }

    return 0;
}
