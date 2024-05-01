#pragma once

typedef struct Edge{
    int source, target, cost;
    struct Edge *next_source;
    struct Edge *next_target;
} Edge;

typedef struct {
    Edge *first_in;
    Edge *first_out;
} Node;

typedef struct {
    int numberOfNodes;
    Node *nodes;
} Graph;

Edge *createEdge(int source, int target, int cost);
Graph *createGraph(int numberOfVertices);
void printGraph(Graph *graph);
void copyGraph(Graph *graph);
int getNumberOfNodes(Graph *graph);
int isEdge(Graph *graph, int vertex1, int vertex2);
int getCost(Graph *graph, int vertex1, int vertex2);
