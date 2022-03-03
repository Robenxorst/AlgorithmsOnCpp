//
// Created by palko on 04.01.2022.
//
#include <iostream>
#include <cassert>//assert - функция вывода ошибки при некорректных данных
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::vector <int> items;
    int temp = n;
    for( int i = 1; i <= n; i++) {
        n = n - i;
        if (n > i)
        {
            items.push_back(i);
            temp = temp - i;
        }
        else
        {
            items.push_back(temp);
            break;
        }
    }

    std::cout << items.size() << std::endl;
    for (int i = 0; i < items.size(); i++)
        std::cout << items[i] << " ";
    return 0;
}