//
// Created by palko on 04.01.2022.
//


//Класс, позволяющий оценить быстродействие той или иной функции.
//При запуске деструктора произойдет вывод времени работы блока,
//ограниченного фигурными скобками

//Example:
//{
//TimeDuration ld("identifier");
//// some operations
//}

#ifndef ALGORITHMS_TIMEDURATION_HPP
#define ALGORITHMS_TIMEDURATION_HPP

#include <string>
#include <chrono> // библиотека времени
#include <iostream>

class TimeDuration {
public:
    TimeDuration(std::string id) : id_(std::move(id)) { }
    // конструктор создает индентификатор, ассоциир с названием анализируемой функции
    ~TimeDuration() {
        const auto end_time = std::chrono::steady_clock::now();
        const auto dur = end_time - start_time_;
        std::cout << id_ << ": ";
        std::cout << "operation time"
                  << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }

private:
    const std::string id_;
    const std::chrono::steady_clock::time_point  start_time_ =
            std::chrono::steady_clock::now();
};

#endif //ALGORITHMS_TIMEDURATION_HPP
