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

void Graph::addEdge(int a, int b)
{
    a--;
    b--;
    
    adjacency[a][b] = 1;
    adjacency[b][a] = 1;
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

unsigned int Graph::numberOfComponents()
{
    int numberOfComponents = 0;
    
    while(adjacency.size() > 0)
    {
        removeComponent(0);
    }
    
    return numberOfComponents;
}