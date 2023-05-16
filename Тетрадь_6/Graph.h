#include <iostream>
#include <vector>
#include <string>

class Graph
{
    int numberOfNodes;
    std::vector<std::vector<float>> adjacency;

public:

    Graph();

    Graph(std::vector<std::vector<float>> _adjacency, std::string matrixType);

    void showAdjacency();
    void showAdjacency(char separator);
};