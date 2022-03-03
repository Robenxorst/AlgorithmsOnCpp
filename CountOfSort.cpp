//Первая строка содержит число  n ,
//вторая — массив A[1…n], содержащий натуральные числа.
//Необходимо посчитать число пар индексов
// 1≤i<j≤n, для которых A[i]>A[j].
// (Такая пара элементов называется инверсией массива.
// Количество инверсий в массиве является в некотором смысле его
// мерой неупорядоченности: например, в упорядоченном по неубыванию
// массиве инверсий нет вообще, а в массиве, упорядоченном по убыванию,
// инверсию образуют каждые два элемента.)

// для корректного подсчета количества инверсий к входным
// данным добавляются нули в начале, чтобы количество элементов
// было всегда равно двум в какой либо степени
#include <algorithm>// sort
#include <cstddef>// size_t
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "TimeDuration.hpp"

// работаем исключительно на стеках,а не на массивах

std::stack<size_t> Reverse(std::stack <size_t> &s){// функция реверса стека
    std::stack<size_t> rez;

    while(!s.empty()){
        rez.push(s.top());
        s.pop();
    }

    return rez;
}

// распечатка стека
void PrintStack(std::stack <size_t> s){
    while (!s.empty()){
        std::cout <<  s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

std::stack<size_t> Merge(std::stack<size_t> &st_b, std::stack<size_t> &st_c, size_t &count){
    // на входе функции имеем
    // два отсортированных(по ворастанию) стека,
    // которые требуется слить в один
    // b[] = {1, 3, 4, 7}
    // c[] = {2, 5, 6, 8}

    std::stack<size_t> rez;//результирующий массив - слияние двух массивов

    while (!st_b.empty() && !st_c.empty()) {
        if (st_b.top() <= st_c.top()){
            rez.push(st_b.top());
            st_b.pop();
        }
        else if (st_b.top() > st_c.top()){//проверка не выполняется,
            // если сработал другой if
            rez.push(st_c.top());
            st_c.pop();
            count += st_b.size();
        }
    }

    if (st_c.empty()){
        while(!st_b.empty()){
            rez.push(st_b.top());
            st_b.pop();
        }
    }
    if (st_b.empty()){
        while(!st_c.empty()){
            rez.push(st_c.top());
            st_c.pop();
        }
    }

    return Reverse(rez);
}

// вмешний итеративный алгоритм, использующий Merge

std::stack<size_t> IterativeMergeSort(std::vector<size_t> &A, size_t &count) {
    std::queue<std::stack <size_t>> q;// создаем очередь, состоящую из стеков;

    size_t i = 0;
    while(i < A.size()){//заполняем очередь стеками
        std::stack <size_t> temp;
        temp.push(A[i]);
        q.push(temp);
        i++;
    }// работает верно

    while (q.size() != 1) {
        std::stack<size_t> buf = q.front();//вынимаем и запоминаем первый элемент очереди
        q.pop();// теперь он нам не нужен
        q.push(Merge(buf, q.front(), count));
        // вынимаем из очереди два первых элемента, мерджим их,
        // результат кладем в конец очереди
        q.pop();// второй элемент сравнения больше не нужен
        PrintStack(q.back());// распечатка положенного в очередь стека
    }

    return q.front();
}

size_t logC(size_t &n){
    size_t pow = 0;
    size_t n_copy = n;
    while (n_copy > 0) {
        n_copy >>= 1;
        pow++;
    }
    return pow;
}

int main(){
    TimeDuration ld("identifier");// определение быстродействия программы
    std::vector <size_t> array;
    size_t n;// количество элементов во входном массиве
    std::cin >> n;

    size_t cheat = logC(n); // ближайшая степень
    // двойки к исходному количеству элементов
    size_t n1 = 1;
    while (cheat-- != 0){
        n1 *= 2;
    }
    size_t count_zero = n1 - n;
    // дополняем количество элементов массива до 2^cheat.
    // Т.о. создаем идеальные условия сортировки.
    while (count_zero-- != 0){
        array.push_back(0);
    }
    while (n-- > 0){
        int a;
        std::cin >> a;
        array.push_back(a);
    }// заполняем входной массив элементами с клавиатуры;

     //распечатка модифицированного входного массива
    size_t j = 0;
    while(j < array.size()) {
        std::cout << array[j] << " ";
        j++;
    }

    size_t count = 0;// количество инверсий в массиве
    std::stack<size_t> result = IterativeMergeSort(array, count);

    PrintStack(result);

    std::cout << count << std::endl;

    return  0;
}