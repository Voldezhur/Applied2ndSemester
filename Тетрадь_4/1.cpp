#include <iostream>
#include <vector>

class hashMap
{
    std::vector<int> values;

public:
    
    hashMap()
    {
        values.resize(7);
    }
    hashMap(int n)
    {
        values.resize(n);
    }

    void add(int val)
    {
        int index = val % values.size();
        
        // Если ячейка пустая, или то же значение
        if(values[index] == 0)
        {
            values[index] = val;
        }

        // Если ячейка занята, искать свободную
        else if(values[index] != val)
        {
            int i = (index + 1) % values.size();

            for(int k = 0; k < values.size(); k++)
            {
                if(values[i] == 0 or values[i] == val)
                {
                    values[i] = val;
                    break;
                }

                i++;
            }
        }
    }

    void show()
    {
        for(auto i: values)
        {
            std::cout << i;

            if(i != values.back())
            {
                std::cout << ", ";
            }
        }
    }
};


int main()
{
    hashMap A;

    A.add(86);
    A.add(90);
    A.add(27);
    A.add(29);
    A.add(38);
    A.add(30);
    A.add(40);

    A.show();
}