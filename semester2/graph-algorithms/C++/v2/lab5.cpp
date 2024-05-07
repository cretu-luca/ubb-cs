#include "graph.h"
#include <vector>
using namespace std;

/*
 * 8. Given an undirected graph with costs satisfying the triangle inequality, find a Hamiltonian cycle
 * of no more than twice the minimum cost in O(m+n log n).
 */

int Graph::root(int a, vector<int> parent) {
    if(parent[a] == a)
        return a;
    return parent[a] = root(parent[a], parent);
}

vector<pair<int, int>> Graph::Kruskal(vector<pair<int, int>>& edges, vector<int> parent) {
    vector<pair<int, int>> tree (this->numberOfNodes);

    int cost = 0, pos = 0;
    for(int i = 0; i < this->numberOfEdges; i++) {
        int source = root(edges[i].first, parent);
        int destination = root(edges[i].second, parent);

        if(source != destination) {
            parent[source] = parent[destination];
            cost += this->getEdgeCost(source, destination);
            tree[++pos] = edges[i];
        }
    }

    cout << "Minimum cost is " << cost << "\n";
    for(int i = 0; i < pos; i++)
        cout << tree[i].first << " " << tree[i].second << '\n';

    cout << "done\n";
    return tree;
}

void Graph::TSP() {
    vector<int> parent (this->numberOfNodes);
    vector<pair<int, int>> edges = getUndirectedEdges();

    for(int i = 0; i < this->numberOfNodes; i++) {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end(), [this](pair<int, int> first, pair<int, int> second) {
        return this->getEdgeCost(first.first, first.second) >
            this->getEdgeCost(second.first, second.second);
    });

    Kruskal(edges, parent);
}

vector<pair<int, int>> Graph::getUndirectedEdges() {
    vector<pair<int, int>> undirectedEdges(this->numberOfEdges * 2);
    for(int i = 0; i < this->numberOfNodes; i++) {
        for(auto neighbor: outEdges[i]) {
            if(!isEdge(neighbor, i)) {
                this->addEdge(neighbor, i, getEdgeCost(i, neighbor));
                undirectedEdges.emplace_back(neighbor, i);
            }
        }

        for(auto neighbor: inEdges[i]) {
            if(!isEdge(i, neighbor)) {
                this->addEdge(i, neighbor, getEdgeCost(neighbor, i));
                undirectedEdges.emplace_back(i, neighbor);
            }
        }
    }

    return undirectedEdges;
}