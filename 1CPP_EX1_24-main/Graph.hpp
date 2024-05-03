#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>
namespace ariel{ 

class Graph {
public:
    void loadGraph(const std::vector<std::vector<int>>& adjacencyMatrix);
    void printGraph() const;
    std::vector<std::vector<int>> matrix;
//private:
    //std::vector<std::vector<int>> matrix;
};

}

#endif /* GRAPH_HPP */
