#include <iostream>


int main()
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "goydsipeluavcrjwxznhbqftmk";

    std::string message;

    std::cout << "Введите сообщение:\n";
    std::cin >> message;

    std::string sipher;

    for(int i = 0; i < message.length(); i++)
    {
        sipher += key[alphabet.find(message[i])];
    }

    std::cout << sipher;
}