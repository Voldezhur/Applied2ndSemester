// g++ -o 2 2.cpp Graph.cpp && ./2

#include "Graph.h"

int main()
{
    // Созданиие матрицы, заданной матрицей смежности
    std::vector<std::vector<float>> inputMatrix = {{0, 0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}};

    Graph A(inputMatrix, "adjacency");

    A.showAdjacency();

    // Вывод количества компонент
    std::cout << "\nКоличество компонент связности: " << A.numberOfComponents() << '\n';

    
    // Создание матрицы, заданной матрицей инцидентности
    inputMatrix = {{1, 1, 1, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}, {0, 0, 1, 0, 0}, {0, 1, 0, 0, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 1, 0}};

    Graph B(inputMatrix, "incidence");

    B.showIncidence();
}