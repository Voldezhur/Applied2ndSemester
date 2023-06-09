// g++ -o 3 3.cpp Graph.cpp && ./3

#include "Graph.h"

int main()
{
    // Созданиие матрицы, заданной матрицей смежности
    std::vector<std::vector<float>> inputMatrix = {{0, 7, 0, 1, 5, 3, 0}, {7, 0, 1, 0, 0, 0, 9}, {0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 4, 0, 0}, {5, 0, 0, 4, 0, 0, 2}, {3, 0, 0, 0, 0, 0, 0}, {0, 9, 0, 0, 2, 0, 0}};

    Graph A(inputMatrix, "adjacency");

    A.showAdjacency();

    
}