#include "Graph.h"
#include <stack>
#include <vector>
using namespace std;

// DIJKSTRA, QUEUE
int Graph::Dijkstra(int source, int destination) {
    vector<int> dist(this->numberOfEdges, 1e9);
    queue<int> q;
    dist[source] = 0;
    q.push(source);

    while(!q.empty()) {
        int current = q.front();
        q.pop();
        for(auto neighbor: outEdges[current]) {
            int cost = getEdgeCost(current, neighbor);
            if(dist[neighbor] > dist[current] + cost) {
                dist[neighbor] = dist[current] + cost;
                q.push(neighbor);
            }
        }
    }

    return dist[destination];
}

void Graph::topSortDFS(int current, vector<int>& visited, std::stack<int>& order) {
    visited[current] = 1;

    for(auto neighbor: outEdges[current])
        if(!visited[neighbor])
            topSortDFS(neighbor, visited, order);

    order.push(current);
}

stack<int> Graph::topSort() {
    vector<int> visited(this->numberOfNodes, 0);
    std::stack<int> order;

    for(int i = 0; i < this->numberOfNodes; i++)
        if(!visited[i])
            topSortDFS(i, visited, order);

    return order;
}
