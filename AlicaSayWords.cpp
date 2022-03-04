
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <ios> // рассинхронизация потоков scanf и cin

// функция GetNumber получает на вход число 2^i и возвращает степень двойки i
int GetNumber(int & count){
    int res=0;

    if (count == 1){
        return 0;
    }
    while (count != 1){
        count = count >> 1; // делим число на два
        res++;// увеличиваем счетчик делений
    }
    return res;
}

void PrintSymbolsAlice(std::vector<int> & W, std::vector <char> & map ){
    int tempW = 0; //переменная, которая хранит текущее значение W
    for (int i = 0; i < W.size(); i++){// перебираем элементы массива W
        int t = abs(W[i] - tempW); // берем значение числа по модулю
        int j = GetNumber(t);
        std::cout << map[j];
        tempW = W[i];
    }
}


int main(){
    //отключаем синхронизацию потока cin co scanf(в программе мы не используем scanf)
    std::ios_base::sync_with_stdio(false);

    // задаем массив карты из 26тиэлементов
    std::vector <char> map = {'a','b', 'c', 'd', 'e', 'f',
                              'g', 'h', 'i', 'j', 'k', 'l',
                              'm', 'n', 'o', 'p', 'q', 'r',
                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ' };
    int n;
    std::cin >> n;
    // вектор значений W, сказанных алисой
    std::vector <int> W;
    while (n > 0){
        int temp;
        std::cin >> temp;
        W.push_back(temp);
        n--;
    }

    PrintSymbolsAlice(W, map);

    return 0;
}
