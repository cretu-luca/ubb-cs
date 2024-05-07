#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Graph{
public:

    int numberOfNodes, numberOfEdges;

    unordered_map<int, unordered_map<int, int>> edges;
    unordered_map<int, int> inDegrees;

    Graph(int numberOfNodes, int numberOfEdges);

    vector<vector<int>> components;
    int visited[10000];

    Graph deepCopy() const;

    int getNumberOfEdges() const;
    int getNumberOfNodes() const;
    int getInDegree(int node);
    int getOutDegree(int node);
    int getEdgeCost(int node1, int node2);

    bool isEdge(int node1, int node2);

    void addEdge(int source, int target, int cost);
    void setEdgeCost(int node1, int node2, int cost);
    void removeEdge(int source, int target);
    void removeNode(int node);
    void generateGraph(int numberOfNodes, int numberOfEdges);
    void findConnectedComponents();
    void DFS_components(int node, int componentIndex);
};