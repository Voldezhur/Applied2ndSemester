#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

// ===== Большие числа из первого семестра

// Генератор чисел фон Неймана длины x без проверки на первый ноль
short fonNeyman(unsigned int x){
    if(x < 8){
        // seed
        static double A = 8691454555;

        // get the number from which to get the random value
        std::string B = std::to_string(A*A);
        std::string num = "";

        // index to start building randomized value from
        int n = 10;
        

        // build randomized value with numbers taken from the middle of the original number (from 5th to (x-1)th)
        for(int i = n; i <= n + x - 1; i++){
            // check if value starts with 0 and if it does replace 0  with 1
            if(i == n && B[i] == '0'){
                num += '1';
            }

            else{
                num += B[i];
            }
            //num += B[i];
        }


        // replace A with B for different results, checking if the first number is 0 and replacing it with 1 in that case
        if(B[4] == '0'){
            B[4] = '1';
        }

        A = stod(B.substr(4, 11));
    

        // return final randomized value
        int out = stoi(num);
        
        return(out);
    }


    else{
        std::cout << "x must be less than 8";
    }
    
    return 0;
}

// Создание большого числа длины n
short* bigNum(int n){
    // создание динамического массива
    short* num = new short[n];

    // цикл создания и вывода числа
    for(int i = 0; i < n; i++){
        // проверка, чтобы первая цифра не была равна нулю
        if(i == 0){
            num[i] = (num[i] == 0 ? 1 : num[i]);
        }
        
        // создание и вывод случайной цифры
        num[i] = fonNeyman(1);
    }

    return num;
}

// Сравнение больших чисел
int isBigger(short* num1, short* num2, int n1, int n2){
    // числа разной длины
    if(n1 != n2){
        return(n1 > n2 ? 1 : 0);
    }

    // числа одной длины
    else{
        bool equal = true;

        for(int i = 0; i < n1; i++){
            if(num1[i] > num2[i]){
                return 1;
                equal = false;
                break;
            }
            
            else if(num2[i] > num1[i]){
                return 0;
                equal = false;
                break;
            }
        }

        if(equal) return -1;
    }
    
    return 0;
}

int cornerFix;
// Сложение больших чисел
short* addNums(short* numt, short* numz, int n1, int n2){
    // длина максимального и минимального числа
    int maxLen = std::max(n1, n2);
    int minLen = std::min(n1, n2);
    
    // создание массивов для чисел
    short* number1 = numt;
    short* number2temp = numz;


    // замена массивов местами, чтобы number1 был б`ольшим числом
    short* temp = number1;

    if(isBigger(number2temp, number1, n2, n1)){
        number1 = number2temp;
        number2temp = temp;
    }


    // Формирование меньшего числа
    short* number2 = new short[maxLen];

    // запись цифр числа в отдельный массив
    int diff = maxLen - minLen; 

    for(int i = maxLen - 1; i >= diff; i--){
        number2[i] = number2temp[i - diff];
    }

    // добавление ведущих нулей, если это необходимо
    for(int i = 0; i < maxLen - minLen; i++){
        number2[i] = 0;
    }


    int ansLen = maxLen + 1;

    cornerFix = ((ansLen > maxLen ? 1 : 0));

    short* summ = new short[ansLen];

    // Обнуление ответа
    for(int i = 0; i < ansLen; i++){
        summ[i] = 0;
    }


    // Переменная для переноса
    int p = 0;

    // Цикл сложения с конца
    for(int i = maxLen - 1; i >= 0; i--){
        // s - сумма цифр
        int s = 0;

        s = number1[i] + number2[i] + p;
        
        // Разделение суммы для переноса и записи
        // p - десятки; s - единицы
        p = s / 10;
        s %= 10; 

        summ[i + cornerFix] = s;
    }

    if(p > 0){
        summ[0] += p;
    }


    // очистка памяти и вывод
    number1 = NULL;
    number2temp = NULL;
    number2 = NULL;
    temp = NULL;
    delete[] number1, number2temp, number2, temp;

    return summ;
}

