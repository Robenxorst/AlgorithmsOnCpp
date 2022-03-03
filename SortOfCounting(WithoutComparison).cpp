#include <iostream>
#include <vector>
#include <algorithm>// sort
#include <cstddef>// size_t

std::vector<size_t> CountSort(std::vector<size_t> &A, size_t &M){

    std::vector <size_t> res(A.size(), 0);// возвращаемое значение
    std::vector<size_t> B;// массив, содержащий
    // сколько раз встречается то или иное число массиве A
    B.push_back(-1);// нулевой элемент массива не используем,
    // так как работаем с натуральными числами

    size_t i = 1;
    while (i++ <= M){// заполняем массив нулями,
        // начиная с элемента под номером 1(не 0).
        // Всего в массиве должно быть M значений,
        // где М - максимальное число в массиве A
        B.push_back(0);
    }
    for(size_t j = 0; j < A.size(); j++){
        B[A[j]] = B[A[j]] + 1; // теперь в В лежит сколько раз
        // некое число m=A[j] встречается в А
    }
    for(size_t k = 2; k <= M; k++){
        B[k] = B[k] + B[k-1];// к каждому элементу прибавляем
        // предыдущий элемент, получая позицию индекса в искомом массиве
    }
    for (size_t l = A.size() - 1; l != -1; l--){
        res[B[A[l]]-1] = A[l];// в результат на позицию
        // элемента(определяем из B) кидаем сам элемент
        B[A[l]] -= 1;// уменьшаем значение индекса в В
        // Массив заполняется справа налево;
    }

    return res;
}



int main(){
    size_t n;
    std::cin >> n;

    std::vector<size_t> array;

    while (n-- != 0){
        size_t a;
        std::cin >> a;
        array.push_back(a);
    }

    size_t M = 10;
    std::vector<size_t> res = CountSort(array, M);

    size_t i = 0;
    while (i < res.size()){
        std::cout << res[i] << " ";
        i++;
    }

    std::cout << std::endl;

    return 0;
}