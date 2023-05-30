#include "Graph.h"

Graph::Graph()
{
    adjacency = {{0, 0}, {0, 0}};
}

Graph::Graph(std::vector<std::vector<float>> inputMatrix, std::string matrixType)
{
    if(matrixType == "adjacency")
    {
        adjacency = inputMatrix;
    }   

    else if(matrixType == "incidence")
    {
        incidence = inputMatrix;

        // Перевод в матрицу смежности
    }

    else
    {
        std::cout << "\n*unknown input matrix type*\n";
        adjacency = {{0, 0}, {0, 0}};
    }
}

int Graph::size()
{
    return adjacency.size();
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

void Graph::showIncidence()
{
    for(std::vector<float> i : incidence)
    {
        for(float j : i)
        {
            std::cout << j << ' ';
        }

        std::cout << '\n';
    }
}

void Graph::showIncidence(char separator)
{
    for(std::vector<float> i : incidence)
    {
        for(float j : i)
        {
            std::cout << j << separator;
        }

        std::cout << '\n';
    }
}

void Graph::addEdge(int a, int b)
{
    a--;
    b--;
    
    adjacency[a][b] = 1;
    adjacency[b][a] = 1;
}

void Graph::addEdge(int a, int b, float value)
{
    a--;
    b--;
    
    adjacency[a][b] = value;
    adjacency[b][a] = value;
}

float Graph::getSideLength(int a, int b)
{
    a--;
    b--;

    return adjacency[a][b];
}

void Graph::removeEdge(int a, int b)
{
    a--;
    b--;

    adjacency[a][b] = 0;
    adjacency[b][a] = 0;
}

void Graph::removeVertex(int a)
{
    a--;

    // Удаление всех инцидентных ребер
    for(int i = 0; i < adjacency[a].size(); i++)
    {
        if(adjacency[a][i] != 0)
        {
            removeEdge(a + 1, i + 1);
        }
    }

    // Удаление вершины из матрицы смежности
    
    // Удаление столбика
    for(int i = 0; i < adjacency.size(); i++)
    {
        adjacency[i].erase(adjacency[i].begin() + a);
    }

    // Удаление строки
    adjacency.erase(adjacency.begin() + a);
}

void Graph::removeEmptyVertices()
{
    // Список пустых вершин
    std::vector<int> verticesToRemove;

    // Нахождение пустых вершин
    for(int i = 0; i < adjacency.size(); i++)
    {
        bool empty = true;
        // Проверка на пустоту
        for(float j : adjacency[i])
        {
            if(j != 0)
            {
                empty = false;
                break;
            }
        }

        if(empty)
        {
            verticesToRemove.push_back(i + 1);
            // i + 1 т.к. i это индекс (на 1 меньше)
        }
    }

    // Вывод удаляемых вершин
    // for(int i : verticesToRemove)
    // {
    //     std::cout << i << ' ';
    // }

    int i = 0;
    // Удаление пустых вершин
    while(verticesToRemove.size() > 0)
    {
        // Удаление вершины из графа
        removeVertex(verticesToRemove[i]);

        // Удаление вершины из списка удаляемых вершин
        verticesToRemove.erase(verticesToRemove.begin());

        // Снижение индексов вершин на 1 (т.к. они сдвинулись влево на 1 после удаления вершины)
        for(int i = 0; i < verticesToRemove.size(); i++)
        {
            verticesToRemove[i]--;
        }
    }
}

void Graph::removeComponent(int a)
{
    a--;

    // Создание копии матрицы смежности    
    std::vector<std::vector<float>> tempAdjacency = adjacency;

    // Цикличное удаление всех ребер в компоненте
    for(int i = 0; i < tempAdjacency[a].size(); i++)
    {
        if(tempAdjacency[a][i] != 0)
        {
            removeEdge(a + 1, i + 1);
        }
    }

    // Удаление всех вершин компоненты (Нулевых строк)
    removeEmptyVertices();
}

int Graph::findClosestVertex(int a)
{
    a--;

    int minimum = 0;
    int closestIndex = 0;

    for(int i = 0; i < adjacency[a].size(); i++)
    {
        if(i != a && adjacency[a][i] != 0)
        {
            if(minimum == 0 || adjacency[a][i] < minimum)
            {
                minimum = adjacency[a][i];
                closestIndex = i;
            }
        }
    }

    return closestIndex + 1;
}

std::vector<int> Graph::getEmptyVertices()
{
    // Список пустых вершин
    std::vector<int> emptyVertices;

    // Нахождение пустых вершин
    for(int i = 0; i < adjacency.size(); i++)
    {
        bool empty = true;
        // Проверка на пустоту
        for(float j : adjacency[i])
        {
            if(j != 0)
            {
                empty = false;
                break;
            }
        }

        if(empty)
        {
            emptyVertices.push_back(i + 1);
            // i + 1 т.к. i это индекс (на 1 меньше)
        }
    }

    return emptyVertices;
}

unsigned int Graph::numberOfComponents()
{
    int numberOfComponents = 0;

    // Пока не пустая матрица - удаляем компоненты
    while(adjacency.size() > 0)
    {
        removeComponent(1);

        numberOfComponents++;
    }
    
    return numberOfComponents;
}
