//Вычислить высоту корневого дерева,
// которое задано, как список
// элементов parent[i], т е родителей i-ых вершин

//Медленный способ снизу вверх(разобран на лекции)//
#include <iostream>
#include <vector>
#include <unordered_map> // список, состоящий из пар ключ-значение;

int Height(int r, const std::vector<int> &array){
    int res = 1;

    for (int i = 0; i < array.size(); i++) {
        if (array[i] == r)
            res = std::max(res, 1+Height(i, array));
    }
    return res;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<int> array;
    int core;

    for (int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        if (temp == -1)
            core = i;
        array.push_back(temp);
    }
    std::cout << core << std::endl;

    int result = Height(core, array);
    std::cout << result << std::endl;
    return 0;
}