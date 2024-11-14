// Id: 211696521 Mail: galh2011@icloud.com
#include "Algorithms.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

namespace ariel
{
    bool Algorithms::isConnected(const Graph &g)
    {
        const std::vector<std::vector<int>> &adjacencyMatrix = g.getAdjacencyMatrix();
        int numVertices = g.getVertices();

        std::vector<bool> visited(static_cast<std::vector<bool>::size_type>(numVertices), false);

        // Starts DFS from vertex 0
        return dfs(adjacencyMatrix, visited, 0);
    }

    string Algorithms::shortestPath(const Graph &g, int start, int end)
    {
        const auto &adjacencyMatrix = g.getAdjacencyMatrix();
        int numVertices = g.getVertices();

        // Initialize a vector to mark visited vertices
        std::vector<bool> visited(static_cast<std::vector<bool>::size_type>(numVertices), false);

        // Perform DFS from the start vertex
        if (!dfs(adjacencyMatrix, visited, start) || Algorithms::negativeCycle(g) != "No negative cycle found.")
        {
            // If the end vertex is not reachable from the start vertex, return "-1"
            return "-1";
        }

        // Reconstruct the shortest path
        std::string path = std::to_string(end);
        while (end != start)
        {
            // Find the parent vertex of the current vertex on the shortest path
            for (std::vector<int>::size_type i = 0; i < static_cast<std::vector<int>::size_type>(numVertices); ++i)
            {
                if (adjacencyMatrix[i][static_cast<std::vector<int>::size_type>(end)] && visited[i])
                {
                    path = std::to_string(i) + "->" + path;
                    end = static_cast<int>(i);
                    break;
                }
            }
        }

        return path;
    }

    std::string Algorithms::isContainsCycle(const Graph &g)
    {
        const auto &adjacencyMatrix = g.getAdjacencyMatrix();
        int numVertices = g.getVertices();

        // Mark all the vertices as not visited
        std::vector<bool> visited(static_cast<size_t>(numVertices), false);

        // Stores the cycle vertices if found
        std::vector<int> cycle;

        // Call the recursive helper function to detect cycle in different DFS trees
        for (int u = 0; u < numVertices; u++)
        {
            // Don't recur for u if it is already visited
            if (!visited[static_cast<size_t>(u)])
            {
                if (isContainsCycleH(adjacencyMatrix, u, visited, -1, cycle))
                {
                    // Construct the output string for the cycle
                    std::string cycleStr = "The cycle is: ";
                    for (size_t i = 0; i < cycle.size(); ++i)
                    {
                        cycleStr += std::to_string(cycle[i]);
                        if (i != cycle.size() - 1)
                            cycleStr += "->";
                    }
                    return cycleStr;
                }
            }
        }
        return "0";
    }

    bool Algorithms::isContainsCycleH(const std::vector<std::vector<int>> &adjacencyMatrix, int vertex, std::vector<bool> &visited, int parent, std::vector<int> &cycle)
    {
        // Mark the current node as visited
        visited[static_cast<size_t>(vertex)] = true;

        // Recur for all the vertices adjacent to this vertex
        for (size_t i = 0; i < adjacencyMatrix[static_cast<size_t>(vertex)].size(); ++i)
        {
            // If an adjacent vertex is not visited, then recur for that adjacent
            if (adjacencyMatrix[static_cast<size_t>(vertex)][i] && !visited[i])
            {
                if (isContainsCycleH(adjacencyMatrix, static_cast<int>(i), visited, vertex, cycle))
                {
                    // If a cycle is found, add the current vertex to the cycle
                    cycle.push_back(static_cast<int>(vertex));
                    return true;
                }
            }
            // If an adjacent vertex is visited and is not the parent of the current vertex, then there exists a cycle in the graph
            else if (adjacencyMatrix[static_cast<size_t>(vertex)][i] && i != static_cast<size_t>(parent))
            {
                // Construct the cycle
                cycle.push_back(static_cast<int>(vertex));
                //cycle.push_back(static_cast<int>(i));
                return true;
            }
        }
        return false;
    }

