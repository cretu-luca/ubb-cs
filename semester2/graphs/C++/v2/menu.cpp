#pragma once
#include "graph.h"

Graph getGraph(){
    std::cout << "1. Read graph from file\n";
    std::cout << "2. Generate random graph\n";

    int option;
    std::cin >> option;
    if(option == 1){
        std::string filePath;
        std::cout << "File path:\n";
        std::cin >> filePath;

        Graph graph(filePath);
        return graph;
    }
    else {
        int numberOfNodes, numberOfEdges;
        std::cout << "Number of nodes:\n";
        std::cin >> numberOfNodes;
        std::cout << "Number of edges:\n";
        std::cin >> numberOfEdges;

        while(numberOfEdges > numberOfNodes * numberOfNodes){
            std::cout << "Such a graph does not exist.\n";
            std::cout << "Number of nodes:\n";
            std::cin >> numberOfNodes;
            std::cout << "Number of edges:\n";
            std::cin >> numberOfEdges;
        }

        Graph graph(numberOfNodes, numberOfEdges);
        return graph;
    }
}

void writeGraph(Graph& graph){
    std::string filePath;
    std::cout << "File path:";
    std::cin >> filePath;
    graph.writeToFile(filePath, graph);
}

void menu() {
    /*
    std::cout << "1. Number of edges\n"
                 "2. Number of nodes\n"
                 "3. Check if edge\n"
                 "4. Get in degree\n"
                 "5. Get out degree\n"
                 "6. Get edge cost\n"
                 "7. Set edge cost\n"
                 "8. Add edge\n"
                 "9. Remove edge\n"
                 "10. Add node\n"
                 "11. Remove node\n"
                 "12. Print graph\n"
                 "13. Write graph\n"
                 "14. Connected components\n"
                 "15. SSC\n"
                 "16. Biconnected components\n";
    */
    std::cout << "17. Find path with minimal cost (Floyd-Warshall)\n"
                 "18. Find number of paths (Backtracking)\n"
                 "19. Find number of costs with minimal cost (F-W + BT)\n"
                 "20. Solve Bridge and Torch problem\n"
                 ">";
}

void isEdgeUI(Graph& graph){
    int node1, node2;
    std::cout << "Node1: \n";
    std::cin >> node1;

    std::cout << "Node2: \n";
    std::cin >> node2;

    if(graph.isEdge(node1, node2))
        std::cout << "True\n";
    else
        std::cout << "False\n";
}

void getInDegreeUI(Graph& graph){
    int node;
    std::cout << "Node: \n";
    std::cin >> node;

    if(graph.isNode(node))
        std::cout << "Node does not exist.\n";
    else
        std::cout << "In degree: " << graph.getInDegree(node) << std::endl;
}

void getOutDegreeUI(Graph& graph){
    int node;
    std::cout << "Node: \n";
    std::cin >> node;

    if(graph.isNode(node))
        std::cout << "Node does not exist.\n";
    else
        std::cout << "Out degree: " << graph.getOutDegree(node) << std::endl;
}

void getEdgeCostUI(Graph& graph){
    int node1, node2;
    std::cout << "Node1: \n";
    std::cin >> node1;

    std::cout << "Node2: \n";
    std::cin >> node2;

    if(graph.isEdge(node1, node2))
        std::cout << "Edge does not exist.\n";
    else
        std::cout << "Cost: " << graph.getEdgeCost(node1, node2) << std::endl;
}

void setEdgeCostUI(Graph& graph){
    int node1, node2, cost;
    std::cout << "Node1: \n";
    std::cin >> node1;

    std::cout << "Node2: \n";
    std::cin >> node2;

    std::cout << "Cost: \n";
    std::cin >> cost;

    if(!graph.isEdge(node1, node2))
        std::cout << "Edge does not exist.\n";
    else {
        graph.setEdgeCost(node1, node2, cost);
        std::cout << "Edge cost set.\n";
    }
}

void addEdgeUI(Graph& graph){
    int node1, node2, cost;
    std::cout << "Node1: \n";
    std::cin >> node1;

    std::cout << "Node2: \n";
    std::cin >> node2;

    std::cout << "Cost: \n";
    std::cin >> cost;

    if(graph.isEdge(node1, node2))
        std::cout << "Edge already in graph.\n";
    else {
        graph.addEdge(node1, node2, cost);
        std::cout << "Edge added.\n";
    }
}

