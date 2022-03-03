// У Андрея есть n бесконечно больших резервуаров, расположенных в один ряд.
// Изначально в каждом резервуаре находится некоторое количество кислоты.
// Необходимо, чтобы в каждом резервуаре был одинаковый объем кислоты
// За одну операцию можно разлить по 1л кислоты
// в каждый из первых 1 <= k <= n резервуаров.
// Для разных операций k могут быть разными.
// Выливать кислоту из резервуаров нельзя. Можно ли уровнять объем кислоты в резервуарах,
// если до то за какое кол-во минимальных операций?

// Ввод : 1 < n < 10^5 - кол-во резервуаров(первая строка),
// n целых чисел 1 < a[i] < 10^9;


// Вывод : если объем возможно уравнять, то выводим мин кол-во операций
// Иначе: -1

#include <iostream>
// библиотека оценки по времени
//#include "TimeDuration.hpp"
#include <vector>
#include <algorithm>
#include <ios> // рассинхронизация потоков scanf и cin

int MinimalOperation(std::vector<unsigned> &Arr){
    unsigned res = 0;

    for (int i = 0; i < Arr.size()-1; i++){
        if (Arr[i] == Arr[i+1])
            continue;
        else if(Arr[i] > Arr[i+1])
            return -1;
        else
            res += Arr[i+1] - Arr[i];
    }

    return static_cast<int>(res);
}

int main() {
    //TimeDuration ld("identifier");
    //отключаем синхронизацию потока cin co scanf(в программе мы не используем scanf)
    std::ios_base::sync_with_stdio(false);//получаем большую оптимизацию по времени

    unsigned n;
    std::cin >> n;
    std::vector<unsigned> Arr;

    while (n > 0){
        unsigned temp;
        std::cin >> temp;
        Arr.push_back(temp);
        n--;
    }

    const int res = MinimalOperation(Arr);

    std::cout << res << std::endl;

    return 0;
}
