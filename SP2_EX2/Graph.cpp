// Id: 211696521 Mail: galh2011@icloud.com
#include "Graph.hpp"
#include <stdexcept>
#include <sstream>

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
        for (const auto &row : adjacencyMatrix)
        {
            for (std::vector<int>::size_type i = 0; i < row.size(); ++i)
            {
                std::cout << row[i];
                if (i < row.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

    std::string Graph::toString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            oss << "[";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                oss << adjacencyMatrix[i][j];
                if (j != adjacencyMatrix[i].size() - 1) {
                    oss << ", ";
                }
            }
            oss << "]";
            if (i != adjacencyMatrix.size() - 1) {
                oss << "\n";
            }
        }
        return oss.str();
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

    Graph Graph::operator+(const Graph &other) const
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }
        Graph result = *this;
        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                result.adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }
        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator-(const Graph &other) const
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract.");
        }
        Graph result = *this;
        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                result.adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract.");
        }
        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator+() const
    {
        return *this;
    }

    Graph Graph::operator-() const
    {
        Graph result = *this;
        for (auto &row : result.adjacencyMatrix)
        {
            for (auto &value : row)
            {
                value = -value;
            }
        }
        return result;
    }

    Graph Graph::operator*(int scalar) const
    {
        Graph result = *this;
        for (auto &row : result.adjacencyMatrix)
        {
            for (auto &value : row)
            {
                value *= scalar;
            }
        }
        return result;
    }

    Graph &Graph::operator*=(int scalar)
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &value : row)
            {
                value *= scalar;
            }
        }
        return *this;
    }

    Graph Graph::operator*(const Graph &other) const
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to multiply.");
        }
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size(), 0));
        result.vertices = vertices;

        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                for (std::vector<int>::size_type k = 0; k < adjacencyMatrix.size(); ++k)
                {
                    result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
            }
        }
        return result;
    }

    Graph Graph::operator/(int scalar) const
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        Graph result = *this;
        for (auto &row : result.adjacencyMatrix)
        {
            for (auto &value : row)
            {
                value /= scalar;
            }
        }
        return result;
    }

    Graph &Graph::operator/=(int scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        for (auto &row : adjacencyMatrix)
        {
            for (auto &value : row)
            {
                value /= scalar;
            }
        }
        return *this;
    }

    bool Graph::operator==(const Graph &other) const
    {
        return adjacencyMatrix == other.adjacencyMatrix;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    bool Graph::operator>(const Graph &other) const
    {
        if (vertices != other.vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size to compare.");
        }

        int thisEdges = 0;
        int otherEdges = 0;

        for (std::vector<std::vector<int>>::size_type i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0 && other.adjacencyMatrix[i][j] == 0)
                {
                    return true;
                }
                else if (adjacencyMatrix[i][j] == 0 && other.adjacencyMatrix[i][j] != 0)
                {
                    return false;
                }
                thisEdges += adjacencyMatrix[i][j];
                otherEdges += other.adjacencyMatrix[i][j];
            }
        }
        return thisEdges > otherEdges;
    }

    bool Graph::operator<(const Graph &other) const
    {
        return other > *this;
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other);
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other);
    }

    Graph &Graph::operator++()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &value : row)
            {
                ++value;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph &Graph::operator--()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &value : row)
            {
                --value;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const Graph &g)
    {
        for (const auto &row : g.adjacencyMatrix)
        {
            os << "[";
            for (std::vector<int>::size_type i = 0; i < row.size(); ++i)
            {
                os << row[i];
                if (i < row.size() - 1)
                {
                    os << ", ";
                }
            }
            os << "]\n";
        }
        return os;
    }

}
