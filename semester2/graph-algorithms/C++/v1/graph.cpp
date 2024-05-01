#include "graph.h"

Graph::Graph(int numberOfNodes, int numberOfEdges) {
    this->numberOfNodes = numberOfNodes;
    this->numberOfEdges = numberOfEdges;
}

void Graph::generateGraph(int numberOfNodes, int numberOfEdges) {
    int source, target, cost;
    while(numberOfEdges > 0){
        source = rand() % numberOfNodes;
        target = rand() % numberOfNodes;
        cost = rand() % 20;

        if(!this->isEdge(source, target)){
            numberOfEdges--;
            this->addEdge(source, target, cost);
        }
    }
}

void Graph::DFS_components(int node, int componentIndex){
    cout << "here1";
    this->visited[node] = componentIndex;

    this->components[componentIndex].push_back(node);
    for(auto pair_it: this->edges[node])
        if(!visited[pair_it.first]) {
            DFS_components(pair_it.first, componentIndex);
            cout << "loop";
        }
}

void Graph::findConnectedComponents(){
    cout << "here";
    int componentIndex = 0;

    for(int node = 1; node <= numberOfNodes; node++)
        if(!visited[node]){
            componentIndex++;
            DFS_components(node, componentIndex);
        }
    cout << "here2";
    for(int i = 0; i < componentIndex; i++) {
        cout << "Component " << i;
        for (auto node: this->components[i])
            cout << node << " ";
        cout << endl;
    }
}

Graph Graph::deepCopy() const{
    Graph copyGraph(this->numberOfNodes, 0);

    for(const auto &nodePair: this->edges){
        int sourceNode = nodePair.first;
        const auto &targetMap = nodePair.second;
        for(const auto &edgePair: targetMap){
            int targetNode = edgePair.first;
            int edgeCost = edgePair.second;

            copyGraph.addEdge(sourceNode, targetNode, edgeCost);
        }
    }

    copyGraph.numberOfEdges = this->numberOfEdges;

    return copyGraph;
}

int Graph::getNumberOfNodes() const{
    return this->numberOfNodes;
}

int Graph::getNumberOfEdges() const{
    return this->numberOfEdges;
}

int Graph::getInDegree(int node){
    return this->inDegrees[node];
}

int Graph::getOutDegree(int node){
    return this->edges[node].size();
}

int Graph::getEdgeCost(int node1, int node2) {
    return this->edges[node1][node2];
}

void Graph::setEdgeCost(int node1, int node2, int cost){
    this->edges[node1][node2] = cost;
}

bool Graph::isEdge(int node1, int node2){
    auto it = edges.find(node1);
    if(it != edges.end())
        return it->second.find(node2) != it->second.end();

    return false;
}

void Graph::addEdge(int source, int target, int cost){
    if(!this->isEdge(source, target)) {
        this->inDegrees[target]++;
        this->edges[source][target] = cost;
    }
}

void Graph::removeEdge(int source, int target){
    if(this->edges[source].erase(target)) {
        this->inDegrees[target]--;
        numberOfEdges--;
    }
}

void Graph::removeNode(int node) {
    // erases the node and removes the outgoing edges
    auto it = edges.find(node);
    if(it != edges.end()){
        this->numberOfEdges = this->numberOfEdges - it->second.size();
        edges.erase(it);
    }

    // removes the incoming edges
    for(auto &pair: edges){
        auto &targetEdges = pair.second;
        if(targetEdges.erase(node) > 0) {
            this->inDegrees[node]--;
            this->numberOfEdges--;
        }
    }
    this->inDegrees.erase(node);
}
