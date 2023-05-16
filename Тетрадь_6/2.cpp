// g++ -o 2 2.cpp Graph.cpp && ./2

#include "Graph.h"

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{2, 0, 0, 1, 1, 1, 0}, {0, 2, 1, 0, 0, 0, 0}, {0, 1, 2, 1, 1, 1, 1}, {1, 0, 1, 2, 0, 0, 1}, {1, 0, 1, 0, 0, 0, 1}, {1, 0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 2}};

    Graph A(inputMatrix, "adjacency");

    A.showAdjacency();
}