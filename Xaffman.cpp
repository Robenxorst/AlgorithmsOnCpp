//
// Created by palko on 04.01.2022.
//

#include <algorithm>// sort
#include <cassert>// assert
#include <cstddef>// size_t
#include <iostream>
#include <string>
#include <queue>// очереди
#include <tuple>// tie
#include <unordered_map>// unordered map
#include <vector>

class Huffman {
    struct CharSetFrequency {
        std::string char_set;
        int frequency;

        bool operator < (const CharSetFrequency &other) const { // переопределяем опреатор
            // для сортировки от большего к меньшему
            return std::tie(frequency, char_set) > std::tie(other.frequency, other.char_set);
        }
    };
//    // вспомогательный метод для кодировки Шенона Фано(ниже на англ описано, что подается на вход)
//    static std::unordered_map<char, std::string> shannon_fano_encode
//                                (const std::vector<CharFrequency> &frequencies, int total_frequency);
//    //input array must be sorted be frequency
//    //sum of all frequencies must be passed in total_frequency
public:
    static std::unordered_map<char, std::string> encode(const std::string &text);

    static std::string decode(const std::string &text, const std::unordered_map<char, std::string> &huffman_encoding);
};

//Метод Шенона-Фано, который не всегда выдает верный ответ


//std::unordered_map<char, std::string> Huffman::shannon_fano_encode
//                                (const std::vector<CharFrequency> &frequencies, int total_frequency) {
//
//    size_t size = frequencies.size();// количество различных букв в строке
//
//    std::unordered_map<char, std::string> result;
//
//    if (size <= 1) {//если таких букв не более одной, то отображаем в каждую букву пустую строку
//        for (auto &frequency: frequencies) {
//            result[frequency.c] = "";
//        }
//        return std::move(result);
//    }//так же это условие выхода из рекурсии
//
//    //жадно разбиваем все буквы на две группы
//    size_t split_pos;
//    int first_part_frequency = 0;
//    for (split_pos = 0; split_pos < size; split_pos++) {
//        int current_frequency = frequencies[split_pos].frequency;
//        if (first_part_frequency >= total_frequency - (first_part_frequency + current_frequency)){
//            // adding current c increases difference between part frequencies
//            break;
//        }
//        first_part_frequency += current_frequency;
//    }
//
//    assert(split_pos < size); // проверка не стал ли счетчик разбивки больше,
//    // чем количество букв(может стать таковым из-за инкремента в конце цикла
//
//    // результат объединения частей
//    for (auto &encoded: shannon_fano_encode
//                    ({frequencies.begin(), frequencies.begin() + split_pos}, first_part_frequency)) {
//        result[encoded.first] = "0" + encoded.second;
//    } // рекурсивно кодируем первую группу вначале дописывая 0
//    // (при развертке рекурсии снизу вверх запись будет зеркально отображена)
//    for (auto &encoded: shannon_fano_encode
//            ({frequencies.begin() + split_pos, frequencies.end()}, total_frequency - first_part_frequency)) {
//        result[encoded.first] = "1" + encoded.second;
//    }// аналогично со второй группой и еденицей;
//    return std::move(result);
//}

