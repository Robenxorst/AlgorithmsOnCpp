//
// Created by palko on 04.01.2022.
//

// Первая строка содержит количество предметов n
// и вместимость рюкзака W.
// Каждая из следующих n строк задаёт стоимость c[i]
// и объём w[i] предмета. Выведите максимальную стоимость частей предметов
// (от каждого предмета можно отделить любую часть, стоимость и объём
// при этом пропорционально уменьшатся), помещающихся в данный рюкзак,
// с точностью не менее трёх знаков после запятой.

#include <iostream>//sort
#include <cassert>//assert - функция вывода ошибки при некорректных данных
#include <vector>
#include <cinttypes>
#include <algorithm>
#include <iomanip>
#include <ios> // подключаем рассинхронизацию потоков scanf и cin

struct Item final { // класс описывающий параметры вещи
    int weight;// вес
    int value;// стоимость
};

//Функция определяющая максимальную стоимость рюкзака
//при заданной вместимости и вещах, которые мы можем туда класть

//double get_price_quality(const Item & item)// Показатель цена-качество;
//{
//    // в данном случае скольк остоит вещь - это ее вес,
//    // а стоимость - это ее качество
//    return static_cast <double>(item.weight) / item.value;
//}

bool comp(const Item &left, const Item &right)
{
//    return get_price_quality(left) < get_price_quality(right);
    return static_cast <std::int64_t> (left.weight) * right.value <
            static_cast <std::int64_t> (left.value) * right.weight;
    // оптимизационная замена деления в функции цена-качество умножением,
    // по правилу креста для дробей + приведение к более вместительному типу инта
}

double get_max_knapsack_value(int capacity, std::vector <Item> items)
{
    double value = 0.0;
    // сортировка от большего к меньшему по цене-качеству
    std::sort(items.begin(), items.end(), comp);
    // элементы попадают в comp в том порядке,
    // как они указаны в sort

    // take items while there is empty space in bag
    for (auto &item:items)//перебираем все вещи в том порядке,
        // в котром они были переданны
    {
        if (capacity > item.weight){
            //can take full item and continue
            capacity -= item.weight;
            value += item.value;
        }
        else {
            value += item.value * (static_cast <double>(capacity) / item.weight);
            // берем ту часть вещи, котроая влезает в рюкзак  завершаем перебор
            break;
        }
    }

    return value;
}


int main() {
    //отключаем синхронизацию потока cin co scanf(в программе мы не используем scanf)
    std::ios_base::sync_with_stdio(false);//получаем большую оптимизацию по времени

    int number_of_items;
    int knapsack_capacity;
    std::cin >> number_of_items >> knapsack_capacity;
    std::vector <Item> items(number_of_items);
    for( int i = 0; i < number_of_items; i++) {
        std::cin >> items[i].value >> items[i].weight;
    }

    double max_knapsack_value = get_max_knapsack_value(knapsack_capacity,
                                                       std::move(items));
    //настройка вывода трех чисел после запятой
    std::cout << std::fixed << std::setprecision(3) << max_knapsack_value << std::endl;
    return 0;
}