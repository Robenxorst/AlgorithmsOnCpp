//Дано целое число n и массив A[1…n] натуральных чисел, не
//превосходящих 2⋅10^9. Выведите максимальное 1≤k≤n, для которого
//найдётся подпоследовательность 1≤i1<i2<…<ik≤n длины k, в
//которой каждый элемент делится на предыдущий (формально: для  всех 1≤j<k,
//A[ij] | A[ij+1]).

#include <iostream>
#include <vector>
#include <algorithm>

int LISBottomUP(std::vector<int> & A){
    std::vector<int> D;

    for (int i = 0; i < A.size(); i++){
        D.push_back(1);
            for (int j = 0; j < i; j++){
                if (A[i]%A[j] == 0  && (D[j]+1) > D[i]){
                    D[i] = D[j] + 1;
                }
            }
    } // получили массив D
    int answer = 0;
    for (int k = 0; k != D.size(); k++){
        answer = std::max(answer, D[k]);
    }
    return answer;
}

int main(){
    unsigned int n;
    std::cin >> n;
    std::vector<int> arr;

    while (n > 0){
        int temp;
        std::cin >> temp;
        arr.push_back(temp);
        n--;
    }

    const int res = LISBottomUP(arr);

    std::cout << res << std::endl;
    return 0;
}