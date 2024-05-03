#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>
#include <climits>
#include <algorithm>
#include <iostream>
#include <limits>


namespace ariel {


bool Algorithms::isConnected(const Graph& graph) {
    // Perform DFS from every vertex
    for (size_t i = 0; i < graph.matrix.size(); ++i) {
        std::vector<bool> visited(graph.matrix.size(), false);
        std::stack<size_t> stack;
        stack.push(i);
        visited[i] = true;

        while (!stack.empty()) {
            size_t current = stack.top();
            stack.pop();

            for (size_t j = 0; j < graph.matrix.size(); ++j) {
                if (graph.matrix[current][j] != 0 && !visited[j]) {
                    stack.push(j);
                    visited[j] = true;
                }
            }
        }

        // If any vertex is unreachable, return false
        for (size_t j = 0; j < graph.matrix.size(); ++j) {
            if (!visited[j]) {
                return false;
            }
        }
    }

    return true;
}

bool Algorithms::hasNegativeCycle(const Graph& graph) {
    size_t size = graph.matrix.size();
    std::vector<int> distance(static_cast<size_t>(size), 0);

    // Relax all edges |V| - 1 times
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t u = 0; u < size; ++u) {
            for (size_t v = 0; v < size; ++v) {
                if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph.matrix[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (size_t u = 0; u < size; ++u) {
        for (size_t v = 0; v < size; ++v) {
            if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
                return true; // Negative cycle found
            }
        }
    }

    return false;
}

std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
    std::vector<int> distance(graph.matrix.size(), std::numeric_limits<int>::max());
    std::vector<int> predecessor(graph.matrix.size(), -1);
    std::vector<bool> visited(graph.matrix.size(), false);

    distance[start] = 0;

    for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
        size_t u = minDistance(distance, visited);
        visited[u] = true;

        for (size_t v = 0; v < graph.matrix.size(); ++v) {
            if (!visited[v] && graph.matrix[u][v] != 0 &&
                distance[u] + graph.matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + graph.matrix[u][v];
                predecessor[v] = u;
            }
        }
    }

    if (distance[end] == std::numeric_limits<int>::max())
        return "-1";

    // Construct the path.
    std::stack<size_t> path;
    size_t current = end;
    while (current != start) {
        path.push(current);
        if(predecessor[current] == -1)
        return "-1";
        current = static_cast<size_t>(predecessor[current]);
    }
    path.push(start);

    // Format the path as a string.
    std::string result;
    while (!path.empty()) {
        result += std::to_string(path.top());
        path.pop();
        if (!path.empty()) {
            result += "->";
        }
    }

    return result;
}

