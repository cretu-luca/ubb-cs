#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Edge *createEdge(int source, int target, int cost){
    Edge * edge = malloc(sizeof(Edge));
    edge->source = source;
    edge->target = target;
    edge->cost = cost;
    edge->next_source = NULL;
    edge->next_target = NULL;

    return edge;
}

Graph *createGraph(int numberOfVertices){
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->numberOfNodes = numberOfVertices;
    graph->nodes = (Node *) malloc(sizeof(Node) *numberOfVertices);

    for(int i = 0; i < numberOfVertices; i++){
        graph->nodes[i].first_in = NULL;
        graph->nodes[i].first_out = NULL;
    }
    return graph;
}

void printGraph(Graph *graph) {
    if (graph == NULL) {
        printf("Graph is null.\n");
        return;
    }

    printf("Graph with %d vertices:\n", graph->numberOfNodes);
    for (int i = 0; i < graph->numberOfNodes; i++) {
        Node node = graph->nodes[i];
        printf("Vertex %d:\n", i);

        printf("  Outgoing edges:\n");
        for (Edge *e = node.first_out; e != NULL; e = e->next_source) {
            printf("    to %d, cost: %d\n", e->target, e->cost);
        }

        printf("  Incoming edges:\n");
        for (Edge *e = node.first_in; e != NULL; e = e->next_target) {
            printf("    from %d, cost: %d\n", e->source, e->cost);
        }
    }
}

int getNumberOfNodes(Graph *graph){
    return graph->numberOfNodes;
}

int isEdge(Graph *graph, int vertex1, int vertex2){
    for(Edge *iter = graph->nodes[vertex1].first_out; iter != NULL; iter = iter->next_source)
        if(iter->target == vertex2)
             return 1;

    return 0;
}





