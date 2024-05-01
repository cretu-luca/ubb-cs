#include <iostream>
#include "read_write.h"
using namespace std;

void printGraph(Graph graph){
    cout << graph.getNumberOfNodes() << " " << graph.getNumberOfEdges() << '\n';
    for(const auto& iter: graph.edges) {
        for (const auto& iter2: iter.second)
            cout << iter.first << " " << iter2.first << " " << iter2.second << '\n';
    }
}

Graph getGraph(){
    cout << "1. Read graph from file\n";
    cout << "2. Generate random graph\n";

    int option;
    cin >> option;
    if(option == 1){
        string filePath;
        cout << "File path:\n";
        cin >> filePath;
        Graph graph = readFromFile(filePath);
        return graph;
    }
    else {
        int numberOfNodes, numberOfEdges;
        cout << "Number of nodes:\n";
        cin >> numberOfNodes;
        cout << "Number of edges:\n";
        cin >> numberOfEdges;

        while(numberOfEdges > numberOfNodes * numberOfNodes){
            cout << "Such a graph does not exist.\n";
            cout << "Number of nodes:\n";
            cin >> numberOfNodes;
            cout << "Number of edges:\n";
            cin >> numberOfEdges;
        }

        Graph graph(numberOfNodes, numberOfEdges);
        graph.generateGraph(numberOfNodes, numberOfEdges);
        return graph;
    }
}

void printNumberOfNodes(Graph graph){
    cout << "There are " + to_string(graph.getNumberOfNodes()) + " nodes." << '\n';
}

void printNumbersOfEdges(Graph graph){
    cout << "There are " + to_string(graph.getNumberOfEdges()) + " edges." << '\n';
}

void checkExistenceOfEdge(Graph graph){
    int source, target;
    cout << "Source:";
    cin >> source;
    cout << "Target:";
    cin >> target;

    if(graph.isEdge(source, target))
        cout << "True\n";
    else
        cout << "False\n";
}

void printINDegreeOfNode(Graph graph){
    int node;
    cout << "Node:";
    cin >> node;
    cout << "The in-degree of " << node << " is " << graph.getInDegree(node) << '\n';
}

void printOutDegreeOfNode(Graph graph){
    int node;
    cout << "Node:";
    cin >> node;
    cout << "The out-degree of " << node << " is " << graph.getOutDegree(node) << '\n';
}

void printCostOfEdge(Graph graph){
    int source, target;
    cout << "Source:";
    cin >> source;
    cout << "Target:";
    cin >> target;

    if(graph.isEdge(source, target))
        cout << "The cost of the edge (" + to_string(source) + "," + to_string(target) + ") is " +
            to_string(graph.getEdgeCost(source, target)) << '\n';
    else
        cout << "No such edge.\n";
}

void writeGraph(Graph graph){
    string filePath;
    cout << "File path:";
    cin >> filePath;
    writeToFile(filePath, graph);
}

void printMenu(){
    cout << "1. Print number of nodes\n";
    cout << "2. Print number of edges\n";
    cout << "3. Check existence of certain edge\n";
    cout << "4. Get in degree of certain node\n";
    cout << "5. Get out degree of certain node\n";
    cout << "6. Get cost of given edge\n";
    cout << "7. Write graph to file\n";
    cout << "8. Add edge\n";
    cout << "9. Remove edge\n";
    cout << "10. Add node\n";
    cout << "11. Remove node\n";
    cout << "12. Print all edges\n";
    cout << "13. Print graph\n";
    cout << "14. Find connected components\n";
    cout << "0. Exit\n";
}

void addEdgeUI(Graph &graph){
    int source, target, cost;
    cout << "Source:";
    cin >> source;
    cout << "Target:";
    cin >> target;
    cout << "Cost:";
    cin >> cost;

    if(graph.isEdge(source, target))
        cout << "Edge already in graph.\n";
    else
        graph.addEdge(source, target, cost);
}

void removeEdgeUI(Graph &graph){
    int source, target;
    cout << "Source:";
    cin >> source;
    cout << "Target:";
    cin >> target;

    if(!graph.isEdge(source, target))
        cout << "No such edge in the graph.\n";
    else
        graph.removeEdge(source, target);
}

void addNodeUI(Graph &graph){
    int newNode = graph.getNumberOfNodes();
    graph.edges[newNode];
    graph.numberOfNodes++;
    cout << "Node " << newNode << " was added\n";
}

void removeNodeUI(Graph &graph){
    int node;
    cout << "Node:";
    cin >> node;
    graph.removeNode(node);
}

void connectedComponents(Graph &graph){
    graph.findConnectedComponents();
}

int main(){
    Graph graph = getGraph();
    while(true) {
        int option;
        printMenu();
        cin >> option;

        if (option == 0)
            exit(0);
        if (option == 1)
            printNumberOfNodes(graph);
        if (option == 2)
            printNumbersOfEdges(graph);
        if (option == 3)
            checkExistenceOfEdge(graph);
        if (option == 4)
            printINDegreeOfNode(graph);
        if (option == 5)
            printOutDegreeOfNode(graph);
        if (option == 6)
            printCostOfEdge(graph);
        if(option == 8)
            writeGraph(graph);
        if(option == 9)
            addEdgeUI(graph);
        if(option == 10)
            removeEdgeUI(graph);
        if(option == 11)
            addNodeUI(graph);
        if(option == 12)
            removeNodeUI(graph);
        if(option == 13)
            printGraph(graph);
        if(option == 14)
            connectedComponents(graph);
    }
}
