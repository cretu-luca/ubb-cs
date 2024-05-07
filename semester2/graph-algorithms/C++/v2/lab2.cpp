#pragma once
#include "graph.h"

/*
 * 3. Write a program that finds the connected components of an undirected
 *      graph using a depth-first traversal of the graph.
 */

void Graph::DFS_components_iterative(Graph &graph, int node, int componentIndex) {
    std::stack<int> recursionStack;
    int currentNode;

    recursionStack.emplace(node);
    while(!recursionStack.empty()) {
        currentNode = recursionStack.top();
        recursionStack.pop();

        if (!this->indices[currentNode]) {
            this->indices[currentNode] = componentIndex;
            this->components[componentIndex - 1].push_back(currentNode);

            for (int neighbor: this->outEdges[currentNode])
                if (!this->indices[neighbor])
                    recursionStack.push(neighbor);

            for (int neighbor: this->inEdges[currentNode])
                if (!this->indices[neighbor])
                    recursionStack.push(neighbor);
        }
    }
}

void Graph::findConnectedComponents() {
    this->indices.assign(this->numberOfNodes + 1, 0);
    this->components.clear();
    int componentIndex = 0;

    for(int node = 1; node <= this->numberOfNodes; ++node) {
        if(!this->indices[node]) {
            this->components.emplace_back();
            DFS_components_iterative(*this, node, ++componentIndex);
        }
    }

    for(int index = 0; index < componentIndex; ++index) {
        std::cout << "Component " << (index + 1) << ":\n";
        for(int node: components[index])
            std::cout << node << " ";
        std::cout << "\n";
    }
}

/*
 * 1B. Write a program that finds the strongly-connected components of a directed graph in O(n+m)
 *      (n=no. of vertices, m=no. of arcs)
 */

Graph Graph::transposedGraph(Graph& other) {
    Graph transpose(other.getNumberOfNodes(), 0);

    for (const auto& edgeList: other.getOutEdges()) {
        int source = edgeList.first;
        for (int target : edgeList.second) {
            int cost = other.getEdgeCost(source, target);
            transpose.addEdge(target, source, cost);
        }
    }

    return transpose;
}

void Graph::DFS_timing_iterative(Graph& graph, int node, std::stack<int>& stack){
    std::stack<int> nodeStack;
    nodeStack.push(node);
    int currentNode;

    while(!nodeStack.empty()) {
        currentNode = nodeStack.top();
        nodeStack.pop();

        if(graph.indices[currentNode] == 0) {
            graph.indices[currentNode] = 1;
            stack.push(currentNode);

            for(int neighbor: graph.outEdges[currentNode]) {
                if(graph.indices[neighbor] == 0) {
                    nodeStack.push(neighbor);
                }
            }
        }
    }
}

void Graph::DFS_iterative(Graph& graph, int node, int componentIndex){
    std::stack<int> recursionStack;
    int currentNode;

    recursionStack.emplace(node);
    while(!recursionStack.empty()) {
        currentNode = recursionStack.top();
        recursionStack.pop();

        if (!this->indices[currentNode]) {
            this->indices[currentNode] = componentIndex;
            this->components[componentIndex - 1].push_back(currentNode);

            for(int neighbor: this->outEdges[currentNode])
                if(!this->indices[neighbor])
                    recursionStack.push(neighbor);
        }
    }
}

void Graph::Kosaraju() {
    std::stack<int> stack1;
    this->indices.assign(this->numberOfNodes + 1, 0);
    this->components.clear();

    for(int node = 1; node <= this->numberOfNodes; node++)
        if(!this->indices[node])
            DFS_timing_iterative(*this, node, stack1);

    Graph transpose = transposedGraph(*this);

    int componentIndex = 0, pivot;
    this->indices.assign(this->numberOfNodes + 1, 0);

    while(!stack1.empty()) {
        pivot = stack1.top();
        stack1.pop();
        if(!this->indices[pivot]){
            this->components.emplace_back();
            DFS_iterative(transpose, pivot, ++componentIndex);
        }
    }

    for(int index = 0; index < componentIndex; index++) {
        std::cout << "Strongly connected component " << index + 1 << ":\n";
        for (int node: components[index])
            std::cout << node << " ";
        std::cout << "\n";
    }
}

/*
 * 2B. Write a program that finds the biconnected components of an undirected graph in O(n+m).
 */
void Graph::DFS_Tarjan(int currentNode, int parent) {
    this->disc[currentNode] = disc[parent] + 1;
    this->low[currentNode] = disc[currentNode];
    stack.push(currentNode);

    for (int neighbour: outEdges[currentNode]) {
        if (neighbour == parent)
            continue;

        // not visited yet
        if (disc[neighbour] == 0) {
            DFS_Tarjan(neighbour, currentNode);
            low[currentNode] = std::min(low[currentNode], low[neighbour]);

            // check if current node is articulation point
            if (low[neighbour] >= disc[currentNode]) {
                std::vector<int> component;
                // retrieve all nodes of the current biconnected component from the stack.
                while (stack.top() != neighbour) {
                    component.push_back(stack.top());
                    stack.pop();
                }
                component.push_back(stack.top());
                stack.pop();
                component.push_back(currentNode);

                biconnectedComponents.push_back(component);
            }
        } else { // found a back edge, update low value of current node (back edge - edge that connects a
            // vertex to an ancestor in the DFS tree)
            low[currentNode] = std::min(low[currentNode], disc[neighbour]);
        }
    }
}

void Graph::Tarjan() {
    this->disc.assign(numberOfNodes + 1, 0); // // marking when a node is accessed by the DFS
    this->low.assign(numberOfNodes + 1, 0); // records the earliest discovered vertex
    // that can be reached from subtree rooted with v or by one of v's ancestors

    while (!stack.empty()) stack.pop();
    biconnectedComponents.clear();

    for (int i = 1; i <= numberOfNodes; ++i) {
        if (disc[i] == 0) {
            DFS_Tarjan(i, i);
        }
    }

    for(int index = 0; index < this->biconnectedComponents.size(); index++) {
        std::cout << "Biconnected component " << index + 1 << ":\n";
        for (int node: biconnectedComponents[index])
            std::cout << node << " ";
        std::cout << "\n";
    }
}