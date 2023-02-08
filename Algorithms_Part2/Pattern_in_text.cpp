// Поиск образца в тексте - реализация алгоритма Рабина-Карпа;

#include<iostream>
#include<string>
#include<vector>

#define p 1000000007 // число для большой арифметики
#define x 1 // Основание полиномиальной Хеш-Функции;

// Функция возведения числа в степень по модулю p
long long pow(const long long &base, const unsigned long &power){
    if (power == 0 || base == 1)
        return 1;

    long long res = 1;

    for (unsigned long i = 1; i != power; i++)
        res = (res * base) % p;
    return res % p;
}

// Операция расчета хеш функции от строки
long long Hash(const std::string &str){
    long long hash = 0;

    for (int i = 0; i < str.size(); i++){
        hash = (hash + str[i] * pow (x, i)) % p;
    }

    return hash % p;
}

int main(){
    std::string pattern, text;
    std::cin >> pattern >> text;

    // массив для ответа;
    std::vector<unsigned > result;

    // рассчитываем хеш паттерна и его длину
    long long pattern_hash = Hash( pattern);
    long long length_window = pattern.length();

    // начальная позиция последнего окна
    unsigned len = text.length() - length_window + 1;
    // Вспомогательные переменные
    char old_char = text[0];// символ, который удаляется
    char new_char;// символ, который добавляем
    long long hash = Hash(text.substr(0, length_window));
    long long tmp;

    // идем слева направо по нашей строке
    for (unsigned i = 0; i < len; i++){
        // Если обнаружили совпадение
        if (hash == pattern_hash){
            // сравниваем строки
            if ( text.substr(i, length_window) == pattern)
                result.push_back(i);
        }
        new_char = text[i + length_window];
        tmp = ((hash - old_char) % p + p) % p;
        tmp = tmp / x;
        hash = tmp + ((new_char * pow(x, length_window - 1)) % p) % p;
        old_char = text[i + 1];
    }

    // Распечатка результата;
    for (auto j : result){
        std::cout << j << " ";
    }
    std::cout << std::endl;
    return 0;
}