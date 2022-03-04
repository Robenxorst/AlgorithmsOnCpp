// HomeWork - YandexContest
// В качестве домашнего задания Борису необходимо решить T заданий следующего вида:
//«Даны два целых числа A и B, можно ровно
// один раз умножить либо A,либо B на любое простое число.
// Какого наибольшего значения НОД можно добиться с помощью такого умножения?»

#include <iostream>
#include <vector>
#include <ios> // рассинхронизация потоков scanf и cin
#include "TimeDuration.hpp"

// Основная идея заключается в домножении
// малого числа на МАКСИМАЛЬНЫЙ ПРОСТОЙ ДЕЛИТЕЛЬ большего числа

// 1)Разбить большее число на простые множители;
// 2)Взять из них максимальный(X);
// 3)Подсчитать НОД исходных двух чисел;
// 4)Перемножить X и НОД исходных двух чисел;
// 5)Распечатать

struct Task{
    int A;
    int B;
};

// Алгоритм Евклида первоначальный
//int gcd(int a, int b)
//{
//    while (a && b)
//        if (a >= b)
//            a %= b;
//        else
//            b %= a;
//    return a | b;
//}

//int gcd(int  a, int b) { // числа A и B могут превышать int
//    while (b > 0) {
//        a %= b;
//        std::swap(a,b);
//    }
//    return a;
//}

// Алгоритм Евклида через рекурсию
inline int gcd(int  a, int b) { // числа A и B могут превышать int
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a >= b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}

// Решето Эратосфена для определения является ли число простым
bool Iratosfen(int n){
    std::vector<int> a;
    int temp;
    for (int i = 0; i < n + 1; i++)
        a.push_back(i);
    for (long long p = 2; p < n + 1; p++)
    {
        if (a[p] != 0)
        {
            temp = a[p];
            for (long long j = p*p; j < n + 1; j += p)
                a[j] = 0;
        }
    }
    if (temp == n)
        return true;
    return false;
}

// Разложение числа на простые множители(возвращает максимальный из них)
int MaxDel(int n){
    // Проверяем не является ли число простым изначально
    if (Iratosfen(n))
        return n;
    int div = 2;

    while (n > 1)
    {
        while (n % div == 0)
            n = n / div;
        if (div == 2) div++;
        else div += 2;
    }
    if (div == 3)
        return 2;
    return (div-2);
}


void MaxNod(std::vector<Task> & Questions){
    for (const auto temp: Questions){// перебираем все элементы массива
        if (temp.A == temp.B)// если на входе два одинаковых числа,то распечатываем одно из них
            std::cout << temp.A << std::endl;
        else if (temp.A > temp.B){
            int res = MaxDel(temp.A) * gcd(temp.A, temp.B);
            std::cout << res << std::endl;
        }
        else{
            int res = MaxDel(temp.B) * gcd(temp.A, temp.B);
            std::cout << res << std::endl;
        }
    }
}

int main() {
    TimeDuration ld("identifier");
    //отключаем синхронизацию потока cin co scanf(в программе мы не используем scanf)
    std::ios_base::sync_with_stdio(false);
    // Количество заданий для Бориса
    int T;
    std::cin >> T;
    std::vector<Task> Questions; // массив заданий
    // заполнение массива заданий
    while(T > 0){
        Task temp;
        std::cin >> temp.A >> temp.B;
        Questions.push_back(temp);
        T--;
    }

    MaxNod(Questions); // распечатываем максимально возможное значение НОД

    return 0;
}
