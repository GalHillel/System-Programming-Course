// Id: 211696521 Mail: galh2011@icloud.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

namespace ariel
{

    class Graph
    {
    public:
        Graph();
        void loadGraph(const std::vector<std::vector<int>> &graph);
        void printGraph() const;
        bool isValidGraph(const std::vector<std::vector<int>> &graph) const;
        int getVertices() const { return vertices; }
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const { return adjacencyMatrix; }

    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        int vertices;
    };

}

#endif
