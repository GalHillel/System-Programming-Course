// Id: 211696521 Mail: galh2011@icloud.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Algorithms Class Tests")
{
    SUBCASE("Test isConnected")
    {
        ariel::Graph g;
        // Test a connected graphs
        vector<vector<int>> connectedGraph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(connectedGraph);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> connectedGraph1 = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {1, 0, 1, 0},
        };
        g.loadGraph(connectedGraph1);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> connectedGraph2 = {
            {0, 1, 0, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
        };
        g.loadGraph(connectedGraph2);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> connectedGraph3 = {
            {0, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 0},
        };
        g.loadGraph(connectedGraph3);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> connectedGraph4 = {
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 0},
        };
        g.loadGraph(connectedGraph4);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        // Test a disconnected graphs
        vector<vector<int>> disconnectedGraph = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(disconnectedGraph);
        CHECK(ariel::Algorithms::isConnected(g) == false);

        vector<vector<int>> disconnectedGraph1 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(disconnectedGraph1);
        CHECK(ariel::Algorithms::isConnected(g) == false);

        vector<vector<int>> disconnectedGraph2 = {
            {0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0}};
        g.loadGraph(disconnectedGraph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);

        vector<vector<int>> disconnectedGraph3 = {
            {0, 1, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 1, 0}};
        g.loadGraph(disconnectedGraph3);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    SUBCASE("Test shortestPath")
    {
        ariel::Graph g;

        // Test shortest path in a connected graph
        vector<vector<int>> connectedGraph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(connectedGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

        vector<vector<int>> connectedGraph1 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g.loadGraph(connectedGraph1);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->4");

        // Test shortest path in a disconnected graph
        vector<vector<int>> disconnectedGraph = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(disconnectedGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

        // Test shortest path in a weighted graph
        vector<vector<int>> weightedGraph = {
            {0, 2, 0, 3},
            {0, 0, 4, 0},
            {0, 0, 0, 1},
            {0, 0, 0, 0}};
        g.loadGraph(weightedGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->3");

        vector<vector<int>> negativeWeightGraph = {
            {0, 1, -1, 0, 0},
            {1, 0, 1, 0, 0},
            {-1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(negativeWeightGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");

        // Test shortest path with cyclic graph
        vector<vector<int>> cyclicGraph = {
            {0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 0, 0, 0, 0}};
        g.loadGraph(cyclicGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");

        // Test shortest path with self-loop
        vector<vector<int>> selfLoopGraph = {
            {0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0}};
        g.loadGraph(selfLoopGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");

        // Test shortest path in a graph with a negative cycle
        vector<vector<int>> negativeCycleGraph = {
            {0, -1, 0, 0},
            {0, 0, -1, 0},
            {0, 0, 0, -1},
            {-1, 0, 0, 0}};
        g.loadGraph(negativeCycleGraph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");
    }

    SUBCASE("Test isContainsCycle")
    {
        ariel::Graph g;

        // Test a graph without a cycle
        vector<vector<int>> graph1 = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}};
        g.loadGraph(graph1);
        cout << ariel::Algorithms::isContainsCycle(g) << endl;
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

        // Test a graph with a cycle
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g.loadGraph(graph2);
        cout << ariel::Algorithms::isContainsCycle(g) << endl;

        CHECK(ariel::Algorithms::isContainsCycle(g).find("The cycle is:") != string::npos);

        // Test a graph with multiple cycles
        vector<vector<int>> graph3 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0}};
        g.loadGraph(graph3);
        cout << ariel::Algorithms::isContainsCycle(g) << endl;

        CHECK(ariel::Algorithms::isContainsCycle(g).find("The cycle is:") != string::npos);

        // Test a graph without cycles but with a self-loop
        vector<vector<int>> graph4 = {
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}};
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
    }

    SUBCASE("Test isBipartite")
    {
        ariel::Graph g;
        // Test a bipartite graph
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph1);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

        // Test a non-bipartite graph
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");

        // Test another bipartite graph
        vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

        vector<vector<int>> graph4 = {
            {0, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 0, 1, 0}};
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4, 6}, B={1, 3, 5}");

        vector<vector<int>> graph5 = {
            {0, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 0}};
        g.loadGraph(graph5);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");

        vector<vector<int>> graph6 = {
            {0, 0, 0, 1, 1, 1},
            {0, 0, 0, 1, 1, 1},
            {0, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 0},
            {1, 1, 1, 0, 0, 0},
            {1, 1, 1, 0, 0, 0},
        };
        g.loadGraph(graph6);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={3, 4, 5}");
    }

    SUBCASE("Test negativeCycle")
    {
        ariel::Graph g;

        // Test a graph with no negative cycle
        vector<vector<int>> graph1 = {
            {0, 1, 2},
            {2, 0, 3},
            {1, 4, 0}};
        g.loadGraph(graph1);
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found.");

        vector<vector<int>> graph4 = {
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, -10, 0, 0, 0, 0, 0, 0},
            {0, -10, 0, 20, 0, 0, 0, 0, 0},
            {0, 0, 20, 0, -30, 0, 0, 0, 0},
            {0, 0, 0, -30, 0, 40, 0, 0, 0},
            {0, 0, 0, 0, 40, 0, -50, 0, 10},
            {0, 0, 0, 0, 0, -50, 0, 60, 0},
            {0, 0, 0, 0, 0, 0, 60, 0, -70},
            {0, 0, 0, 0, 0, 10, 0, -70, 0}};
        g.loadGraph(graph4);
        cout << ariel::Algorithms::negativeCycle(g) << endl;
        CHECK(ariel::Algorithms::negativeCycle(g).find("Negative cycle found:") != string::npos);

        // Test a graph with a negative cycle containing two vertices
        vector<vector<int>> graph5 = {
            {0, -1, 2},
            {3, 0, 1},
            {-4, 5, 0}};
        g.loadGraph(graph5);
        cout << ariel::Algorithms::negativeCycle(g) << endl;
        CHECK(ariel::Algorithms::negativeCycle(g).find("Negative cycle found:") != string::npos);

        // Test a graph with two vertices and no negative cycle
        vector<vector<int>> graph10 = {{0, 1}, {1, 0}};
        g.loadGraph(graph10);
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found.");

        vector<vector<int>> graph3 = {
            {0, -1, 2, 0, 1, 2},
            {3, 0, -2, 1, 0, 3},
            {4, 5, 0, 3, 2, 4},
            {0, -4, 0, 0, 3, 5},
            {0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}};
        g.loadGraph(graph3);
        cout << ariel::Algorithms::negativeCycle(g) << endl;
        CHECK(ariel::Algorithms::negativeCycle(g).find("Negative cycle found:") != string::npos);
    }
}

TEST_CASE("Graph Class Tests")
{
    SUBCASE("Test isValidGraph")
    {
        ariel::Graph g;
        // Valid graph
        vector<vector<int>> validGraph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        CHECK(g.isValidGraph(validGraph) == true);

        // Invalid graph (not square matrix)
        vector<vector<int>> invalidGraph1 = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
        CHECK(g.isValidGraph(invalidGraph1) == false);

        // Test an empty graph
        vector<vector<int>> emptyGraph;
        CHECK(g.isValidGraph(emptyGraph) == false);

        // Test a valid square graph
        vector<vector<int>> validSquareGraph = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
        CHECK(g.isValidGraph(validSquareGraph) == true);

        vector<vector<int>> validGraph1 = {
            {0, -1, 0},
            {-1, 0, 1},
            {0, 1, 0}};
        CHECK(g.isValidGraph(validGraph1) == true);

        vector<vector<int>> validGraph2 = {
            {1, 1, 0},
            {1, 1, 1},
            {0, 1, 1}};
        CHECK(g.isValidGraph(validGraph2) == true);
    }

    SUBCASE("Test loadGraph")
    {
        ariel::Graph g;
        vector<vector<int>> invalidGraph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
        CHECK_THROWS(g.loadGraph(invalidGraph));

        vector<vector<int>> validSquareGraph = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        CHECK_NOTHROW(g.loadGraph(validSquareGraph));

        // Test loading an empty graph
        vector<vector<int>> emptyGraph;
        CHECK_THROWS(g.loadGraph(emptyGraph));

        // Test loading a valid square graph
        vector<vector<int>> validSquareGraph1 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
        CHECK_NOTHROW(g.loadGraph(validSquareGraph1));

        // Test loading an invalid graph (non-square matrix)
        vector<vector<int>> invalidGraph1 = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
        CHECK_THROWS(g.loadGraph(invalidGraph1));

        // Test loading a graph with negative weights
        vector<vector<int>> invalidGraph2 = {
            {0, -1, 0},
            {-1, 0, 1},
            {0, 1, 0}};
        CHECK_NOTHROW(g.loadGraph(invalidGraph2));

        // Test loading a graph with non-zero diagonal elements
        vector<vector<int>> invalidGraph3 = {
            {1, 1, 0},
            {1, 1, 1},
            {0, 1, 1}};
        CHECK_NOTHROW(g.loadGraph(invalidGraph3));
    }

    SUBCASE("Test getVertices")
    {
        ariel::Graph g;
        // Test an empty graph
        CHECK(g.getVertices() == 0);

        // Test a graph with 3 vertices
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph1);
        CHECK(g.getVertices() == 3);

        // Test a graph with 5 vertices
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(g.getVertices() == 5);
    }
}

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 + g2;
    CHECK(g3.toString() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    g1 += g2;
    CHECK(g1.toString() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 - g2;
    CHECK(g3.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    g1 -= g2;
    CHECK(g1.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 * g2;
    CHECK(g3.toString() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

TEST_CASE("Test scalar multiplication and division")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2 = g1 * 3;
    CHECK(g2.toString() == "[0, 3, 0]\n[3, 0, 3]\n[0, 3, 0]");

    g1 *= 2;
    CHECK(g1.toString() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    ariel::Graph g3 = g2 / 3;
    CHECK(g3.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    g2 /= 3;
    CHECK(g2.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test unary operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2 = +g1;
    CHECK(g2.toString() == g1.toString());

    ariel::Graph g3 = -g1;
    CHECK(g3.toString() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

TEST_CASE("Test increment and decrement operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ++g1;
    CHECK(g1.toString() == "[1, 2, 1]\n[2, 1, 2]\n[1, 2, 1]");

    g1++;
    CHECK(g1.toString() == "[2, 3, 2]\n[3, 2, 3]\n[2, 3, 2]");

    --g1;
    CHECK(g1.toString() == "[1, 2, 1]\n[2, 1, 2]\n[1, 2, 1]");

    g1--;
    CHECK(g1.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test comparison operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0,0},
        {1,0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1},
        {0, 0}};
    g2.loadGraph(graph2);


    CHECK(g1 != g2);
    CHECK(g1 == g1);

    ariel::Graph g3;
    g3.loadGraph(graph1);



    //CHECK(g1 == g3);
    //CHECK(g1 <= g3);
    //CHECK(g1 >= g3);
    CHECK(g2 > g1);
    CHECK(g1 < g2);
}

TEST_CASE("Test invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {0, 1, 1, 1}};
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g3.loadGraph(graph3);

    CHECK_THROWS(g1 + g2);
    CHECK_THROWS(g1 - g2);
    CHECK_THROWS(g1 * g2);
    CHECK_THROWS(g1 + g3);
    CHECK_THROWS(g1 - g3);
    CHECK_THROWS(g1 * g3);
    CHECK_THROWS(g1 / 0);
}

TEST_CASE("Edge cases")
{
    ariel::Graph g1;
    vector<vector<int>> emptyGraph = {};
    CHECK_THROWS(g1.loadGraph(emptyGraph));

    ariel::Graph g2;
    vector<vector<int>> nonSquareGraph = {
        {0, 1},
        {1, 0},
        {0, 1}};
    CHECK_THROWS(g2.loadGraph(nonSquareGraph));

    ariel::Graph g3;
    vector<vector<int>> oneElementGraph = {
        {42}};
    g3.loadGraph(oneElementGraph);
    CHECK(g3.toString() == "[42]");
}
