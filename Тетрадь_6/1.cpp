// g++ -o 1 1.cpp Graph.cpp && ./1

// Что сделал: написал цикл поиска неприсоединенной вершины, ближайшей к одной из присоединенных
// Что не получилось: если соединить первую и вторую вершины, нет таких вершин, у которых ближайшими будут 1 или 2

#include "Graph.h"
#include <algorithm>

// Вывод массивов для проверки
void outputVectors(std::vector<int> connected, std::vector<int> unconnected)
{
    std::cout << '\n';
    
    for(int i : connected)
    {
        std::cout << i << ' ';
    }
    
    std::cout << '\n';
    
    for(int i : unconnected)
    {
        std::cout << i << ' ';
    }
    
    std::cout << '\n';
}

int main()
{
    std::vector<std::vector<float>> inputMatrix = {{0, 1.97, 21.6, 10.7, 22.3, 10.4}, {1.97, 0, 22.3, 11.4, 23, 11.1}, {21.6, 22.3, 0, 11.5, 5.2, 12}, {10.7, 1.4, 11.5, 0, 13.4, 0.68}, {22.3, 23, 5.2, 13.4, 0, 13.8}, {10.4, 11.1, 12, 0.68, 13.8, 0}};    
    std::vector<std::vector<float>> closestPaths = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};

    Graph A(inputMatrix, "adjacency");
    Graph B(closestPaths, "adjacency");

    A.showAdjacency('\t');

    // Алгоритм Прима
    // Создаем матрицы присоединенных и не присоединенных вершин (вершины хранятся по номерам вершин (индекс + 1))
    std::vector<int> unconnected;
    for(int i = 1; i < inputMatrix.size() + 1; i++)
    {
        unconnected.push_back(i);
    }

    std::vector<int> connected;

    int v = 1;
    connected.push_back(1);
    unconnected.erase(unconnected.begin());
    int u = A.findClosestVertex(v);
    connected.push_back(u);
    unconnected.erase(std::remove(unconnected.begin(), unconnected.end(), u), unconnected.end()); // erase-remove идиома

    // outputVectors(connected, unconnected);

    B.addEdge(v, u, A.getSideLength(v, u));

    // Цикл из тетради
    // while(unconnected.size() > 0)
    // {
        // Поиск ближайшей вершины к любой из присоединенных
        for(int i : unconnected)
        {
            // std::cout << "\ntest: " << i;
            int vertexToConnect = A.findClosestVertex(i);
            // std::cout << ' ' << vertexToConnect;
            // Если ближайшая вершина к проверяемой находится в списке приоединенных - присоединить
            if(std::find(connected.begin(), connected.end(), vertexToConnect) != connected.end())
            {
                B.addEdge(vertexToConnect, i, A.getSideLength(vertexToConnect, i));
                connected.push_back(i);
                unconnected.erase(std::remove(unconnected.begin(), unconnected.end(), i), unconnected.end()); // erase-remove идиома
                std::cout << "\nAdded connection\n";
            }
        }
    // }

    // outputVectors(connected, unconnected);

    std::cout << '\n';
    B.showAdjacency('\t');
}