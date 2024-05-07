#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

Graph readFromFile(const string& filePath);
void writeToFile(const string& filePath, const Graph& graph);