#include <iostream>
#include <tuple>

// Функция наибольшего общего делителя
int nod(int a, int b){
    while(a != b){
        if(a > b){
            a -= b;
        }
        
        else{
            b -= a;
        }
    }

    return a;
}

// Расширенный алгоритм Евклида
void gcdex(int a, int b, int arr[])
{
    int d = nod(a, b);
    arr[0] = d;

    if(b == 0)
    {
        d = a;
        arr[0] = d;

        arr[1] = 1;
        arr[2] = 0;
    }   

    else
    {
        int arr2[3];
        gcdex(b, a%b, arr2);
    }
}

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

int main()
{
    int a = 18;
    int b = 30;

    std::tuple<int, int, int> values = extended_gcd(a, b);

    std::cout << "НОД: " << std::get<0>(values) << '\n';
    std::cout << '(' << std::get<1>(values) << '*' << a << ")+(" << std::get<2>(values) << '*' << b << ") = " << std::get<0>(values);
}