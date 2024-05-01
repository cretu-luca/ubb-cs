#include "main.h"
#include "read.h"

int main(int argc, char **argv){
    Graph *graph = readGraph(argv[1]);
    printGraph(graph);
    return 0;
}