void removeEdgeUI(Graph& graph){
    int node1, node2;
    std::cout << "Node1: \n";
    std::cin >> node1;

    std::cout << "Node2: \n";
    std::cin >> node2;

    if(!graph.isEdge(node1, node2))
        std::cout << "Edge does not exist.\n";
    else {
        graph.removeEdge(node1, node2);
        std::cout << "Edge removed.\n";
    }
}

void addNodeUI(Graph& graph){
    graph.addNode();
}

void removeNodeUI(Graph& graph){
    int node;
    std::cout << "Node: \n";
    std::cin >> node;

    if(!graph.isNode(node))
        std::cout << "Node does not exist.\n";
    else {
        graph.removeNode(node);
        std::cout << "Node removed.\n";
    }
}

void connectedComponentsUI(Graph& graph) {
    graph.findConnectedComponents();
}

void SSCUI(Graph& graph){
    graph.Kosaraju();
}

void findBiconnected(Graph& graph) {
    graph.Tarjan();
}

void findShortestPath(Graph& graph) {
    int node1, node2;
    std::cout << "Source:";
    std::cin >> node1;

    std::cout << "Destination:";
    std::cin >> node2;

    /*
    int cost = graph.Floyd_Warshall(node1, node2);
    if(cost == 1e9)
        std::cout << "There is no path between " << node1 << " and " << node2 << '\n';
    else
        std::cout << "Distance from " << node1 << " to " << node2 << " is " << cost << "\n\n";
    */
    std::pair<int, std::vector<int>> solution = graph.getFloydWarshallPath(node1, node2, graph);

    std::cout << "The time needed is " << solution.first << '\n';
    std::cout << "The solution is:\n";

    for(auto node: solution.second)
        std::cout << node << " ";

    std::cout << '\n';
}

void countAllPaths(Graph& graph) {
    int source, destination;
    std::cout << "Source:";
    std::cin >> source;

    std::cout << "Destination:";
    std::cin >> destination;

    graph.numberOfPaths(source, destination);
}

void countAllMinimumPaths(Graph& graph) {
    int source, destination;
    std::cout << "Source:";
    std::cin >> source;

    std::cout << "Destination:";
    std::cin >> destination;

    graph.numberOfMinimalCosts(source, destination);
}

void solveBridgeTorchUI(Graph& graph) {
    std::string path;
    std::cout << "Path:";
    std::cin >> path;

    std::ifstream fin(path);

    int numberOfPeople, time;
    fin >> numberOfPeople;
    std::vector<int> timeNeeded (numberOfPeople, 0);
    for(int i = 0; i < numberOfPeople; i++) {
        fin >> time;
        timeNeeded[i] = time;
    }

    graph.solveBridgeTorch(numberOfPeople, timeNeeded);
}

int main(){
    int option;
    Graph graph = getGraph();

    while(true){
        menu();
        std::cin >> option;

        switch(option) {
            case 0:
                exit(0);
            case 1:
                std::cout << "Edges: " << graph.getNumberOfEdges() << std::endl;
                break;
            case 2:
                std::cout << "Nodes: " << graph.getNumberOfNodes() << std::endl;
                break;
            case 3:
                isEdgeUI(graph);
                break;
            case 4:
                getInDegreeUI(graph);
                break;
            case 5:
                getOutDegreeUI(graph);
                break;
            case 6:
                getEdgeCostUI(graph);
                break;
            case 7:
                setEdgeCostUI(graph);
                break;
            case 8:
                addEdgeUI(graph);
                break;
            case 9:
                removeEdgeUI(graph);
                break;
            case 10:
                addNodeUI(graph);
                break;
            case 11:
                removeNodeUI(graph);
                break;
            case 12:
                graph.printGraph();
                break;
            case 13:
                writeGraph(graph);
                break;
            case 14:
                connectedComponentsUI(graph);
                break;
            case 15:
                SSCUI(graph);
                break;
            case 16:
                findBiconnected(graph);
                break;
            case 17:
                findShortestPath(graph);
                break;
            case 18:
                countAllPaths(graph);
                break;
            case 19:
                countAllMinimumPaths(graph);
                break;
            case 20:
                solveBridgeTorchUI(graph);
                break;
        }
    }
}