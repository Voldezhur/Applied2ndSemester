#include <iostream>


int main()
{
    std::string message;
    int key;

    std::cout << "Введите сообщение:\n";
    std::cin >> message;

    std::cout << "Введите ключ:\n";
    std::cin >> key;

    std::string sipher;

    for(int i = 0; i < message.length(); i++)
    {
        sipher += (message[i] + key);
    }

    std::cout << '\n' << sipher;
}