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
        char letter;
        
        if(message[i] + key <= 122)
        {
            letter = message[i] + key;
        }   

        else
        {
            letter = message[i] + key - 26;
        }

        sipher += letter;
    }

    std::cout << '\n' << sipher;
}