#include "graph.h"
#include <iostream>
using namespace std;

void menu() {
    cout << "1. Check if DAG + find shortest path.\n"
            "2. Reconstruct tree.\n"
            "3. Check if DAG + find number of paths.\n"
            "4. Check if DAG + find number of shortest paths.\n"
            ">";
}

void task1(Graph& graph) {
    if(graph.checkIfDAG()) {
        int source, destination;
        cout << "Graph is DAG.\n";

        cout << "Source:\n";
        cin >> source;

        cout << "Destination:\n";
        cin >> destination;

        cout << "Cost from " << source << " to " << destination << " is " << graph.Dijkstra(source, destination) << ".\n";
    } else {
        cout << "Graph is not DAG.\n";
    }
}

void task3(Graph& graph) {
    if(graph.checkIfDAG()) {
        int source, destination;
        cout << "Graph is DAG.\n";

        cout << "Source:\n";
        cin >> source;

        cout << "Destination:\n";
        cin >> destination;

        cout << "There are " << graph.numberOfPathsDP(source, destination) << " paths between " << source << " and "
             << destination << '\n';
    } else {
        cout << "Graph is not DAG.\n";
    }
}

void task4(Graph& graph) {
    if(graph.checkIfDAG()) {
        int source, destination;
        cout << "Graph is DAG.\n";

        cout << "Source:\n";
        cin >> source;
        cout << "Destination:\n";
        cin >> destination;

        std::pair<int, int> result = graph.numberOfLowestCostPaths(source, destination);

        cout << "There are " << result.first << " paths of cost " << result.second << " from " << source << " to "
            << destination << ".\n";
    }
}

int main() {
    Graph graph(R"(C:\\Users\\lucac\\uni\\ubb-cs\\semester2\\graph-algorithms\\C++\\v2\\DAG.txt)");
    int option;

    while(true) {
        menu();
        cin >> option;

        switch(option) {
            case 0:
                exit(0);
            case 1:
                task1(graph);
                break;
            case 3:
                task3(graph);
                break;
            case 4:
                task4(graph);
                break;
        }
    }

}