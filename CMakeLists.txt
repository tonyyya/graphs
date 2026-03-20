cmake_minimum_required(VERSION 3.10)
project(GraphLab)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(graph src/cli/main.cpp)

add_executable(test_graph tests/graph_tests.cpp)
add_executable(test_metrics tests/metrics_tests.cpp)
