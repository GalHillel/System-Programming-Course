// Id: 211696521 Mail: galh2011@icloud.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

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
        std::string toString() const;
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const { return adjacencyMatrix; }

        Graph &operator+=(const Graph &other);
        Graph &operator-=(const Graph &other);
        Graph operator+(const Graph &other) const;
        Graph operator-(const Graph &other) const;
        Graph operator+() const;
        Graph operator-() const;
        Graph &operator*=(int scalar);
        Graph operator/(int scalar) const;
        Graph &operator/=(int scalar);
        Graph operator*(int scalar) const;
        Graph operator*(const Graph &other) const;

        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        bool operator>(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator>=(const Graph &other) const;
        bool operator<=(const Graph &other) const;

        Graph &operator++();   // Prefix increment
        Graph operator++(int); // Postfix increment
        Graph &operator--();   // Prefix decrement
        Graph operator--(int); // Postfix decrement

        friend std::ostream &operator<<(std::ostream &os, const Graph &g);

    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        int vertices;
    };

}

#endif