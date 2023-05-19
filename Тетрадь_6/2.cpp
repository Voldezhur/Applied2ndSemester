// g++ -o 2 2.cpp Graph.cpp && ./2

#include "Graph.h"

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{0, 0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}};

    Graph A(inputMatrix, "adjacency");

    A.showAdjacency();

    // Вывод количества компонент
    std::cout << A.numberOfComponents();

    // // Удаление компоненты, содержащей первую вершину
    // A.removeComponent(1);

    // std::cout << '\n' << A.size() << '\n';
    // A.showAdjacency();

    // // Удаление компоненты, содержащей первую вершину
    // A.removeComponent(1);

    // std::cout << '\n' << A.size() << '\n';
    // A.showAdjacency();
}