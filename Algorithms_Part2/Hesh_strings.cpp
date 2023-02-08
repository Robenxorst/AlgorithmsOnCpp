// Хеширование цепочками: реализуем команды
// 1. add string
// 2. del string
// 3. find string
// 4. check i
// Вход: m - количество цепочек; n - число запросов, далее сами запросы
// Выход: для каждого find выводим yes или no;
// check i: вывести i-й список (используя пробел в качестве разделителя);
// если i-й список пуст, вывести пустую строку.
// Новый элемент добавляется в вершину цепочки, а не в ее конец
// - поэтому используем стеки;

#include <iostream>
#include <vector>
#include <forward_list> // используем список
#include <string>

// Операция расчета чисел массива оснований X
void Array_X(std::vector <long long> *X){
    long long x = 1; // элементы нашего массива;
    long long p = 1000000007; // число для большой арифметики

    for(int i = 0; i <= 15; i++){
        (*X).push_back(x);
        x = (x * 263) % p; // 263 - это основание полиномиальной хеш-функции;
    }
}

// Операция расчета хеш символа от строки
long long Hash(const std::vector<long long> *X, const std::string &str, unsigned m){
    long long hash = 0;
    long long p = 1000000007; // число для большой арифметики

    for (int i = 0; i < str.size(); i++){
        hash += str[i] * (*X).at(i);
    }

    return (hash % p) % m;
}

int main() {
    unsigned m, n; // соответственно количество цепочек, и количество команд;
    std::cin >> m >> n;

    // создаем массив из m элементов, которые являются словарями
    std::vector<std::forward_list<std::string>> book(m);
    // соответствующий указатель для поиска по словарю
    std::forward_list<std::string>::iterator it;

    // Создаем массив степеней x и сразу же его заполняем;
    std::vector<long long> X;
    Array_X(&X);

    long long hash;

    for (int j = 0; j != n; j++){
        std::string command;
        std::cin >> command;

        // Распечатка элементов списка
        if (command == "check"){
            unsigned i;
            std::cin >> i;
            if ( i < m && !book.at(i).empty()){
                // Распечатка элементов нужного списка;
                for (auto item : book.at(i))
                    std::cout << item << " ";
                std::cout << std::endl;
            }
        }
        // Остальные операции
        else{
            // Считываем строчку
            std::string string;
            std::cin >> string;

            // рассчитываем хеш-значение для нашей строки
            hash = Hash(&X, string, m);

            // Ищем строчку в соответствующем списке
            it = book.at(hash).end();
            auto prev = book.at(hash).begin();
            if(!book.at(hash).empty()){
                it = book.at(hash).begin();
                while( it != book.at(hash).end()){
                    if (*it == string) // если строчка найдена
                        break; // итератор указывает на позицию строки
                    prev = it; // итератор на предыдущий элемент необходим для удаления;
                    ++it;
                }
            }
            // итератор в конце списка - список либо не существует, либо элемент не найден

            if (command == "add"){
                // Если строчку не нашли, то добавляем новый элемент в начало множества
                if (it == book.at(hash).end())
                    book.at(hash).push_front( string);
            }

            else if (command == "find"){
                if (it == book.at(hash).end())
                    std::cout << "no" << std::endl;
                else
                    std::cout << "yes" << std::endl;
            }

            else if (command == "del"){
                if (it == book.at(hash).end())
                    // элемент найден не был;
                    continue;
                else if ( it == book.at(hash).begin())
                    // отдельно прописываем вариант с удалением первого элемента;
                    book.at(hash).pop_front();
                else // обычная операция удаления
                    book.at(hash).erase_after(prev);
            }
        }

    }

    return 0;
}
