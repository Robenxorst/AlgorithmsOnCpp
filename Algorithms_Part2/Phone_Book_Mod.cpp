// Телефонная книга: реализуем команды
// 1. add number name
// 2. del number
// 3. find number
// Вход - число запросов, далее сами запросы
// Выход: для каждого find выводим имя, либо "not found"

#include <iostream>
#include <map>
#include <vector>
#include <string>

// По первой цифре номера будем разделять все запросы на 10ть словарей

int main(){
    int n;
    std::cin >> n; // количество наших команд

    // создаем массив из 10ти элементов, которые являются словарями
    std::vector <std::map <std::string, std::string>> book10;

    // Все верхние элементы будут пустышками
    std::map <std::string, std::string> empty = {{"", ""}};
    for (int i = 0; i < 10; i++)
        book10.push_back(empty);

    // Введем итератор для поиска в словарях
    // и колонку для определения словаря
    std::map <std::string, std::string> :: iterator it;
    int colomn;

    for (int i = 0; i != n; i++){
        std::string command;
        std::string number;
        std::cin >> command >> number;
        // Узнаем колонку в которой должен лежать номер
        colomn = number[0] - 48;

        if (command == "add"){
            std::string name;
            std::cin >> name;
            // Ищем номер в соответствующей колонке
            it = book10.at(colomn).find(number);
            // Если номер не нашли, то добавляем новую пару
            if (it == book10.at(colomn).end())
                book10.at(colomn).insert(std::make_pair(number, name));
            // Если такое значение уже есть, то изменяем его;
            else
                it->second = name;
        }

        else if (command == "find"){
            // ищем номер ячейки и распечатываем ее значение;
            it = book10.at(colomn).find(number);
            if (it == book10.at(colomn).end())
                std::cout << "not found" << std::endl;
            else
                std::cout << it->second << std::endl;
        }
        else if (command == "del"){
            // ищем номер ячейки и удаляем ее
            it = book10.at(colomn).find(number);
            if (it == book10.at(colomn).end())
                continue;
            else
                book10.at(colomn).erase(it);
        }
    }

    return 0;
}