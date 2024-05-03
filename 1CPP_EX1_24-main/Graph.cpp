#include "Graph.hpp"
#include <iostream>
namespace ariel {

void Graph::loadGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int size = adjacencyMatrix.size();
    if (size != 0 && size == adjacencyMatrix[0].size()) {
        matrix = adjacencyMatrix;
        std::cout << "Graph loaded successfully." << std::endl;
    } else {
        throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
}


void Graph::printGraph() const {
    size_t size = matrix.size();
    std::cout << "Graph with " << size << " vertices and ";
    size_t edges = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (matrix[i][j] != 0) {
                ++edges;
            }
        }
    }
    std::cout << edges << " edges." << std::endl;
}}
