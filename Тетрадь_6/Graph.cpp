#include "Graph.h"

Graph::Graph()
{
    numberOfNodes = 2;
    adjacency = {{0, 0}, {0, 0}};
}

Graph::Graph(std::vector<std::vector<float>> inputMatrix, std::string matrixType)
{
    if(matrixType == "adjacency")
    {
        adjacency = inputMatrix;
        numberOfNodes = adjacency.size();
    }   

    else if(matrixType == "incidence")
    {

    }

    else
    {
        std::cout << "\n*unknown input matrix type*\n";
    }
}

void Graph::showAdjacency()
{
    for(std::vector<float> i : adjacency)
    {
        for(float j : i)
        {
            std::cout << j << ' ';
        }

        std::cout << '\n';
    }
}

void Graph::showAdjacency(char separator)
{
    for(std::vector<float> i : adjacency)
    {
        for(float j : i)
        {
            std::cout << j << separator;
        }

        std::cout << '\n';
    }
}