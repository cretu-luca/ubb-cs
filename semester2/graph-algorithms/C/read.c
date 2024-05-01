#include <stdio.h>
#include "read.h"

Graph *readGraph(char filePath[20]){
    FILE *file = fopen(filePath, "r");
    if(file == NULL){
        printf("Failed to open file.");
    }
    else {
        int numberOfVertices, numberOfEdges, source, target, cost;
        fscanf(file, "%d %d\n", &numberOfVertices, &numberOfEdges);
        Graph *graph = createGraph(numberOfVertices);
        for (int i = 0; i < numberOfEdges; i++) {
            fscanf(file, "%d %d %d", &source, &target, &cost);
            addEdgeToGraph(graph, source, target, cost);
        }
        fclose(file);
        return graph;
    }
}

void addEdgeToGraph(Graph *graph, int source, int target, int cost){
    int edgeAlreadyExists = 0;
    Edge *newEdge = createEdge(source, target, cost);

    if(graph->nodes[source].first_out == NULL) {
        graph->nodes[source].first_out = newEdge;
    } else {
        Edge * edgeParser = graph->nodes[source].first_out;
        while(edgeParser->next_source != NULL) {
            if (edgeParser->target == newEdge->target) {
                edgeAlreadyExists = 1;
                break;
            }
            edgeParser = edgeParser->next_source;
        }
        if (!edgeAlreadyExists && edgeParser->target != newEdge->target)
            edgeParser->next_source = newEdge;
    }

    edgeAlreadyExists = 0;
    if(graph->nodes[target].first_in == NULL) {
        graph->nodes[target].first_in = newEdge;
    } else {
        Edge * edgeParser = graph->nodes[target].first_in;
        while (edgeParser->next_target != NULL) {
            if (edgeParser->target == newEdge->source) {
                edgeAlreadyExists = 1;
                break;
            }
            edgeParser = edgeParser->next_target;
        }
        if (!edgeAlreadyExists && edgeParser->target != newEdge->source)
            edgeParser->next_target = newEdge;
    }
}


