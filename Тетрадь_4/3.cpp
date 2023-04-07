#include <iostream>
#include <vector>


// Класс хеш-таблиц
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

    // Добавить числового значения
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

    // Добавить символьного значения
    void add(char _val)
    {
        int index = int(_val) % values.size();
        int val = int(_val);

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
                
                if(i >= values.size())
                {
                    i = 0;
                }
            }
        }
    }

    void addToCounter(int index)
    {
        values[index]++;
    }

    // Поиск по числовому значению
    int find(int val)
    {
        for(int i = 0; i < values.size(); i++)
        {
            if(values[i] == val)
            {
                return i;
            }
        }

        return 0;
    }

    // Поиск по символьному значению
    int find(char _val)
    {
        for(int i = 0; i < values.size(); i++)
        {
            if(values[i] == int(_val))
            {
                return i;
            }
        }

        return 0;
    }

    // Вывести числовые значения
    void show()
    {
        for(int i = 0; i < values.size(); i++)
        {
            std::cout << i << " - ";

            std::cout << values[i] << '\n';
        }
    }

    // Вывести значения в виде символов
    void showChars()
    {
        for(int i = 0; i < values.size(); i++)
        {
            std::cout << i << " - ";

            std::cout << char(values[i]) << '\n';
        }
    }
};


int main()
{
    std::string str = "aaaaabba";

    int size = str.size();

    hashMap chars(size);
    hashMap counts(size);

    for(int i = 0; i < size; i++)
    {
        chars.add(str[i]);
        counts.addToCounter(chars.find(str[i]));
    }

    chars.showChars();
    std::cout << '\n';
    counts.show();
}