// описание метода кодирования символов кода Хаффмана(имеет доступ к приватным ячейкам)
std::unordered_map<char, std::string> Huffman::encode(const std::string &text){
    std::unordered_map<char, int> char_frequencies;

    for (auto c:text) { // for (auto c = text.begin(); c != text.end(); ++c) - эквивалент данной записи(подробнее - итераторы)
        char_frequencies[c]++; // вычисляем для каждого символа частоту,
        // с которой он встречается во входной строчке
    }

    std::vector<CharSetFrequency> frequencies;// кладем полученные unordered_map частоты в вектор
    for (auto char_frequency:char_frequencies) { // преобразование полученных unordered_map частот в вектор
        frequencies.push_back( { std::string (1, char_frequency.first), char_frequency.second} );
    }

//    std::sort(frequencies.begin(), frequencies.end());// сортировка вектора по уменьшению
//    // частоты для алгоритма Шенона - Фано

    if (frequencies.size() == 1) // один символ в исходной строке
    {
        //присваиваем этому символу код 0;
        std::unordered_map<char, std::string> result;
        result[frequencies[0].char_set[0]] = "0";
        return result;
    }

//    return shannon_fano_encode(std::move(frequencies), static_cast<int>(text.size()));



    // Алгоритм Хафмана
    std::priority_queue<CharSetFrequency> q(frequencies.begin(), frequencies.end()); //инициализируем
    // очередь с приоритетом массивом из наших класов CharSetFrequency

    std::unordered_map<char, std::string> result;

    //до тех пор пока в очереди хотя бы два элемента
    while(q.size() >= 2) {
        auto first = q.top(); // кладем в first первый элемент очереди
        q.pop();//удаляем его
        auto second = q.top();
        q.pop();

        for (auto c:first.char_set) {// символам из первого множества дописываем 0
            result[c] += "0";
        }
        for (auto c:second.char_set) {
            result[c] += "1";
        }
        // добавляем в очередеь элемент с объединенными символами и суммой частот
        q.push({first.char_set + second.char_set, first.frequency + second.frequency});
    }

    // необходимо перевернуть все получившиеся строки,
    // так как после цикла получили зеркальное отображение

    for (auto &it:result) // second в result - это как раз наши строки string , которые мы реверсим
        std::reverse(it.second.begin(), it.second.end());

    return  result;
}


std::string Huffman::decode(const std::string &text, const std::unordered_map<char, std::string> &huffman_encoding){
    size_t len = text.size();
    size_t pos = 0;
    std::string result;
    while (pos < len) {
        for (auto &encoded:huffman_encoding) {
            if (text.substr(pos, encoded.second.size()) == encoded.second) {// если
                // подстрока текста, начиная с pos, длиной строчки,
                // которая лежит в нашей кодировке на втором месте,
                // полностью совпадает с этой самой строчкой(которая на втором месте в unordered_map)
                result += encoded.first;// добавляем в результат эту строчку со второго места
                pos += encoded.second.size();// увеличиваем позицию
                // указателя на размер добавленной строчки
                break;
            }
        }
    }
    return result;
}


int main()
{
    // Кодирование кода Хафмана:
//    std::string text;
//    std::cin >> text;
//    // класс Huffman занимется только созданием ассоциативного словаря,
//    // то бишь двоичного древа кодов
//
//    auto huffman_encoding = Huffman::encode(text);//кодируем текст
//    // в ассоциативный массив(словарь) unordered_map,
//    // где каждому ключу соответствует одно кодовое значение
//
//
//    std::string encoded_text; //создаем строку, в которую будем закидывать
//    for (auto c:text){
//        encoded_text += huffman_encoding[c];//поэлементно закидываем
//        // в новую строчку коды из нашего словаря, проводя соответствие с каждым символом из текста
//    }
//    // выводим размер алфавита(кол-во элементов в словаре) и размер закодированного текста
//    std::cout << huffman_encoding.size() << " " << encoded_text.size() << std::endl;
//    // для каждого символа входного текста выводим его кодировку
//    for (auto &encoded: huffman_encoding){
//        std::cout << encoded.first << ": " << encoded.second << std::endl;
//    }
//    // выводим саму кодировку входного текста
//    std::cout << encoded_text << std::endl;



// Декодирование кода Хафмана:
    int size_of_map;
    int size_of_string;

    std::cin >> size_of_map >> size_of_string;
// как распарсить с: 0?

    std::unordered_map<char, std::string> huffman_encoding;

    std::string tempC;
    std::string tempS;

    int i = 0;

    while (i < size_of_map)
    {
        std::cin >> tempC;
        const char c = tempC[0];
        std::cin >> tempS;
        huffman_encoding[c] = tempS;
        i++;
    }

    std::string code;

    std::cin >> code;

    std::string  dec;
    dec = Huffman::decode(code, huffman_encoding);
    std::cout << dec << std::endl;

    return 0;
}