// Вычитание больших чисел
short* subtNums(short* numt, short* numz, int n1, int n2){
    // длина максимального и минимального числа
    int maxLen = std::max(n1, n2);
    int minLen = std::min(n1, n2);
    
    // создание массивов для чисел
    short* number1 = numt;
    short* number2temp = numz;


    // замена массивов местами, чтобы number1 был б`ольшим числом
    short* temp = number1;

    if(isBigger(number2temp, number1, n2, n1)){
        number1 = number2temp;
        number2temp = temp;
    }


    // Формирование меньшего числа
    short* number2 = new short[maxLen];

    // запись цифр числа в отдельный массив
    int diff = maxLen - minLen; 

    for(int i = maxLen - 1; i >= diff; i--){
        number2[i] = number2temp[i - diff];
    }

    // добавление ведущих нулей, если это необходимо
    for(int i = 0; i < maxLen - minLen; i++){
        number2[i] = 0;
    }

    // Теперь number1 - б`ольшое число, number2 - меньшее число (с ведущими нулями)

    // создание итогового массива 
    int ansLen = maxLen;
    short* answer = new short[ansLen];


    // цикл вычитания
    for(int i = maxLen; i >= 0; i--){
        short a = number1[i] - number2[i];
        
        if(a < 0){
            a += 10;
            number1[i - 1] -= 1;
        }

        answer[i] = a;
    }


    // очистка памяти 
    number1 = NULL;
    number2temp = NULL;
    number2 = NULL;
    temp = NULL;
    delete[] number1, number2temp, number2, temp;

    return answer;
}

// ========================================

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

    return std::get<1>(values);
}

// Возведение в степень по модулю
int modexp(int x, int y, int N)
{
    if(y == 0)
    {
        return 1;
    }

    int z = modexp(x, y / 2, N);

    if(y % 2 == 0)
    {
        return (z*z % N);
    }

    else
    {
        return (x*z*z) % N;
    }
}

// Решето Сундарама
bool sundaram(int N){
    std::vector<int> S(((N - 1)/2));

    // создание вектора S (1, 2, ..., (N - 1)/2)
    for(int i = 1; i <= (N - 1) / 2; i++){
        S.at(i - 1) = i;
    }

    // цикл по i (1 <= i <= j)
    for(int i = 1; i <= N; i++){
        
        // цикл по j (1 <= j <= N)
        for(int j = 1; j <= N; j++){
            
            // цикл проверки всех чисел на вид i + j + 2ij
            for(int t = 0; t < size(S); t++){
                
                if(S.at(t) == i + j + 2*i*j){
                    //вычеркивание числа вида i + j + 2ij
                    S.erase(S.begin() + t);
                }
            }
        }
    }

    // вывод
    if(std::find(S.begin(), S.end(), N) != S.end())
    {
        return true;
    }

    return false;
}

// Функция для вывода вектора
template <typename vectorMember>
void printVector(std::vector<vectorMember> _vector)
{   
    for(vectorMember i : _vector)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main()
{
    // Начало алгоритма RSA
    int p = 17;
    int q = 31;

    int n = p * q;

    int phi = (p - 1)*(q - 1);

    // Создание открытой экспоненты
    int openExponent = 0;

    // Проверка чисел Ферма
    int fermi[] = {3, 17, 257, 65537};

    for(int i : fermi)
    {
        if(nod(i, phi) == 1)
        {
            openExponent = i;
            break;
        }
    }

    // Числа Ферма не подошли
    if(openExponent == 0)
    {
        int i = 100;
        while(openExponent == 0)
        {
            if(nod(i, phi) == 1)
            {
                openExponent = 1;
            }
        }
    }
    
    // openExponent = 3;
    // phi = 35;

    std::cout << "RSA public key: " << openExponent << ' ' << n << '\n';

    // Создание секретной экспоненты
    int secretExponent = reverse(openExponent, phi);

    std::cout << "RSA private key: " << secretExponent << ' ' << n << '\n';
    std::cout << "\n\n";


    // Шифрование строки
    // std::string message = "abc";
    // std::cout << "Открытый текст: " << message << '\n';

    // std::string sipher = "";

    // for(char i : message)
    // {
    //     int numberToAdd = modexp(i - '0', openExponent, n);
    //     std::cout << numberToAdd << '\n';
    //     sipher += numberToAdd + '0';
    // }

    // std::cout << "Зашифрованный текст: " << sipher << '\n';


    // Шифрование числа
    int numberToSipher = 8;
    
    // Вывод открытого числа
    std::cout << "Открытое число: ";
    std::cout << numberToSipher << '\n';

    // Создание шифра
    int numberSipher = modexp(numberToSipher, openExponent, n);
    

    // Вывод шифра
    std::cout << "Зашифрованное число: ";
    std::cout << numberSipher << '\n';

    // Расшифрование
    int numberDesiphered = modexp(numberSipher, secretExponent, n);

    // Вывод расшифрованного числа
    std::cout << "Расшифрованное число: ";
    std::cout << numberDesiphered << '\n';
}