// Телефонная книга: реализуем команды
// 1. add number name
// 2. del number
// 3. find number
// Вход - число запросов, далее сами запросы
// Выход: для каждого find выводим имя, либо "not found"

#include <iostream>
#include <map>
#include <string>

int main(){
    int n;
    std::cin >> n; // количество наших команд

    std::map <std::string, std::string> book;
    std::map <std::string, std::string> :: iterator it;

    for (int i = 0; i != n; i++){
        std::string command;
        std::cin >> command;
        if (command == "add"){
            std::string number;
            std::string name;
            std::cin >> number >> name;
            // Если такое значение уже сеть, то перезаписываем его;
            it = book.find(number);
            if (it == book.end())
                book.insert(std::make_pair(number, name));
            else
                it->second = name;
        }
        else if (command == "find"){
            std::string number;
            std::cin >> number;
            // ищем номер ячейки и распечатываем ее значение;
            it = book.find(number);
            if (it == book.end())
                std::cout << "not found" << std::endl;
            else
                std::cout << it->second << std::endl;
        }
        else if (command == "del"){
            std::string number;
            std::cin >> number;
            // ищем номер ячейки и удаляем ее
            it = book.find(number);
            if (it == book.end())
                continue;
            else
                book.erase(it);
        }
    }

    return 0;
}