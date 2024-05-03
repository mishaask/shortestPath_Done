#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel {

    class Algorithms {
    public:
        static bool isConnected(const Graph& graph);
        static std::string shortestPath(const Graph& graph, size_t start, size_t end);
        static bool hasNegativeCycle(const Graph& graph); 
        static bool isContainsCycle(const Graph& graph);
        static std::string isBipartite(const Graph& graph);
        static size_t minDistance(const std::vector<int>& distance, const std::vector<bool>& visited);
    };

}

#endif /* ALGORITHMS_HPP */
