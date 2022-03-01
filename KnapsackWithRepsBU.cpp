// Первая строка входа содержит целые числа W и n
// — вместимость рюкзака и число золотых слитков.
// Следующая строка содержит n целых чисел w1…wn, задающих веса слитков.
// Найдите максимальный вес золота, который можно унести в рюкзаке.


// дача сводиться к алгоритму рюкзака без повторений(iый элементможно использовать только один раз)!
// В качестве стоимости у нас выбираются сами веса золотых слитков
// (предметы одинаковы по цене за 1кг)
#include <iostream>
#include <vector>
#include <algorithm>

unsigned KnapsackWithRepsBU(const unsigned & W,std::vector<unsigned> & arrW){
    const auto n = arrW.size()-1;//массив arrW был искусственно расширен
    // d[i][w] - создаем матрицу с максимальными стоимостями рюкзака
    // сразу же выделяем нужный нам размер
    std::vector<std::vector<unsigned>> D
            (n+1, std::vector <unsigned>(W+1));
    // нулевая строка и столбец заполняется нулями
    for (int i = 0; i <= n; i++){
        D[i][0] = 0;
    }
    for (int w = 0; w <= W; w++){
        D[0][w] = 0;
    }

    for (unsigned i = 1; i <= n; i++){
        for (unsigned w = 1; w <= W; w++){
            D[i][w] = D[i-1][w];
            if (arrW[i] <= w)
                D[i][w] = std::max(D[i][w], D[i-1][w-arrW[i]] + arrW[i]);
        }
    }

    return D[n][W];
}

int main(){
    unsigned long W;// переменная отвечает за вес рюкзака
    unsigned n;
    std::cin >> W >> n;
    std::vector<unsigned> arrWeights;// массив отвечающий за вес слитков

    // элемент под номером 0 в массиве весов не используется
    arrWeights.push_back(0);
    while (n > 0){
        unsigned weight;
        std::cin >> weight;
        arrWeights.push_back(weight);
        n--;
    }
    // в итоге имеем массив arrWeights из n+1 элементов с 0ым незначимым числом

    // так как мы работаем с одинаковыми золотыми слитками,
    // то стоимость слитков будет одинакова
    const unsigned res = KnapsackWithRepsBU(W, arrWeights);
    std::cout << res << std::endl;
    return 0;
}
