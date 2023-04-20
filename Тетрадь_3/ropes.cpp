#include <iostream>
#include <vector>

class minHeap
{
public:
    std::vector<int> H;

    minHeap(std::vector<int> _H)
    {
        H = _H;
    }

    void show()
    {
        std::cout << '[';

        for(auto i: H)
        {
            std::cout << i << ", ";
        }

        std::cout << "]\n";
    }

    // "Протискивание" элемента вниз
    void pushDown(int i)
    {
        // сравнение левого дочернего узла
        if(2*i + 1 < H.size() && H[2*i + 1] < H[i])
        {
            int temp = H[2*i + 1];
            H[2*i + 1] = H[i];
            H[i] = temp;

            pushDown(2*i + 1);
        }

        // сравнение правого дочернего узла
        if(2*i + 2 < H.size() && H[2*i + 2] < H[i])
        {
            int temp = H[2*i + 2];
            H[2*i + 2] = H[i];
            H[i] = temp;

            pushDown(2*i + 2);
        }
    }

    // Сравнение каждого элемента с родительским
    void balance()
    {
        for(int i = H.size() - 1; i >= 0; i--)
        {
            if(H[(i - 1) / 2] > H[i])
            {
                int temp = H[(i - 1) / 2];
                H[(i - 1) / 2] = H[i];
                H[i] = temp;

                pushDown((i - 1) / 2);
                pushDown(i);
            }
        }
    }

    // Вывод и удаление максимума
    int popMin()
    {
        int min = H[0];
        
        // Удаляем вершину перемещаем последний элемент в вершину
        int temp = H[0];
        H[0] = H.back();
        H.back() = temp;
        H.pop_back();

        H.shrink_to_fit();

        // "Протискиваем" вершину вниз
        pushDown(0);

        return min;
    }

    void add(int val)
    {
        H.emplace(H.begin(), val);
        pushDown(0);
    }
};

int main()
{
    std::vector<int> nums = {5, 4, 2, 8};

    minHeap ropes(nums);
    ropes.balance();

    int effort = 0;

    while(ropes.H.size() > 1)
    {
        ropes.show();

        int tempSum = ropes.popMin() + ropes.popMin();
        effort += tempSum;

        ropes.add(tempSum);
    }

    std::cout << "\nФинальные затраты: " << effort << '\n';
}