size_t Algorithms::minDistance(const std::vector<int>& distance, const std::vector<bool>& visited) {
    size_t minIndex = 0;
    int minDist = std::numeric_limits<int>::max();
    for (size_t i = 0; i < distance.size(); ++i) {
        if (!visited[i] && distance[i] < minDist) {
            minDist = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}


// std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
//        std::vector<int> distance(graph.matrix.size(), std::numeric_limits<int>::max());
//         std::vector<int> predecessor(graph.matrix.size(), -1);

//         distance[start] = 0;

//         //if(start<end){
//         // Relax all edges |V| - 1 times.
//        // for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
//             for (size_t u = start; u < graph.matrix.size(); ++u) {
//                 for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                     if ((graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) ||
//                         (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] == distance[v] && u == start)) {
//                         distance[v] = distance[u] + graph.matrix[u][v];
//                         predecessor[v] = u;
//                     }
//                 }
//             }
//        // }
//         for (size_t u = 0; u < start; ++u) {
//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                     if (graph.matrix[0][v] != 0 && distance[0] + graph.matrix[0][v] < distance[v]) {
//                         distance[v] = distance[0] + graph.matrix[0][v];
//                         predecessor[v] = 0;
//                     }
//                 }
//         }//} else if(start>end){
//         // Relax all edges |V| - 1 times.
//        // for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
//         //    for (size_t u = start; u < graph.matrix.size(); ++u) {
//         //        for (size_t v = 0; v < graph.matrix.size(); ++v) {
//          //           if ((graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) ||
//           //              (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] == distance[v] && u == start)) {
//          //               distance[v] = distance[u] + graph.matrix[u][v];
//           //              predecessor[v] = u;
//          //           }
//          //       }
//          //   }
//        // }
//         // for (size_t u = 0; u < start; ++u) {
//         //     for (size_t v = 0; v < graph.matrix.size(); ++v) {
//         //             if (graph.matrix[0][v] != 0 && distance[0] + graph.matrix[0][v] < distance[v]) {
//         //                 distance[v] = distance[0] + graph.matrix[0][v];
//         //                 predecessor[v] = 0;
//         //             }
//         //         }
//         // }}

//         // Check for negative-weight cycles.
//         for (size_t u = 0; u < graph.matrix.size(); ++u) {
//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                 if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                     return "-1"; // Graph contains negative-weight cycle.
//                 }
//             }
//         }

//         if (distance[end] == std::numeric_limits<int>::max())
//         return "-1";
//         // Construct the path.
//         std::stack<size_t> path;
//         size_t current = end;
//         while (current != start) {
//             path.push(current);
//             current = static_cast<size_t>(predecessor[current]);
//         }
//         path.push(start);

//         // Format the path as a string.
//         std::string result;
//         while (!path.empty()) {
//             result += std::to_string(path.top());
//             path.pop();
//             if (!path.empty()) {
//                 result += "->";
//             }
//         }

//         return result;
//     }



// std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
//     std::string result;

//     if (hasNegativeCycle(graph)) {
//         result = "-1"; // Graph contains negative-weight cycle.
//     } else {
//         std::vector<int> distance(graph.matrix.size(), std::numeric_limits<int>::max());
//         std::vector<int> predecessor(graph.matrix.size(), -1);

//         distance[start] = 0;

//         // Relax all edges |V| - 1 times.
//         for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
//             for (size_t u = 0; u < graph.matrix.size(); ++u) {
//                 for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                     if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                         distance[v] = distance[u] + graph.matrix[u][v];
//                         predecessor[v] = u;
//                     }
//                 }
//             }
//         }

//         // Construct the path.
//         std::stack<size_t> path;
//         size_t current = end;
//         while (current != start) {
//             path.push(current);
//             current = static_cast<size_t>(predecessor[current]);
//         }
//         path.push(start);

//         // Format the path as a string.
//         while (!path.empty()) {
//             result += std::to_string(path.top());
//             path.pop();
//             if (!path.empty()) {
//                 result += "->";
//             }
//         }
//     }

//     return result;
// }



// std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
//     std::vector<int> distance(graph.matrix.size(), std::numeric_limits<int>::max());
//     std::vector<int> predecessor(graph.matrix.size(), -1);

//     distance[start] = 0;
   

//     // Relax all edges |V| - 1 times.
//     for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
//         for (size_t u = 0; u < graph.matrix.size(); ++u) {
//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                 if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                     distance[v] = distance[u] + graph.matrix[u][v];
//                     predecessor[v] = u;
//                 }
//             }
//         }
//     }

//     // Check for negative-weight cycles.
//     for (size_t u = 0; u < graph.matrix.size(); ++u) {
//         for (size_t v = 0; v < graph.matrix.size(); ++v) {
//             if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                 return "-1"; // Graph contains negative-weight cycle.
//             }
//         }
//     }

//     // Construct the path.
//     std::stack<size_t> path;
//     size_t current = end;
//     while (current != start) {
//         path.push(current);
//         current = static_cast<size_t>(predecessor[current]);
//     }
//     path.push(start);

//     // Format the path as a string.
//     std::string result;
//     while (!path.empty()) {
//         result += std::to_string(path.top());
//         path.pop();
//         if (!path.empty()) {
//             result += "->";
//         }
//     }

//     return result;
// }


// std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
//        std::vector<int> distance(graph.matrix.size(), std::numeric_limits<int>::max());
//         std::vector<int> predecessor(graph.matrix.size(), -1);

//         distance[start] = 0;

//         // Relax all edges |V| - 1 times.
//         for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {
//             for (size_t u = 0; u < graph.matrix.size(); ++u) {
//                 for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                     if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                         distance[v] = distance[u] + graph.matrix[u][v];
//                         predecessor[v] = u;
//                     }
//                 }
//             }
//         }

//         // Check for negative-weight cycles.
//         for (size_t u = 0; u < graph.matrix.size(); ++u) {
//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                 if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                     return "-1"; // Graph contains negative-weight cycle.
//                 }
//             }
//         }

//         // Construct the path.
//         std::stack<size_t> path;
//         size_t current = end;
//         while (current != start) {
//             path.push(current);
//             current = static_cast<size_t>(predecessor[current]);
//         }
//         path.push(start);

//         // Format the path as a string.
//         std::string result;
//         while (!path.empty()) {
//             result += std::to_string(path.top());
//             path.pop();
//             if (!path.empty()) {
//                 result += "->";
//             }
//         }

//         return result;
//     }

// std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
//     std::vector<int> distance(graph.matrix.size(), INT_MAX);
//     std::vector<int> predecessor(graph.matrix.size(), -1);

//     distance[start] = 0;

//     // Relax all edges |V| - 1 times.
//     for (size_t i = 0; i < graph.matrix.size() - 1; ++i) {//Main cycles
//         for (size_t u = 0; u < graph.matrix.size(); ++u) {
//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                 if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) { 
//                     distance[v] = distance[u] + graph.matrix[u][v];
//                     predecessor[v] = u;
//                 }
//             }
//         }
//     }

//     // Check for negative-weight cycles.
//     for (size_t u = 0; u < graph.matrix.size(); ++u) {
//         for (size_t v = 0; v < graph.matrix.size(); ++v) {
//             if (graph.matrix[u][v] != 0 && distance[u] + graph.matrix[u][v] < distance[v]) {
//                 return "-1"; // Graph contains negative-weight cycle.
//             }
//         }
//     }

//     // Construct the path.
//     std::stack<size_t> path;
//     size_t current = end;
//     while (current != start) {
//         path.push(current);
//         current = static_cast<size_t>(predecessor[current]);
//     }
//     path.push(start);

//     // Format the path as a string.
//     std::string result;
//     while (!path.empty()) {
//         result += std::to_string(path.top());
//         path.pop();
//         if (!path.empty()) {
//             result += "->";
//         }
//     }

//     return result;
// }

// std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
//     if (start < 0 || start >= static_cast<int>(graph.matrix.size()) ||
//             end < 0 || end >= static_cast<int>(graph.matrix.size())) {
//             return "-1"; // Invalid vertices
//         }

//         const int INF = std::numeric_limits<int>::max();
//         std::vector<int> dist(graph.matrix.size(), INF);
//         std::vector<int> parent(graph.matrix.size(), -1);
//         std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

//         dist[static_cast<size_t>(start)] = 0;
//         pq.push({0, start});

//         while (!pq.empty()) {
//             int u = pq.top().second;
//             int d = pq.top().first;
//             pq.pop();

//             // Skip if already processed
//             if (d > dist[static_cast<size_t>(u)]) continue;

//             for (size_t v = 0; v < graph.matrix.size(); ++v) {
//                 if (graph.matrix[static_cast<size_t>(u)][v] != 0) {
//                     int new_dist = dist[static_cast<size_t>(u)] + graph.matrix[static_cast<size_t>(u)][v];
//                     if (new_dist < dist[v]) {
//                         dist[v] = new_dist;
//                         parent[v] = u;
//                         pq.push({new_dist, v});
//                     }
//                 }
//             }
//         }

//         if (dist[static_cast<size_t>(end)] == INF) {
//             return "-1"; // Path not found
//         }

//         // Reconstruct path
//         std::vector<int> path;
//         int current = end;
//         while (current != -1) {
//             path.push_back(current);
//             current = parent[static_cast<size_t>(current)];
//         }
//         std::reverse(path.begin(), path.end());

//         // Convert path to string
//         std::string pathStr;
//         for (size_t i = 0; i < path.size(); ++i) {
//             pathStr += std::to_string(path[i]);
//             if (i < path.size() - 1) {
//                 pathStr += "->";
//             }
//         }

//         return pathStr;
//     }







//static_cast<size_t>(

// std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
//     // Dijkstra's algorithm to find the shortest path
//     size_t size = graph.matrix.size();
//     std::vector<int> dist(size, INT_MAX);
//     std::vector<int> prev(size, -1);
//     dist[(size_t)start] = 0;
//     //dist[start] = 0;

//     std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
//     pq.push(std::make_pair(0, start));

//     while (!pq.empty()) {
//         size_t u = (size_t)pq.top().second;
//         pq.pop();

//         for (size_t v = 0; v < size; ++v) {
//             if (graph.matrix[u][v] != 0) {
//                 int alt = dist[u] + graph.matrix[u][v];
//                 if (alt < dist[v]) {
//                     dist[v] = alt;
//                     prev[v] = u;
//                     pq.push(std::make_pair(dist[v], v));
//                 }
//             }
//         }
//     }

//     // Construct the path as a string
//     std::string path;
//      if (prev[(size_t)end] != -1) {
//         for (size_t at = (size_t)end; at != -1; at = static_cast<size_t>(prev[at])) {
//             if (!path.empty()) {
//                 path = std::to_string(at) + "->" + path;
//             } else {
//                 path = std::to_string(at);
//             }
//         }

//      } else {
//         path = "-1"; // No path exists
//      }
//     return path;
// }

bool Algorithms::isContainsCycle(const Graph& graph) {
    int size = static_cast<int>(graph.matrix.size());
    std::vector<bool> visited(static_cast<size_t>(size), false);
    std::vector<int> parent(static_cast<size_t>(size), -1); // To store parent of each vertex in DFS tree

    for (int i = 0; i < size; ++i) {
        if (!visited[static_cast<size_t>(i)]) {
            std::stack<int> stack;
            stack.push(i);
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();

                if (visited[static_cast<size_t>(current)]) {
                    // Cycle detected, reconstruct and print the cycle
                    std::vector<int> cycle;
                    cycle.push_back(current);
                    for (int v = parent[static_cast<size_t>(current)]; v != -1 && v != current; v = parent[static_cast<size_t>(v)]) {
                        cycle.push_back(v);
                    }
                    cycle.push_back(current);

                    if (cycle.size() > 2) {
                        // Print the cycle in the correct order
                        std::cout << "The cycle is: ";
                        for (int j = static_cast<int>(cycle.size()) - 1; j > 0; --j) {
                            std::cout << cycle[static_cast<size_t>(j)] << "->";
                        }
                        std::cout << cycle[0] << std::endl;

                        return true;
                    }
                }

                visited[static_cast<size_t>(current)] = true;
                for (int j = 0; j < size; ++j) {
                    if (graph.matrix[static_cast<size_t>(current)][static_cast<size_t>(j)] != 0 && !visited[static_cast<size_t>(j)]) {
                        stack.push(j);
                        parent[static_cast<size_t>(j)] = current;
                    }
                }
            }
        }
    }

    return false;
}





// bool Algorithms::isContainsCycle(const Graph& graph) {
//     size_t size = graph.matrix.size();
//     std::vector<bool> visited(size, false);
//     std::vector<int> parent(size, -1); // To store parent of each vertex in DFS tree

//     for (size_t i = 0; i < size; ++i) {
//         if (!visited[i]) {
//             std::stack<size_t> stack;
//             stack.push(i);
//             while (!stack.empty()) {
//                 size_t current = stack.top();
//                 stack.pop();

//                 if (visited[current]) {
//                     // Cycle detected, reconstruct and print the cycle
//                     std::vector<int> cycle;
//                     cycle.push_back(current);
//                     for (int v = parent[current]; v != -1; v = parent[static_cast<size_t>(v)]) { // Cast to size_t
//                         cycle.push_back(v);
//                     }
//                     cycle.push_back(current);

//                     // Print the cycle
//                     std::cout << "The cycle is:";
//                     for (size_t j = cycle.size() - 2; j < cycle.size(); --j) { // Use size_t for j
//                         std::cout << "->" << cycle[j];
//                     }
//                     std::cout << std::endl;

//                     return true;
//                 }

//                 visited[current] = true;
//                 for (size_t j = 0; j < size; ++j) {
//                     if (graph.matrix[current][j] != 0 && !visited[j]) {
//                         stack.push(j);
//                         parent[j] = static_cast<int>(current); // Cast to int
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }




