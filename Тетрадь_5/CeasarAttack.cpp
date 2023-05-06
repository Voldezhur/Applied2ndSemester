#include <iostream>
#include <map>
#include <algorithm>

std::string Sipher(std::string message, int key)
{
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

    return sipher;
}

std::string Desipher(std::string sipher)
{
    std::map<char, float> frequency;
    std::string frequencyAlphabet = "оеаинтсрвлкмдпуяыьгзбчйхжшюцщэфъё";
    float frequencyPercent[] = {10.983, 8.483, 7.998, 7.376, 6.7, 6.318, 6.473, 4.746, 4.533, 4.343, 3.486, 3.203, 2.977, 2.804, 2.615, 2.001, 1.898, 1.735, 1.687, 1.641, 1.592, 1.45, 1.208, 0.966, 0.94, 0.718, 0.638, 0.486, 0.361, 0.331, 0.267, 0.037, 0.013};

    for(char i : frequencyAlphabet)
    {
        frequency[frequencyAlphabet[i]] = frequencyPercent[i];
    }

    std::string message;

    int letters1[] = {};
    int letters2[] = {};

    

    for(int i = 0; i <= 32;  i++)
    {

    }
}


int main()
{
    std::string message;
    int key;

    std::cout << "Введите сообщение:\n";
    std::cin >> message;

    std::cout << "Введите ключ:\n";
    std::cin >> key;

    std::string sipher = Sipher(message, key);

    std::cout << '\n' << sipher;
}