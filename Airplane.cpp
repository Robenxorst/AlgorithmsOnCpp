// Airplane
// Дан самолет в котором 1 < n < 100 рядов
// и по три кресла слева и справа в каждом ряду.
// Кресла A и F - крайние и находяться у окна, C и D - центральные, у прохода;
// На входе имеем группы из 1ого, 2ух или 3ех человек. Пассажиры желают сидеть рядом.
// Группа из двоих человек не может быть разделена проходом или одним человеком.
// Один из пассажиров группы обязательно хочет сидеть у окна или у прохода.
// Пассажиры хотят занять места в ряду с наименьшим номером, чтоб быстрее выйти.
// Определить для каждой группы есть ли места в самолете

// Вход : 1 < n < 100 - количество рядов в самолете(первая строка)
// Далее в n строках вводиться изначальная рассадка в самолете
// Символы: . - свободные места; # - занятые места; _ - проход между креслами C и D;
// После этого вводиться число 1 < m < 100 - колчиество групп пассажиров.
// Далее в m строках дано описание групп пассажиров:
// num(1,2,3) - количесвто пассажиров,
// side(left or right) - желаемая сторона,
// position(aisle или window) - желаемое место требовательного пассажира;

// Вывод: а)Если группа может сесть на места, удовлетворяющие их требованиям,
// то выводим: Passengers can take seats: список их мест в формате row letter,
// упорядоченный по возрастанию букв A, В, C, D, E, F;
// Затем необходимо вывести в n строках получившуюся рассадку в формате карты,
// где занятые группой место обозначены x.
// Если нет мест : Cannot fulfill passengers requirements

#include <vector>
#include <string>
#include <iostream>
#include <ios> // рассинхронизация потоков scanf и cin
// библиотека оценки по времени
//#include "TimeDuration.hpp"

// структура с запросами пассажиров

struct Passengers{
    int count = 0;
    std::string side;
    std::string requirement;
};

// Функция распечатки матрицы

void printfMatrix(const std::vector<std::vector<char>> & MatrixChar){
    for (int i = 0; i < MatrixChar.size(); i++){
        for (int j = 0; j < 7; j++){
            std::cout << MatrixChar[i][j];
        }
        std::cout << std::endl;
    }
}

void PrintResults(std::vector<std::vector<char>> & MatrixChar,
                  const Passengers & temp, std::vector <char> const & Symbols) {

    int flag;// определяем место требовательного клиента
    if (temp.side == "left" && temp.requirement == "window")
        flag = 0;
    else if (temp.side == "left" && temp.requirement == "aisle")
        flag = 2;
    else if (temp.side == "right" && temp.requirement == "aisle")
        flag = 4;
    else
        flag = 6;

    if (temp.count == 1) {// рассматриваем вариант с одним пассажиром
        for (int i = 0; i < MatrixChar.size(); i++) {// просто движемся по матрице
            for (int j = 0; j < 7; j++) {
                // найдено свободное место
                if (MatrixChar[i][j] == '.' && flag == j) {
                    MatrixChar[i][j] = 'X';
                    std::cout << "Passengers can take seats: "
                              << i+1 << Symbols[j] << std::endl;
                    //распечатка матрицы
                    printfMatrix(MatrixChar);
                    MatrixChar[i][j] = '#';// место занято
                    return ; // запрос пассажира отработан
                }
            }
        }
    }
    else if (temp.count == 2) {// рассматриваем вариант с двумя пассажирами
        for (int i = 0; i < MatrixChar.size(); i++) {// просто движемся по матрице
            for (int j = 0; j < 7; j++) {
                // найдено два свободных места
                if (MatrixChar[i][j] == '.' && MatrixChar[i][j+1] == '.' && (flag == j || flag == (j+1))) {
                    MatrixChar[i][j] = 'X';
                    MatrixChar[i][j+1] = 'X';
                    std::cout << "Passengers can take seats: "
                              << i+1 << Symbols[j]
                              << " " << i+1 << Symbols[j+1] << std::endl;
                    //распечатка матрицы
                    printfMatrix(MatrixChar);
                    MatrixChar[i][j] = '#';// место занято
                    MatrixChar[i][j+1] = '#';
                    return ; // запрос пассажира отработан
                }
            }
        }
    }
    else if (temp.count == 3) {// рассматриваем вариант с тремя пассажирами
        for (int i = 0; i < MatrixChar.size(); i++) {// просто движемся по матрице
            for (int j = 0; j < 7; j++) {
                // найдено три свободных места
                if (MatrixChar[i][j] == '.' && MatrixChar[i][j+1] == '.' && MatrixChar[i][j+2] == '.'
                    && (flag == j || flag == (j+1) || flag == (j+2))) {
                    MatrixChar[i][j] = 'X';
                    MatrixChar[i][j+1] = 'X';
                    MatrixChar[i][j+2] = 'X';
                    std::cout << "Passengers can take seats: "
                              << i+1 << Symbols[j]
                              << " " << i+1 << Symbols[j+1]
                              << " " << i+1 << Symbols[j+2] << std::endl;
                    //распечатка матрицы
                    printfMatrix(MatrixChar);
                    MatrixChar[i][j] = '#';// место занято
                    MatrixChar[i][j+1] = '#';
                    MatrixChar[i][j+2] = '#';
                    return ; // запрос пассажира отработан
                }
            }
        }
    }
    // места не были найдены
    std::cout << "Cannot fulfill passengers requirements" << std::endl;
}

int main(){
    //TimeDuration ld("identifier");
    //отключаем синхронизацию потока cin co scanf(в программе мы не используем scanf)
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;
    // для карты имеет смысл сделать матрицу из char
    std::vector<std::vector<char>> MatrixChar;

    while (n > 0){
        std::string temp;
        std::cin >> temp;
        std::vector <char> t;
        for (int i = 0; i < 7; i++){
            t.push_back(temp[i]);
        }
        MatrixChar.push_back(t);
        n--;
    }


    int m; // количество групп пассажиров
    std::cin >> m;
    std::vector <char> Symbols = {'A', 'B', 'C','_', 'D', 'E', 'F'};
    Passengers temp;// наша структура
    while (m > 0){
        // заполняем структуру значениями с клавиатуры
        std::cin >> temp.count;
        std::cin >> temp.side;
        std::cin >> temp.requirement;
        // распечатываем результаты обработки запроса
        PrintResults(MatrixChar, temp, Symbols);
        m--;
    }

    return 0;
}