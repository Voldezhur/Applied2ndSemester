// g++ -o testing testing.cpp Graph.cpp && ./testing

#include "Graph.h"

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{0, 0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}};

    Graph A(inputMatrix, "adjacency");

    A.showAdjacency();

    // // Вывод количества компонент
    // std::cout << A.numberOfComponents();

    // Удаление компоненты, содержащей первую вершину
    A.removeComponent(1);

    std::cout << '\n' << A.size() << '\n';
    A.showAdjacency();

    // Удаление компоненты, содержащей первую вершину
    A.removeComponent(1);

    std::cout << '\n' << A.size() << '\n';
    A.showAdjacency();

    // // Удаление пустых вершин
    // A.removeEmptyVertices();

    // std::cout << '\n';
    // A.showAdjacency();

    // // Добавление ребра 2 - 5
    // A.addEdge(2, 5);

    // std::cout << '\n';
    // A.showAdjacency();

    // // Удаление ребра 1 - 4
    // A.removeEdge(1, 4);

    // std::cout << '\n';
    // A.showAdjacency();

    // // Удаление вершины 1
    // A.removeVertex(1);

    // std::cout << '\n';
    // A.showAdjacency();
}