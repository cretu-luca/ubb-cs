#pragma once
#include "graph.h"

/*
7. Write a program that, given a graph with costs that has no negative cost cycles and two vertices,
finds the lowest cost walk between the given vertices. The program shall use the Floyd-Warshall algorithm.
*/

#define INF 1e9

int Graph::Floyd_Warshall(int node1, int node2) {
    std::vector<std::vector<int>> distance(this->numberOfNodes + 1, std::vector<int>(this->numberOfNodes + 1, INF));

    for(auto pair: this->edgeCost) {
        distance[pair.first.first][pair.first.second] = pair.second;
    }

    for(int k = 1; k <= this->numberOfNodes; k++) {
        for (int i = 1; i <= this->numberOfNodes; i++) {
            for (int j = 1; j <= this->numberOfNodes; j++) {
                if (distance[i][j] > distance[i][k] + distance[k][j] && distance[k][j] != INF && distance[i][k] != INF)
                    distance[i][j] = distance[i][k] + distance[k][j];
            }
        }
    }

    return distance[node1][node2];
}

std::pair<int, std::vector<int>> Graph::getFloydWarshallPath(int source, int destination, Graph graph) {
    int n = graph.getNumberOfNodes();
    std::vector<std::vector<int>> distance(n + 1, std::vector<int>(n + 1, INF));
    std::vector<std::vector<int>> next(n + 1, std::vector<int>(n + 1, -1));

    for(auto pair: graph.getEdgeCosts()) {
        distance[pair.first.first][pair.first.second] = pair.second;
        next[pair.first.first][pair.first.second] = pair.first.second;
    }

    for(int k = 0; k <= graph.getNumberOfNodes(); k++) {
        for(int i = 0; i <= graph.getNumberOfNodes(); i++) {
            for(int j = 0; j <= graph.getNumberOfNodes(); j++) {
                if (distance[i][j] > distance[i][k] + distance[k][j] && distance[k][j] != INF && distance[i][k] != INF)
                    distance[i][j] = distance[i][k] + distance[k][j],
                    next[i][j] = next[i][k];
            }
        }
    }
    int cost = distance[source][destination];

    std::vector<int> path = {source};
    while(source != destination) {
        source = next[source][destination];
        path.push_back(source);
    }

    return std::make_pair(cost, path);
}

/*
 * 1B. Write a program that, given a graph with costs, having no negative cost cycles, and a pair of vertices,
 * finds the number of distinct walks of minimum cost between the given vertices.
 */

void Graph::backtracking_minimumCost(int previousNode, int currentNode, int destination, int& counter, std::vector<bool>& visited,
                                     int currentCost, int minimumCost) {
    if(previousNode != -1) {
        currentCost += edgeCost[{previousNode, currentNode}];
    }
    visited[currentNode] = true;

    if(currentNode == destination) {
        if(currentCost == minimumCost)
            counter++;
    } else {
        for(int neighbor : outEdges[currentNode]) {
            if(!visited[neighbor]) {
                backtracking_minimumCost(currentNode, neighbor, destination, counter, visited, currentCost, minimumCost);
            }
        }
    }

    visited[currentNode] = false;
}

void Graph::numberOfMinimalCosts(int source, int destination) {
    int minimumCost = this->Floyd_Warshall(source, destination);

    std::vector<bool> visited (this->numberOfNodes, false);
    int counter = 0;
    backtracking_minimumCost(-1, source, destination, counter, visited, 0, minimumCost);

    std::cout << "The minimum cost from node " << source << " to " << destination << " is " << minimumCost << '\n';
    std::cout << "There are " << std::max(counter - 1, 1)  << " paths with cost " << minimumCost << '\n';
}

/*
 * 2B. Write a program that, given a graph that has no cycles (a directed acyclic graph, DAG) and a pair of vertices,
 * finds the number of distinct walks between the given vertices.
 */

void Graph::backtracking(int currentNode, int destination, int& counter, std::vector<bool>& visited) {
    visited[currentNode] = true;

    if(currentNode == destination)
        counter++;
    else {
        for(auto neighbor: this->outEdges[currentNode])
            if(!visited[neighbor])
                backtracking(neighbor, destination, counter, visited);
    }

    visited[currentNode] = false;
}

void Graph::numberOfPaths(int source, int destination) {

    std::vector<bool> visited (this->numberOfNodes, false);
    int counter = 0;
    backtracking(source, destination, counter, visited);

    std::cout << "From node " << source << " to node " << destination << " there are " << std::max(counter - 1, 1) << " paths\n";
}

/*
 * 3B. Use a lowest cost path algorithm and a new implementation of the interface from lab 1 to solve the
 * bridge and torch problem: A number of people (up to 20) must cross a bridge, at night. They have a torch
 * that provides only enough light for at most two people to cross together. For each person, we are given
 * the time needed to cross the bridge alone. If two people cross together, they cross at the pace of the slowest one.
 * Find a solution for all to cross the river, using as little time as possible.
*/
std::vector<bool> getBinaryVector(int number, int size) {
    std::vector<bool> binaryVector(size, false);
    int index = size - 1;
    while (number > 0) {
        binaryVector[index--] = number % 2;
        number /= 2;
    }
    return binaryVector;
}

bool isLegalMove(std::vector<bool> currentState, std::vector<bool> nextState) {
    int count = 0;

    for(int i = 0; i < currentState.size(); i++)
        if(currentState[i] != nextState[i])
            count++;

    if(count == 1 || count == 2)
        return true;

    return false;
}

int getTime(std::vector<bool> currentState, std::vector<bool> nextState, std::vector<int> timeNeeded) {
    int time = 0;
    for(int i = 0; i < currentState.size(); i++)
        if(currentState[i] != nextState[i])
            time = std::max(time, timeNeeded[i]);

    return time;
}

Graph::Graph(int numberOfPeople, std::vector<int> timeNeeded) {
    this->numberOfNodes = 1 << numberOfPeople;
    for (int i = 0; i < this->numberOfNodes; i++) {
        for (int j = 0; j < this->numberOfNodes; j++) {
            if (i != j && isLegalMove(getBinaryVector(i, numberOfPeople), getBinaryVector(j, numberOfPeople))) {
                int cost = getTime(getBinaryVector(i, numberOfPeople), getBinaryVector(j, numberOfPeople), timeNeeded);
                this->addEdge(i, j, cost);
            }
        }
    }
}

void Graph::solveBridgeTorch(int numberOfPeople, std::vector<int> timeNeeded) {
    Graph graph(numberOfPeople, timeNeeded);

    graph.printGraph();

    int lastState = (1 << numberOfPeople) - 1;
    std::pair<int, std::vector<int>> solution = getFloydWarshallPath(0, lastState, graph);

    std::cout << "The cost is " << solution.first << '\n';
    std::cout << "The solution is:\n";

    for(auto node: solution.second)
        std::cout << node << " ";

    std::cout << '\n';
}