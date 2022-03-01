#include <cassert>// вывод ошибок через при неправильных данных assert
#include <iostream>
#include <vector>//подключаем динамический массив vector

class Fibonacci {
public:
    static unsigned long long get(unsigned long long n) {// возвращаем число Фибоначчи
        assert(n >= 0);
        if (n == 0)
            return 0;
        unsigned long long last = 0;
        unsigned long long current = 1;
        for(unsigned long long i = 2; i <= n; ++i){
            unsigned long long temp = (last + current);
            last = current;
            current = temp;
        }
        return current;
    }

    static int get_digit(unsigned long n, int m) {// возвращаем остаток от деления
        if (n == 0)
            return 0;
        int * f = new int [n + 1];
        f[0] = 0;
        f[1] = 1;
        for(unsigned long i = 2; i <= n; ++i)
            f[i] = (f[i-1] + f[i - 2]) % m;
        return f[n];
    }

    static int get_remainder(long long n, int m) {
        assert(n >= 1);
        assert(m >= 2);
        if (n == 0)
            return 0;
        unsigned long def = n % get_pizano_period(m);
        return get_digit(def, m);
    }

    static unsigned long get_pizano_period(int m)// рассчитываем период Пизано
    {
        std::vector<unsigned long> v{1 ,1};// в векторе будем хранить остатки от деления чисел Фибоначи на m
        while (true)//выполняем цикл до тех пор, пока не будет выполнено условие if
        {
            auto t = (v[v.size() - 1] + v[v.size() - 2]) % m; //рассчитываем остаток от деления
            v.push_back(t); // добавляем ячейку в конец массива векторов
            if ( (t == 0) && // проверка, что начало периода равно 0
                    (v.size() % 2 == 0) &&// проверка, что количество элементов делится на 2
                    std::equal(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2, v.end() ) )
                //оператор equal сравнивает проверяет,что от begin до mid и от mad до end
                //лежат одинаковые элементы
                return v.size() / 2;// когда нашли две совпадающие последовательности, то выводим длину одной из них
        }
    }
};

int main() {
    long long n;
    int m;
    std::cin >> n >> m;
    std::cout << "Fibonachi : " << Fibonacci::get(n) << std::endl;
    std::cout << "Pizano : " << Fibonacci::get_pizano_period(m) << std::endl;
    std::cout << "Fibonaci mod m : " << Fibonacci::get_remainder(n, m) << std::endl;
    return 0;
}
