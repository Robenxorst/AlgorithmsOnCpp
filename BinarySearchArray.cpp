// В первой строке даны целое число n
//и массив A[1…n] из n различных натуральных чисел, не превышающих 10^910
//в порядке возрастания, во второй — целое число k
// и k натуральных чисел. Для каждого i от 1 до k необходимо
// вывести индекс j для которого A[j]=b[i],
// ,или -1, если такого j нет.


#include <algorithm>// sort
#include <cassert>// assert
#include <cstddef>// size_t
#include <iostream>
#include <queue>
#include <vector>

// медленный линейный поиск числа в массиве
int get_pos_linear(const std::vector<int> &numbers, int number) {
    auto it = std::find(numbers.begin(), numbers.end(), number); //возвращает итератор,
    // указывающий на число
    if (it == numbers.end()) {
        return -1;// если число не было найдено,
        // то мы дошли до конца массива
    }
    return static_cast<int>(it - numbers.begin()) + 1;// прибавляем 1,
    // так как нумерация начинается с 1;
}

// реализация бинарного поиска через стандартную библиотеку

int get_pos_binary(const std::vector<int> &numbers, int number) {
    auto it = std::lower_bound(numbers.begin(), numbers.end(), number); //возвращает итератор,
    // указывающий на элемент не меньший данного
    if (it == numbers.end() || *it != number) {
        return -1;// если число не было найдено или число больше чем переданное,
        // то мы дошли до конца массива
    }
    return static_cast<int>(it - numbers.begin()) + 1;// прибавляем 1,
    // так как нумерация начинается с 1;
}
// реализация поиска вручную
int get_pos_binary_hands(const std::vector<int> &numbers, int number) {
    size_t l = 0;
    size_t r = numbers.size();
    size_t m;
    while (l + 1 < r) { // пока в итерируемом массиве есть числа
        m = l + ((r - l) / 2); // медианный индекс вычисляем,
        // избегая переполнения при сложении
        if (numbers[m] > number) {
            r = m;
        } else {
            l = m;
        }
    }
    if (l == r || numbers[l] != number) {
        return -1;
    }
    return static_cast<int>(l + 1);
}

int main(){
    std::vector<int> numbers;// массив чисел
    size_t number_count;
    std::cin >> number_count;// считываем количество чисел
    numbers.resize(number_count);// пересобираем массив чисел
    for (auto &number:numbers){
        std::cin >> number;
    }// заполняем массив числами через итератор
    assert(std::is_sorted(numbers.begin(), numbers.end()));// проверяем,
    // что массив действительно отсортирован

    size_t query_count;// количество запросов на поиск числа
    std::cin >> query_count;
    while (query_count-- > 0) {
        int number;// выводим для каждого числа найденную позицию
        std::cin >> number;
        std::cout << get_pos_binary_hands(numbers, number) << " ";
    }
    std::cout << std::endl;
    return 0;
}