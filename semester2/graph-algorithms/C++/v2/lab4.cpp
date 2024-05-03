#pragma once
#include "graph.h"
#include <queue>
using namespace std;

/*  4. Write a program that, given a graph with costs, does the following:
    - verify if the corresponding graph is a DAG and performs a topological sorting of the activities
        using the algorithm based on predecessor counters;
    - if it is a DAG, finds a highest cost path between two given vertices, in O(m+n).
 */

bool Graph::checkIfDAG() {
    queue<int> q;
    vector<int> visited (numberOfNodes + 1, 0);
    vector<int> inDegree (numberOfNodes + 1, 0);
    int count = 0;

    for(int i = 0; i < this->numberOfNodes; i++) {
        inDegree[i] = getInDegree(i);
        if (inDegree[i] == 0) {
            q.push(i);
            visited[i] = 1;
        }
    }

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        count++;
        for(int i: outEdges[v]) {
            if (!visited[i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
    return count == this->numberOfNodes;
}

/*
 *  2B. Write a program that, given a graph, does the following:

    verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
    if it is a DAG, finds the number of distinct paths between two given vertices, in O(m+n).
 */

int Graph::numberOfPathsDP(int source, int destination) {
    std::stack<int> order = topSort();
    std::vector<int> pathCounts(this->numberOfNodes, 0);
    pathCounts[source] = 1;

    while(!order.empty()) {
        int current = order.top();
        order.pop();

        for(auto neighbor: outEdges[current])
            pathCounts[neighbor] += pathCounts[current];
    }

    return pathCounts[destination];
}

/*
 *  3B. Write a program that, given a graph with costs, does the following:

    verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
    if it is a DAG, finds the number of distinct lowest cost paths between two given vertices, in O(m+n).
 */

std::pair<int, int> Graph::numberOfLowestCostPaths(int source, int destination) {
    std::stack<int> order = topSort();
    std::vector<int> pathCounts(this->numberOfNodes, 0);
    std::vector<int> minCost(this->numberOfNodes, 1e9);

    pathCounts[source] = 1;
    minCost[source] = 0;

    while(!order.empty()) {
        int current = order.top();
        order.pop();

        for(auto neighbor: outEdges[current]) {
            int cost = getEdgeCost(current, neighbor);

            if(minCost[neighbor] > minCost[current] + cost) {
                minCost[neighbor] = minCost[current] + cost;
                pathCounts[neighbor] = pathCounts[current];
            } else if(minCost[neighbor] == minCost[current] + cost) {
                pathCounts[neighbor] += pathCounts[current];
            }
        }
    }

    return {pathCounts[destination], minCost[destination]};
}