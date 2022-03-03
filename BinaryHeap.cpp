#include <algorithm>// sort
#include <cassert>// assert
#include <cstddef>// size_t
#include <iostream>
#include <string>
#include <queue>
#include <vector>


// реализация структуры типа
// полное двоичное макс-дерево через массив
// (в корне дерева максимальное число)

//функция округления целочисленного деления вверх
int div_up(int x, int y){
    return (x + y - 1) / y;
}

void SiftUp(int i, std::vector<int> &a){ // просеивание вверх
    while((i > 1) && (a[div_up(i+1,2)] < a[i])){
        int temp = a[div_up(i+1,2)];
        a[div_up(i+1,2)] = a[i];
        a[i] = temp;
        i = div_up(i+1,2);
    }
}

void SiftDown(int i, std::vector<int> &a){ // просеивание вниз
    while (2*i <= (a.size()-1)){ // топим до тех пор,
        // пока не дойдем до самого низа кучи.


        // Стоит учитывать,
        // что количество элементов в дереве на один меньше чем в векторе,
        // так как нулевой элемент отсутствует

        int j = i; // в переменную j кладем максимум из трех элементов(родителя и двух детей);
            if (a[2*i] > a[j])
                j = 2*i;
            if (2*i+1 <= (a.size()-1) && a[2*i+1] > a[j])
                j = 2*i + 1;
        if (j == i) // если два элемента совпали, то мы ничего не делаем
            break;
        int temp = a[i]; // иначе меняем элементы местами;
        a[i] = a[j];
        a[j] = temp;
        i = j; // условие продолжения цикла;
    }
}

void Insert(int x, std::vector<int> &a){ // добавление элемента в макс кучу
    a.push_back(x);
    SiftUp(a.size()-1, a);// Принимает на вход номер елемента,
    // который будем просеивать вверх
}

int PeekMax(std::vector<int> &a){// посмотреть на максимальное число
    // (посмотреть на корень)
    return a[1];
}

int ExtractMax(std::vector<int> &a) {
    int ex_min = a[1]; // в ответе лежит вершина дерева
    a[1] = a[a.size()]; // отправляем в вершину элемент из конца дерева
    a.pop_back();// удаляем элемент в конце дерева
    SiftDown(1, a); // просеиваем вниз новую вершину

    return ex_min;
}

int main(){
    int CountOfOperation;
    std::vector<int> a;
    a.push_back(-1); // нулевой элемент вектора
    // не задействован в дереве
    std::cin >> CountOfOperation;


    for(int i = 0; i < CountOfOperation; i++)
    {
        std::string Operation;
        std::cin >> Operation;
        if (Operation == "Insert"){
            int x;
            std::cin >> x;
            Insert(x, a);
        }
        if (Operation == "ExtractMax")
            std::cout << ExtractMax(a) << std::endl;
    }
    return 0;
}