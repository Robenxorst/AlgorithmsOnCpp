// Реализовать стек с поддержкой максимума.
// При команде max необходимо выдавать текущий максимум.
// Обрабатывать другие команды(top, pop, push) не требуется!

// Идея - зачем нам реализовывать сам стек,
// если можно обойтись одним стеком максимумов?

#include <iostream>
#include <stack>

int main(){
    int count; // количество команд на входе стека
    std::cin >> count;
    std::stack <int> stack;
    // стек максимумов - на вершине всегда лежит максимальное число;
    int max;

    for (int i = 0; i < count; i++){
        std::string command;
        std::cin >> command;

        if (command == "push"){
            int x;
            std::cin >> x;
            if (stack.empty())
                max = x;
            else
                max = std::max(stack.top(), x);
            stack.push(max);
        }

        if (command == "pop"){
            if (stack.empty())
                continue;
            else
                stack.pop();
        }

        if (command == "max"){
            if (stack.empty())
                std::cout << 0 << std::endl;
            else
                std::cout << stack.top() << std::endl;
        }

        }

    return 0;
}
