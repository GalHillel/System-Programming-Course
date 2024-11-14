# Graph Algorithms Implementation

## Overview
This project implements a set of graph algorithms using C++. The algorithms include:
- Connectivity checking
- Shortest path finding
- Cycle detection
- Bipartiteness checking
- Negative cycle identification in weighted graphs

## Implementation Method
The implementation consists of two main classes: `Graph` and `Algorithms`, divided into separate header and source files.

### Graph Class
The `Graph` class represents a graph using an adjacency matrix. It provides methods to load a graph from an adjacency matrix, print the graph, and check if the graph is valid.

#### Files:
- `Graph.hpp`: Header file containing the declaration of the `Graph` class.
- `Graph.cpp`: Source file containing the implementation of the `Graph` class methods.

#### Methods:
1. `isValidGraph(const std::vector<std::vector<int>>& graph)`: Checks if the given graph represented by its adjacency matrix is valid.
2. `loadGraph(const std::vector<std::vector<int>>& graph)`: Loads a graph from the given adjacency matrix.

3. `printGraph()`: Prints the adjacency matrix representation of the graph.

4. `getVertices()`: Returns the number of vertices in the graph.

### Algorithms Class
The `Algorithms` class contains static methods to perform various graph algorithms such as connectivity checking, shortest path finding, cycle detection, bipartiteness checking, and negative cycle identification.

#### Files:
- `Algorithms.hpp`: Header file containing the declaration of the `Algorithms` class.
- `Algorithms.cpp`: Source file containing the implementation of the graph algorithms.

#### Methods:
1. `isConnected(const Graph& graph)`: Checks if the given graph is connected using depth-first search (DFS).

2. `shortestPath(const Graph& graph, int source, int destination)`: Finds the shortest path from a source vertex to a destination vertex using Dijkstra's algorithm.

3. `isContainsCycle(const Graph& graph)`: Checks if the given graph contains a cycle using depth-first search (DFS).

4. `isBipartite(const Graph& graph)`: Checks if the given graph is bipartite using depth-first search (DFS).

5. `negativeCycle(const Graph& graph)`: Identifies if the given weighted graph contains a negative cycle using the Bellman-Ford algorithm.

### Test Program
The `Test.cpp` file serves as a demonstration of how to use the implemented classes and algorithms. It contains sample graphs and demonstrates the usage of each algorithm.

### Makefile
The `Makefile` provides targets for building, running, testing, and cleaning the project. It ensures smooth compilation and execution of the program.

## Compilation and Execution
- Use `make` to compile the project.
- Run the `test` executable to see the demonstration of graph algorithms.

## Testing
- Run `make test` to compile and run the test cases.
- Ensure that all tests pass to verify the correctness of the implementations.

