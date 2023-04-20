#include <iostream>
#include <vector>

class maxHeap
{
public:
    std::vector<int> H;

    maxHeap()
    {
        H = {};
    }

    maxHeap(std::vector<int> _H)
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

    // Вывод максимума
    int max()
    {
        return H[0];
    }

    // Вывод и удаление максимума
    int popMax()
    {
        int max = H[0];
        
        // Удаляем вершину перемещаем последний элемент в вершину
        int temp = H[0];
        H[0] = H.back();
        H.back() = temp;
        H.pop_back();

        H.shrink_to_fit();

        // "Протискиваем" вершину вниз
        pushDown(0);

        return max;
    }

    // Вставка элемента
    void insert(int val)
    {
        int i, parent;
        i = H.size() - 1;

        H[i] = val;
        parent = (i - 1) / 2;

        while(parent >= 0 && i > 0)
        {
            if(H[i] > H[parent])
            {
                int temp = H[i];
                H[i] = H[parent];
                H[parent] = temp;
            }
            
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    // Слияние кучи с другой
    void merge(maxHeap B)    
    {
        std::vector<int> temp;
        
        // Конкатенация векторов
        temp.reserve(H.size() + B.H.size());
        temp.insert(temp.end(), H.begin(), H.end());
        temp.insert(temp.end(), B.H.begin(), B.H.end());

        H = temp;

        balance();
    }
};

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
};


int main()
{
    std::vector<int> nums = {16, 1, 2, 8, 7, 4, 14, 10, 9, 3};

    maxHeap A(nums);
    A.balance();
    A.show();

    minHeap B(nums);
    B.balance();
    B.show();

    std::cout << "\nМаксимальное значение первой кучи: " << A.popMax() << '\n';
    
    std::cout << "\nУдаление максимального элемента из первой кучи\n";
    A.show();

    std::cout << "\nВставка элемента '100' в первую кучу\n";
    A.insert(100);
    A.show();

    std::cout << "\nСоздание новой максимальной кучи\n";
    std::vector<int> nums2 = {5, 6, 11, 12, 13, 15};
    
    maxHeap C(nums2);
    C.balance();
    C.show();

    std::cout << "\nСлияние первой кучи с новой\n";
    
    A.merge(C);
    A.show();
}