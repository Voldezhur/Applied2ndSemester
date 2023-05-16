// g++ -o 1 1.cpp Graph.cpp && ./1

#include "Graph.h"

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{0, 1.97, 21.6, 10.7, 22.3, 10.4}, {1.97, 0, 22.3, 11.4, 23, 11.1}, {21.6, 22.3, 0, 11.5, 5.2, 12}, {10.7, 1.4, 11.5, 0, 13.4, 0.68}, {22.3, 23, 5.2, 13.4, 0, 13.8}, {10.4, 11.1, 12, 0.68, 13.8, 0}};    

    Graph G(inputMatrix, "adjacency");

    G.showAdjacency('\t');
}