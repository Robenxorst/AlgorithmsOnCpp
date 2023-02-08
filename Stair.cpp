#include <algorithm>
#include <iostream>
#include <vector>

// Дано число ступенек n и целые числа a1 a2 ... an
// которыми помечены ступеньки. Найти максимальную сумму,
// которую можно получить, идя по лестнице снизу вверх
// от нулевой до n ой ступеньки, каждый раз поднимаясь
// на одну или две ступеньки.

int MaxWeightOfStair(unsigned n, std::vector<int> a){
    std::vector<int> D(n + 1);  // Массив искомых значений для лестницы
    D[0] = 0;
    D[1] = a[1];

    for (unsigned v = 2; v <= n; v++){
        D[v] = std::max(D[v - 1] + a[v], D[v - 2] + a[v]);
    }
    return D[n];
}

int main(){
    unsigned n, m;
    std::cin >> n;
    m = n;
    std::vector<int> a;// массив отвечающий за вес ступеней лестницы

    a.push_back(0);
    while (n > 0) {
        int weight;
        std::cin >> weight;
        a.push_back(weight);
        n--;
    }

    int res = MaxWeightOfStair(m, a);
    std::cout << res << std::endl;
    return 0;
    }