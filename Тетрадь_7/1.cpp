// g++ -o 1 1.cpp Graph.cpp && ./1

#include "Graph.h"
#include <iostream>

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{0, 3, 4, 0, 0, 0, 0}, {3, 0, 0, 6, 0, 0, 0}, {4, 0, 0, 7, 0, 1, 0}, {0, 6, 7, 0, 8, 0, 0}, {0, 0, 0, 8, 0, 2, 5}, {0, 0, 1, 0, 2, 0, 2}, {0, 0, 0, 0, 5, 2, 0}};

    Graph A(inputMatrix, "adjacency");

    A.showLength();

    A.Dijkstra(1);
}