// Реализовать алгоритм для
// определения правильности расположения скобок в коде

#include <algorithm>
#include <iostream>
#include <stack>

// Реализация через структуру стека

int TrueBrackets(std::string &str){
    std::stack <char> stack;
    std::stack <int> DopNumber;
    DopNumber.push(str.length());

    for( int i = 0; i < str.length(); i++) {
        //рассмотрим закрывающие скобки
        if ( str[i] == ')'){
            if ( !stack.empty() && stack.top() == '('){
                stack.pop();
                DopNumber.pop();
                continue;
            }
            else
                return i+1;
        }
        else if ( str[i] == ']'){
            if ( !stack.empty() && stack.top() == '['){
                stack.pop();
                DopNumber.pop();
                continue;
            }
            else
                return i+1;
        }
        else if ( str[i] == '}'){
            if ( !stack.empty() && stack.top() == '{'){
                stack.pop();
                DopNumber.pop();
                continue;
            }
            else
                return i+1;
        }
        else if ( str[i] == '{' || str[i] == '(' || str[i] == '[') {
            // открывающие скобки кладем в стек, запоминая их номер
            stack.push(str[i]);
            DopNumber.push(i+1);
        }
        else // все остальные символы пропускаем
            continue;
    }

    if (stack.empty())
        return -1;// для случая успеха;
    else// если стек не пуст,
    // то вернем номер последнего открывающего символа
        return DopNumber.top();
}

int main(){
    std::string str;
    std::cin >> str;

    int res = TrueBrackets(str);
    if (res == -1)
        std::cout << "Success" << std::endl;
    else
        std::cout << res << std::endl;

    return 0;
}