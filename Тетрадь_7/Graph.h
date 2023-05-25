#include <iostream>
#include <vector>
#include <string>

class Graph
{
    int numberOfNodes;
    std::vector<std::vector<float>> adjacency;

public:
    // Конструктор по умолчанию
    Graph();

    // Конструктор по матрице (Смежности или инцидентности)
    Graph(std::vector<std::vector<float>> inputMatrix, std::string matrixType);

    // Вернуть размер графа
    int size();

    // Вывести матрицу смежности
    void showAdjacency();
    // Перегрузка для ввода собственного разделителя столбцов
    void showAdjacency(char separator); 

    // Вывести взвешенную матрицу смежности
    void showLength();
    // Перегрузка для ввода собственного разделителя столбцов
    void showLength(char separator); 

    // Добавить ребро между двумя вершинами
    void addEdge(int a, int b);
    // Перегрузка для взвешенных матриц
    void addEdge(int a, int b, float value);

    // Вернуть длину ребра между вершинами
    float getSideLength(int a, int b);

    // Удалить ребро меду двумя вершинами
    void removeEdge(int a, int b);

    // Удалить ребро из графа и из матриц
    void removeVertex(int a);

    // Удалить пустые вершины (нулевые строки)
    void removeEmptyVertices();

    // Удалить компоненту связности по одной из вершин
    void removeComponent(int a);

    // Вернуть количество компонент связности (Алгоритм связности)
    unsigned int numberOfComponents();

    // Вернуть номер ближайшей вершины
    int findClosestVertex(int a);

    // Вернуть список пустых вершин
    std::vector<int> getEmptyVertices();

    // Алгоритм Дейкстры по номеру вершины
    void Dijkstra(int a);
};