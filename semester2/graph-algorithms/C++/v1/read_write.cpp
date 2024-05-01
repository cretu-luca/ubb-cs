#include "read_write.h"

Graph readFromFile(const string& filePath){
    ifstream fin(filePath);

    int numberOfNodes, numberOfEdges, source, target, cost;
    fin >> numberOfNodes >> numberOfEdges;
    Graph graph(numberOfNodes, numberOfEdges);
    for(int i = 0; i < numberOfEdges; i++){
        fin >> source >> target >> cost;
        graph.addEdge(source, target, cost);
    }

    return graph;
}

void writeToFile(const string& filePath, const Graph& graph){
    ofstream fout(filePath);

    fout << graph.getNumberOfNodes() << " " << graph.getNumberOfEdges() << '\n';
    for(const auto &iter: graph.edges){
        for(const auto &iter2: iter.second)
            fout << iter.first << " " << iter2.first << " " << iter2.second << '\n';
    }
}
