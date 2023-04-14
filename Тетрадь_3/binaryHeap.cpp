#include <iostream>
#include <vector>

class Heap
{
public:
    std::vector<int> H;

    Heap(std::vector<int> _H)
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
        if(2*i + 1 < H.size() && H[2*i + 1] > H[i])
        {
            int temp = H[2*i + 1];
            H[2*i + 1] = H[i];
            H[i] = temp;

            pushDown(2*i + 1);
        }

        // сравнение правого дочернего узла
        if(2*i + 2 < H.size() && H[2*i + 2] > H[i])
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
            if(H[(i - 1) / 2] < H[i])
            {
                int temp = H[(i - 1) / 2];
                H[(i - 1) / 2] = H[i];
                H[i] = temp;

                pushDown((i - 1) / 2);
                pushDown(i);
            }
        }
    }
};


int main()
{
    std::vector<int> nums = {16, 1, 2, 8, 7, 4, 14, 10, 9, 3};

    Heap A(nums);
    A.show();

    A.balance();
    A.show();
}