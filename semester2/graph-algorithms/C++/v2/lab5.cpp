#include <set>

#include "graph.h"
#include <vector>
using namespace std;

/*
 * 8. Given an undirected graph with costs satisfying the triangle inequality, find a Hamiltonian cycle
 * of no more than twice the minimum cost in O(m+n log n).
 */

typedef pair<int, int> Edge;

class CompareByCost {
protected:
    const Graph& graph;
public:
    explicit CompareByCost(const Graph& graph): graph(graph) {}

    bool operator()(const Edge& first, const Edge& second) const {
        return graph.getEdgeCost(first.first, first.second) >
                graph.getEdgeCost(second.first, second.second);
    }
};

void Graph::TSPDFS(int node, vector<int>& visited, vector<int>& path) {
    visited[node] = true;
    path.push_back(node);

    for (const auto& neighbor : this->outEdges[node]) {
        if (!visited[neighbor]) {
            TSPDFS(neighbor, visited, path);
        }
    }
}

void Graph::TSP() {
    vector<int> visited(this->numberOfNodes, false);
    vector<Edge> MST;
    priority_queue<Edge, vector<Edge>, CompareByCost> pq(CompareByCost(*this));

    int source = 0;
    visited[source] = true;

    for (const auto& neighbor : this->outEdges[source]) {
        pq.emplace(source, neighbor);
    }

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        int first = edge.first;
        int second = edge.second;

        if (visited[first] && visited[second])
            continue;

        MST.push_back(edge);

        int newNode = visited[first] ? second : first;
        visited[newNode] = true;

        for (const auto& neighbor : this->outEdges[newNode]) {
            if (!visited[neighbor]) {
                pq.emplace(newNode, neighbor);
            }
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<int> path;

    Graph TS(this->numberOfNodes, 0);
    for (const auto& edge : MST) {
        TS.addEdge(edge.first, edge.second, getEdgeCost(edge.first, edge.second));
        TS.addEdge(edge.second, edge.first, getEdgeCost(edge.first, edge.second));
    }

    TS.TSPDFS(source, visited, path);
    path.push_back(source);

    int totalCost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        totalCost += getEdgeCost(path[i], path[i + 1]);
    }

    cout << "2-approximation using Prim's algorithm:\n";
    cout << "The hamiltonian cycle is: \n";
    for (int node : path) {
        cout << node << ' ';
    }
    cout << '\n';
    cout << "The cost is: " << totalCost << ".\n";
}

bool Graph::validHamiltonianGraph(vector<int>& visited) const {
    for (int i = 0; i < this->numberOfNodes; i++)
        if (visited[i] != 1)
            return false;

    return true;
}

void Graph::backtracking(int node, int length, vector<int>& visited, int& minCost, int& currentCost, vector<int>& path, vector<int>& minPath) {
    for (int i = 0; i < this->numberOfNodes; i++) {
        if (!visited[i] && isEdge(node, i)) {

            visited[i] = 1;
            currentCost += getEdgeCost(node, i);
            path.push_back(i);

            if (validHamiltonianGraph(visited)) {
                if (isEdge(i, 0)) {
                    currentCost += getEdgeCost(i, 0);
                    if (currentCost < minCost) {
                        minCost = currentCost;
                        minPath.clear();
                        minPath = path;
                    }
                    currentCost -= getEdgeCost(i, 0);
                }
            } else {
                backtracking(i, length + 1, visited, minCost, currentCost, path, minPath);
            }

            path.erase(path.begin() + distance(path.begin(), find(path.begin(), path.end(), i)));
            currentCost -= getEdgeCost(node, i);
            visited[i] = 0;
        }
    }
}

void Graph::TSP_backtracking() {

    vector<int> visited(numberOfNodes, 0);
    vector<int> currentPath;
    vector<int> minPath;
    int minCost = INT_MAX, currentCost = 0;
    visited[0] = 1;
    backtracking(0, 1, visited, minCost, currentCost, currentPath, minPath);

    cout << "Backtracking Algorithm:\n";
    cout << "The minimum cost hamiltonian cycle is:\n";
    cout << 0 << " ";
    for(auto node: minPath) {
        cout << node << " ";
    }
    cout << 0 << '\n';
    cout << "The cost is: " << minCost << ".\n\n";
}

int Graph::findRoot(int u) {
    if (u != parent[u]) {
        parent[u] = findRoot(parent[u]);
    }
    return parent[u];
}

void Graph::unionSets(int u, int v) {
    int rootU = findRoot(u);
    int rootV = findRoot(v);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

vector<pair<int, int>> Graph::Kruskal() {

    vector<pair<int, int>> MST;

    parent.resize(numberOfNodes);
    rank.resize(numberOfNodes, 0);
    for (int i = 0; i < numberOfNodes; ++i) {
        parent[i] = i;
    }

    vector<tuple<int, int, int>> edgeList;
    for (const auto& edge : this->edgeCost) {
        edgeList.emplace_back(edge.second, edge.first.first, edge.first.second);
    }
    sort(edgeList.begin(), edgeList.end());

    for (const auto& [cost, u, v] : edgeList) {
        if (findRoot(u) != findRoot(v)) {
            unionSets(u, v);
            MST.emplace_back(u, v);
        }
    }

    Graph TS(this->numberOfNodes, 0);
    for (const auto& edge : MST) {
        TS.addEdge(edge.first, edge.second, getEdgeCost(edge.first, edge.second));
        TS.addEdge(edge.second, edge.first, getEdgeCost(edge.first, edge.second));
    }

    vector<int> visited(this->numberOfNodes, false);
    vector<int> path;
    TSPDFS(0, visited, path);
    path.push_back(0);

    int totalCost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        if (isEdge(path[i], path[i + 1])) {
            totalCost += getEdgeCost(path[i], path[i + 1]);
        } else {
            cout << "Invalid edge in path from " << path[i] << " to " << path[i + 1] << "\n";
        }
    }

    cout << "2-approximation using Kruskal's algorithm:\n";
    cout << "The hamiltonian cycle is: \n";
    for (int node : path) {
        cout << node << ' ';
    }
    cout << '\n';
    cout << "The cost is: " << totalCost << ".\n\n";

    return MST;
}