    std::string Algorithms::isBipartite(const Graph &g)
    {
        const auto &adjacencyMatrix = g.getAdjacencyMatrix();
        int numVertices = g.getVertices();

        // Create a color array to store colors assigned to all vertices
        // The value '-1' of colorArr[i] is used to indicate that no color is assigned to vertex 'i'.
        // The value 1 is used to indicate the first color is assigned and value 0 indicates the second color is assigned.
        std::vector<int> colorArr(static_cast<size_t>(numVertices), -1);

        // Stores vertices in two different sets based on their color
        std::vector<int> setA, setB;

        // Run BFS for each component if not already colored
        for (int i = 0; i < numVertices; ++i)
        {
            if (colorArr[static_cast<size_t>(i)] == -1)
            {
                // Assign the first color to the current vertex
                colorArr[static_cast<size_t>(i)] = 1;

                // Add the vertex to set A
                setA.push_back(i);

                // Create a queue for BFS
                std::queue<int> q;
                q.push(i);

                // Run BFS
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();

                    // Return false if there is a self-loop
                    if (adjacencyMatrix[static_cast<size_t>(u)][static_cast<size_t>(u)] == 1)
                        return "0";

                    // Check all adjacent vertices
                    for (int v = 0; v < numVertices; ++v)
                    {
                        // If there is an edge from u to v and v is not colored
                        if (adjacencyMatrix[static_cast<size_t>(u)][static_cast<size_t>(v)] && colorArr[static_cast<size_t>(v)] == -1)
                        {
                            // Assign alternate color to the adjacent vertex of u
                            colorArr[static_cast<size_t>(v)] = 1 - colorArr[static_cast<size_t>(u)];
                            q.push(v);

                            // Add the vertex to the respective set
                            if (colorArr[static_cast<size_t>(v)] == 1)
                                setA.push_back(v);
                            else
                                setB.push_back(v);
                        }
                        // If there is an edge from u to v and v is colored with the same color as u
                        else if (adjacencyMatrix[static_cast<size_t>(u)][static_cast<size_t>(v)] && colorArr[static_cast<size_t>(v)] == colorArr[static_cast<size_t>(u)])
                            return "0";
                    }
                }
            }
        }

        // Construct the output string
        std::string output = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i)
        {
            output += std::to_string(setA[i]);
            if (i != setA.size() - 1)
                output += ", ";
        }
        output += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i)
        {
            output += std::to_string(setB[i]);
            if (i != setB.size() - 1)
                output += ", ";
        }
        output += "}";

        return output;
    }
    std::string Algorithms::negativeCycle(const Graph &g)
    {
        // Get the number of vertices in the graph
        std::vector<std::vector<int>>::size_type numVertices = static_cast<std::vector<std::vector<int>>::size_type>(g.getVertices());

        // Get the adjacency matrix of the graph
        const auto &adjacencyMatrix = g.getAdjacencyMatrix();

        // Initialize distance array to store shortest distances from source vertex
        std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
        distance[0] = 0; // Assuming source vertex is 0

        // Initialize parent array to store parent vertices in the shortest path tree
        std::vector<int> parent(numVertices, -1);

        // Relax edges repeatedly
        bool negativeCycleFound = false;
        for (std::vector<std::vector<int>>::size_type i = 0; i < numVertices - 1; ++i)
        {
            for (std::vector<std::vector<int>>::size_type u = 0; u < numVertices; ++u)
            {
                for (std::vector<int>::size_type v = 0; v < numVertices; ++v)
                {
                    if (adjacencyMatrix[u][v] != 0)
                    {
                        if (distance[u] != std::numeric_limits<int>::max() && distance[u] + adjacencyMatrix[u][v] < distance[v])
                        {
                            distance[v] = distance[u] + adjacencyMatrix[u][v];
                            parent[v] = u;
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (std::vector<std::vector<int>>::size_type u = 0; u < numVertices; ++u)
        {
            for (std::vector<int>::size_type v = 0; v < numVertices; ++v)
            {
                if (adjacencyMatrix[u][v] != 0)
                {
                    if (distance[u] != std::numeric_limits<int>::max() && distance[u] + adjacencyMatrix[u][v] < distance[v])
                    {
                        // Found a negative cycle, construct and return the cycle
                        std::vector<int> cycle;
                        int current = v;
                        while (current != u)
                        {
                            if (current == -1)
                            {
                                // Cycle detected, but no cycle formed
                                return "No negative cycle found.";
                            }
                            cycle.push_back(current);
                            current = static_cast<int>(parent[static_cast<std::vector<int>::size_type>(current)]);
                        }
                        cycle.push_back(u);
                        std::reverse(cycle.begin(), cycle.end());

                        std::string cycleStr;
                        for (int vertex : cycle)
                        {
                            cycleStr += std::to_string(vertex) + "->";
                        }
                        // Remove the trailing "->"
                        cycleStr.pop_back();
                        cycleStr.pop_back();
                        return "Negative cycle found: " + cycleStr;
                    }
                }
            }
        }

        return "No negative cycle found.";
    }

    bool Algorithms::dfs(const std::vector<std::vector<int>> &adjacencyMatrix, std::vector<bool> &visited, int start)
    {
        stack<int> s;

        // Push the start vertex to the stack
        s.push(start);

        // Mark the start vertex as visited
        visited[static_cast<std::vector<bool>::size_type>(start)] = true;

        // Run DFS
        while (!s.empty())
        {
            // Pop a vertex from the stack
            int v = s.top();
            s.pop();

            // Check all adjacent vertices of the popped vertex
            for (std::vector<int>::size_type i = 0; i < adjacencyMatrix[static_cast<std::vector<bool>::size_type>(v)].size(); ++i)
            {
                // If an adjacent vertex is not visited, mark it visited and push it to the stack
                if (adjacencyMatrix[static_cast<std::vector<bool>::size_type>(v)][i] && !visited[i])
                {
                    visited[i] = true;
                    s.push(static_cast<int>(i));
                }
            }
        }

        // Check if all vertices were visited
        for (size_t i = 0; i < visited.size(); ++i)
        {
            if (!visited[i])
                return false;
        }

        return true;
    }

}
