// Задача на поиск максимума в скользящем окне

// Пример входных данных:
// 8
// 2 7 3 1 5 2 6 2
// 4
// Выходные данные:
// 7 7 5 6 6

#include <iostream>
#include <stack>
#include <queue>

int main(){
    int count; // количество элементов в очереди
    std::cin >> count;

    std::queue <int> queue; // очередь входных элементов
    for (int i = 0; i < count; i++){
        int temp;
        std::cin >> temp;
        queue.push(temp);
    }

    int window; // размер окна
    std::cin >> window;

    // стек на входе
    std::stack <int> stack_in;
    // входной стек максимумов;
    std::stack <int> stack_in_max;
    // стек на выходе
    std::stack <int> stack_out;
    // выходной стек максимумов;
    std::stack <int> stack_out_max;

    // В начале основного цикла имеем полностью заполненный входной стек
    while ( stack_in.size() != window){
        int a = queue.front();
        stack_in.push(a);
        if (stack_in_max.empty())
            stack_in_max.push(a);
        else
            stack_in_max.push(std::max(stack_in_max.top(), a));
        queue.pop();
    }
    // таким образом макс размер любого стека всегда равен размеру окна

    // Условие выхода из основного цикла - это отсутствие новых элементов в очереди
    while (true){
        // Если пуст выходной стек, то надо заполнить его значениями из входного
        if (stack_out_max.empty())
            while(stack_out.size() != window){
                int a = stack_in.top();
                stack_out.push(a);
                if (stack_out_max.empty())
                    stack_out_max.push(a);
                else
                    stack_out_max.push(std::max(stack_out_max.top(), a));
                stack_in.pop();
                stack_in_max.pop();
            }

        int max; // выбираем максимум из двух стеков

        // Если пуст входной, то максимум - это число из выходного
        if (stack_in.empty())
            max = stack_out_max.top();
        // Вариант с числами в обоих стеках
        else
            max = std::max(stack_out_max.top(), stack_in_max.top());

        std::cout << max << " "; // печатаем максимум окна;
        // удаляем число из выходного стека
        stack_out.pop();
        stack_out_max.pop();

        // Добавляем во входной стек число из очереди(его максимум),
        // если в очереди что-то есть. Иначе - выход из цикла;
        if (queue.empty())
            break;
        else{
            int a = queue.front();
            stack_in.push(a);
            if (stack_in_max.empty())
                stack_in_max.push(a);
            else
                stack_in_max.push(std::max(stack_in_max.top(), a));
            queue.pop();
        }
    }
    std::cout << std::endl;

    return 0;
}