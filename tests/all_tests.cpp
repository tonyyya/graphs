#include <iostream>

int run_graph_tests();
int run_metrics_tests();

int main() {
    std::cout << "=== RUNNING ALL TESTS ===\n\n";
    
    std::cout << ">>> GRAPH TESTS\n";
    run_graph_tests();
    
    std::cout << "\n>>> METRICS TESTS\n";
    run_metrics_tests();
    
    std::cout << "\n=== ALL TESTS COMPLETED ===\n";
    return 0;
}
