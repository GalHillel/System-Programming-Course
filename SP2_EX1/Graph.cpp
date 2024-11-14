// Id: 211696521 Mail: galh2011@icloud.com
#include "Graph.hpp"
#include <stdexcept>

namespace ariel
{

    Graph::Graph() : vertices(0) {}

    void Graph::loadGraph(const std::vector<std::vector<int>> &graph)
    {
        if (!isValidGraph(graph))
        {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        adjacencyMatrix = graph;
        vertices = static_cast<int>(graph.size());
    }

    void Graph::printGraph() const
    {
        std::cout << "Graph with " << vertices << " vertices and ";
        int edges = 0;
        for (const auto &row : adjacencyMatrix)
        {
            for (int weight : row)
            {
                if (weight > 0)
                    edges++;
            }
        }
        std::cout << edges << " edges." << std::endl;
    }

    bool Graph::isValidGraph(const std::vector<std::vector<int>> &graph) const
    {
        std::vector<std::vector<int>>::size_type rows = graph.size();
        if (rows == 0)
            return false;

        for (const auto &row : graph)
        {
            if (row.size() != rows)
                return false;
        }

        return true;
    }
}