// bool Algorithms::isContainsCycle(const Graph& graph) {
//     // DFS traversal to check for cycles
//     size_t size = graph.matrix.size();
//     std::vector<bool> visited(size, false);
//     std::stack<int> stack;

//     for (size_t i = 0; i < size; ++i) {
//         if (!visited[i]) {
//             stack.push(i);
//             while (!stack.empty()) {
//                 size_t current = (size_t)stack.top();
//                 stack.pop();
//                 if (visited[current])
//                     return true;
//                 visited[current] = true;
//                 for (size_t j = 0; j < size; ++j) {
//                     if (graph.matrix[current][j] != 0 && !visited[j]) {
//                         stack.push(j);
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }

std::string Algorithms::isBipartite(const Graph& graph) {
    size_t size = graph.matrix.size();
    std::vector<int> color(size, -1);
    std::queue<int> q;

    for (size_t i = 0; i < size; ++i) {
        if (color[i] == -1) {
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (size_t v = 0; v < size; ++v) {
                    if (graph.matrix[(size_t)u][v] != 0) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[(size_t)u];
                            q.push(v);
                        } else if (color[v] == color[(size_t)u]) {
                            return "0"; // Not bipartite
                        }
                    }
                }
            }
        }
    }

    // Construct the bipartition sets
    std::vector<int> setA, setB;
    for (size_t i = 0; i < size; ++i) {
        if (color[i] == 0) {
            setA.push_back(i);
        } else {
            setB.push_back(i);
        }
    }

    // Sort the sets
    std::sort(setA.begin(), setA.end());
    std::sort(setB.begin(), setB.end());

    // Construct the result string
    if (setA.empty() || setB.empty()) {
        return "0"; // Not bipartite
    }

    std::string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        result += std::to_string(setA[i]);
        if (i != setA.size() - 1) {
            result += ", ";
        }
    }
    result += "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        result += std::to_string(setB[i]);
        if (i != setB.size() - 1) {
            result += ", ";
        }
    }
    result += "}";

    return result;
}
} // namespace ariel
