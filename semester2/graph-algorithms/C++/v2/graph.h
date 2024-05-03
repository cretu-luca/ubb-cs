#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <stack>
#include <functional>
#include <iostream>
#include <fstream>
#include <queue>

class Graph {

private:
    int numberOfEdges, numberOfNodes;

    std::map<int, std::vector<int>> inEdges;
    std::map<int, std::vector<int>> outEdges;
    std::map<std::pair<int, int>, int> edgeCost;

    std::vector<int> indices = {0};
    std::vector<std::vector<int>> components;

    std::vector<int> disc, low;
    std::stack<int> stack;
    std::vector<std::vector<int>> biconnectedComponents;

public:
    Graph(int numberOfNodesToGenerate, int numberOfEdgesToGenerate);
    Graph(const std::string& filePath);
    Graph(const Graph& other);
    Graph(int numberOfPeople, std::vector<int> timeNeeded);

    Graph transposedGraph(Graph& other);
    Graph makeUndirectedCopy() const;
    Graph& operator=(const Graph& other);

    std::map<int, std::vector<int>> getInEdges() {return this->inEdges; };
    std::map<int, std::vector<int>> getOutEdges() {return this->outEdges; };
    std::map<std::pair<int, int>, int> getEdgeCosts() {return this->edgeCost; }
    std::pair<int, std::vector<int>> getFloydWarshallPath(int source, int destination, Graph graph);
    std::pair<int, int> numberOfLowestCostPaths(int source, int destination);
    std::stack<int> topSort();

    bool isEdge(int node1, int node2);
    bool isNode(int node);
    bool checkIfDAG();

    int getNumberOfEdges() const;
    int getNumberOfNodes() const;
    int getInDegree(int node) const;
    int getOutDegree(int node) const;
    int Floyd_Warshall(int node1, int node2);
    int getEdgeCost(int node1, int node2) const;
    int Dijkstra(int source, int destination);
    int numberOfPathsDP(int source, int destination);

    void setEdgeCost(int node1, int node2, int cost);
    void addEdge(int node1, int node2, int cost);
    void removeEdge(int node1, int node2);
    void addNode();
    void removeNode(int node);
    void printGraph() const;
    void DFS_iterative(Graph& graph, int node, int componentIndex);
    void DFS_timing_iterative(Graph& graph, int node, std::stack<int>& stack);
    void DFS_components_iterative(Graph &graph, int node, int componentIndex);
    void Kosaraju();
    void findConnectedComponents();
    void setInEdges(Graph& other) {this->inEdges = other.inEdges; };
    void setOutEdges(Graph& other) {this->outEdges = other.outEdges; };
    void setEdgeCosts(Graph& other) {this->edgeCost = other.edgeCost; }
    void writeToFile(const std::string& filePath, const Graph& graph);
    void DFS_Tarjan(int currentNode, int parent);
    void Tarjan();
    void backtracking(int currentNode, int destination, int& counter, std::vector<bool>& visited);
    void numberOfPaths(int source, int destination);
    void numberOfMinimalCosts(int source, int destination);
    void backtracking_minimumCost(int previousNode, int currentNode, int destination, int& counter, std::vector<bool>& visited,
                                         int currentCost, int minimumCost);
    void solveBridgeTorch(int numberOfPeople, std::vector<int> timeNeeded);
    void topSortDFS(int current, std::vector<int>& visited, std::stack<int>& order);

    class edgeIterator {
    private:
        int currentEdgeIndex;
        std::vector<int> edges;

    public:
        edgeIterator(int node, std::vector<int> edges);

        void next();
        void first();

        bool valid();

        int getCurrent();
    };
};