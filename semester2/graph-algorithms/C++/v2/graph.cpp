#pragma once
#include "graph.h"
#include <sstream>
#include <utility>

Graph::Graph(const std::string& filePath):
    numberOfNodes(0), numberOfEdges(0){
    int numberOfEdgesToGenerate;
    std::ifstream fin(filePath);

    fin >> this->numberOfNodes >> numberOfEdgesToGenerate;
    this->indices.resize(this->numberOfNodes + 1, 0);

    int source, target, cost;
    for(int i = 0; i < numberOfEdgesToGenerate; i++){
        fin >> source >> target >> cost;
        this->addEdge(source, target, cost);
        this->edges.emplace_back(source, target);
    }
}

Graph::Graph(int numberOfNodesToGenerate, int numberOfEdgesToGenerate):
    numberOfNodes(numberOfNodesToGenerate), numberOfEdges(0){
	this->indices.resize(this->numberOfNodes + 1, 0);
    int source, target, cost;

    srand(static_cast<unsigned int>(time(nullptr)));

    while(numberOfEdgesToGenerate > 0){
        target = rand() % numberOfNodes + 1;
        source = rand() % numberOfNodes + 1;
        cost = rand() % 20;

        if(!this->isEdge(source, target)){
            numberOfEdgesToGenerate--;
            this->addEdge(source, target, cost);
        }
    }
}

Graph::Graph(const Graph& other)
        : numberOfEdges(other.numberOfEdges),
          numberOfNodes(other.numberOfNodes),
          inEdges(other.inEdges),
          outEdges(other.outEdges),
          edgeCost(other.edgeCost) {
}

Graph Graph::makeUndirectedCopy() const {
    Graph undirectedGraph(this->numberOfNodes, 0);

    for (const auto& edgeList : this->outEdges) {
        int source = edgeList.first;
        for (int target : edgeList.second) {
            int cost = this->edgeCost.at({source, target});
            undirectedGraph.addEdge(source, target, cost);
            if (!undirectedGraph.isEdge(target, source)) {
                undirectedGraph.addEdge(target, source, cost);
            }
        }
    }

    return undirectedGraph;
}

Graph& Graph::operator=(const Graph& other) {
    numberOfEdges = other.numberOfEdges;
    numberOfNodes = other.numberOfNodes;
    inEdges = other.inEdges;
    outEdges = other.outEdges;
    edgeCost = other.edgeCost;

    return *this;
}

int Graph::getNumberOfEdges() const {
    return this->numberOfEdges;
}

int Graph::getNumberOfNodes() const {
    return this->numberOfNodes;
}

int Graph::getInDegree(int node) const {
    auto it = this->inEdges.find(node);
    return it != this->inEdges.end() ? it->second.size() : 0;
}

int Graph::getOutDegree(int node) const {
    auto it = this->outEdges.find(node);
    return it != this->outEdges.end() ? it->second.size() : 0;
}

int Graph::getEdgeCost(int node1, int node2) const {
    auto it = this->edgeCost.find({node1, node2});
    if (it != this->edgeCost.end()) {
        return it->second;
    } else {
        std::ostringstream msg;
        msg << "Edge does not exist between nodes " << node1 << " and " << node2;
        throw std::out_of_range(msg.str());
    }
}


bool Graph::isEdge(int node1, int node2) {
    return this->edgeCost.find({node1, node2}) != this->edgeCost.end();
}

bool Graph::isNode(int node){
    return inEdges.find(node) != inEdges.end() || outEdges.find(node) != outEdges.end();
}

void Graph::setEdgeCost(int node1, int node2, int cost) {
    this->edgeCost[{node1, node2}] = cost;
}

void Graph::addEdge(int node1, int node2, int cost) {
    this->numberOfEdges++;
    this->outEdges[node1].push_back(node2);
    this->inEdges[node2].push_back(node1);
    this->edgeCost[{node1, node2}] = cost;
}

void Graph::addNode() {
    this->numberOfNodes++;
    inEdges[this->numberOfNodes];
    outEdges[this->numberOfNodes];
}

void Graph::removeEdge(int node1, int node2) {
    auto& edgesFromNode1 = outEdges[node1];
    auto newEndOut = std::remove(edgesFromNode1.begin(), edgesFromNode1.end(), node2);
    edgesFromNode1.resize(std::distance(edgesFromNode1.begin(), newEndOut));

    auto& edgesToNode2 = inEdges[node2];
    auto newEndIn = std::remove(edgesToNode2.begin(), edgesToNode2.end(), node1);
    edgesToNode2.resize(std::distance(edgesToNode2.begin(), newEndIn));

    edgeCost.erase({node1, node2});

    numberOfEdges--;
}

void Graph::removeNode(int node) {
    for (int connectedNode: this->outEdges[node]) {
        auto& edgesToConnectedNode = this->inEdges[connectedNode];
        auto newEndIn = std::remove(edgesToConnectedNode.begin(), edgesToConnectedNode.end(), node);
        edgesToConnectedNode.resize(std::distance(edgesToConnectedNode.begin(), newEndIn));
        this->numberOfEdges--;
    }

    for (int connectedNode: this->inEdges[node]) {
        auto& edgesFromConnectedNode = this->outEdges[connectedNode];
        auto newEndOut = std::remove(edgesFromConnectedNode.begin(), edgesFromConnectedNode.end(), node);
        edgesFromConnectedNode.resize(std::distance(edgesFromConnectedNode.begin(), newEndOut));
        this->numberOfEdges--;
    }

    this->inEdges.erase(node);
    this->outEdges.erase(node);

    auto it = this->edgeCost.begin();
    while (it != this->edgeCost.end()) {
        if (it->first.first == node || it->first.second == node) {
            it = this->edgeCost.erase(it);
        } else {
            ++it;
        }
    }

    this->numberOfNodes--;
}

Graph::edgeIterator::edgeIterator(int node, std::vector<int> edges) {
    this->currentEdgeIndex = 0;
    this->edges = std::move(edges);
}

void Graph::edgeIterator::next() {
    if(this->valid())
        this->currentEdgeIndex++;
}

void Graph::edgeIterator::first() {
    this->currentEdgeIndex = 0;
}

bool Graph::edgeIterator::valid() {
    return this->currentEdgeIndex < this->edges.size();
}

int Graph::edgeIterator::getCurrent() {
    if (this->valid()) {
        return this->edges[this->currentEdgeIndex];
    } else {
        throw std::out_of_range("Attempted to access an invalid edge.");
    }
}

void Graph::writeToFile(const std::string& filePath, const Graph& graph) {
    std::ofstream fout(filePath);

    fout << graph.getNumberOfNodes() << " " << graph.getNumberOfEdges() << '\n';
    for (const auto& edgePair : graph.edgeCost) {
        int source = edgePair.first.first;
        int target = edgePair.first.second;
        int cost = edgePair.second;

        fout << source << " " << target << " " << cost << '\n';
    }

    fout.close();
}

void Graph::printGraph() const {
    std::cout << numberOfNodes << " " << numberOfEdges << "\n";

    for (const auto& edge : edgeCost) {
        int source = edge.first.first;
        int target = edge.first.second;
        int cost = edge.second;
        std::cout << source << " " << target << " " << cost << "\n";
    }
}