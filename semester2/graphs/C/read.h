#pragma once
#include "graph.h"

Graph *readGraph(char filePath[20]);
void addEdgeToGraph(Graph *graph, int source, int target, int cost);