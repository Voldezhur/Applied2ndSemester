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
            if(j != 0)
            {
                std::cout << 1 << ' ';
            }

            else
            {
                std::cout << 0 << ' ';
            }
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
            if(j != 0)
            {
                std::cout << 1 << separator;
            }

            else
            {
                std::cout << 0 << separator;
            }
        }

        std::cout << '\n';
    }
}

void Graph::showLength()
{
    for(std::vector<float> i : adjacency)
    {
        for(float j : i)
        {
            if(j != 0)
            {
                std::cout << j << ' ';
            }

            else
            {
                std::cout << ". ";
            }
        }

        std::cout << '\n';
    }
}

void Graph::showLength(char separator)
{
    for(std::vector<float> i : adjacency)
    {
        for(float j : i)
        {
            if(j != 0)
            {
                std::cout << j << separator;
            }

            else
            {
                std::cout << '.' << separator;
            }
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

unsigned int Graph::numberOfComponents()
{
    int numberOfComponents = 0;
    
    while(adjacency.size() > 0)
    {
        removeComponent(0);
    }
    
    return numberOfComponents;
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

// Вспомогательная функция для алгоритма Дейкстры
// bool hasUnvisited(std::vector<int> paths)
// {
//     for(int i : paths)
//     {
//         if(i == 10000)
//         {
//             return true;
//         }
//     }
//
//     return false;
// }

void Graph::Dijkstra(int a)
{    
    a--;
    // С этого момента вершины не по номеру, а по индексу (номер - 1)

    // Метки всех вершин равны 10000
    std::vector<int> marks;

    for(int i = 0; i < size(); i++)
    {
        marks.push_back(10000);
    }

    // Путь до стартовой вершины равен 0
    marks[a] = 0;
    // Список посещенных вершин
    std::vector<int> visited;

    // Проверяемая на данный момент вершина
    int currentVertex = a;

    // Пока не побывали во всех вершинах
    while(visited.size() < adjacency.size())
    {   
        // Проверка соседних вершин
        for(int i = 0; i < adjacency[currentVertex].size(); i++)
        {
            // Если есть путь в вершину
            if(adjacency[currentVertex][i] != 0)
            {
                // Метка вершины с учетом пройденного до нее пути
                float path = marks[currentVertex] + adjacency[currentVertex][i];

                // Если новая метка меньше старой - замена
                if(path < marks[i])
                {
                    marks[i] = path;
                }
            }
        }

        // Добавление вершины в список посещенных
        visited.push_back(currentVertex);
        // Переход к следующей вершине
        currentVertex++;
    }

    // Вывод меток
    for(int i : marks)
    {
        std::cout << i << ", ";
    }
}
