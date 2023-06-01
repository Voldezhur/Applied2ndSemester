#include <iostream>
#include <tuple>

// РАЕ с интернета
std::tuple<int, int, int> extended_gcd(int a, int b)
{
    if (a == 0) {
        return std::make_tuple(b, 0, 1);
    }
 
    int gcd, x, y;
 
    // распаковываем возвращаемый функцией кортеж в переменные
    std::tie(gcd, x, y) = extended_gcd(b % a, a);
 
    return std::make_tuple(gcd, (y - (b/a) * x), x);
}

// Нахождение обратного числа по модулю
int reverse(int a, int b)
{
    std::tuple <int, int, int> values = extended_gcd(a, b);

    return std::get<2>(values);
}

int main()
{
    int a = 18, b = 30;

    std::cout << reverse(a, b);
}