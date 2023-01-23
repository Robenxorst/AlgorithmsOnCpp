//Вычислить высоту корневого дерева,
// которое задано ,как список
// элементов parent[i], т е родителей i-ых вершин

//Быстрый способ сверху вниз(модификация с помощью доп массива)//
// 1. Заполняем массив глубин;
// 2. Возвращаем максимальное значение из этого массива;
#include <iostream>
#include <vector>

void Height(int i, int *depth, const std::vector<int> &array){
    //Если значение было уже рассчитано
    if (depth[i] != 0)
        return;

    if (array[i] == -1) {
        depth[i] = 1;
        return;
    }// вершина является корнем

    if (depth[array[i]] == 0)
        // Если глубина родителя не известна, то вычисляем ее;
        Height(array[i], depth, array);

    // Увеличиваем значение, зная глубину родителя
    depth[i] = depth[array[i]] + 1;
}

int CreateArrayOfDepth(const std::vector<int> &array){
    //Создаем массив необходимой длины, заполненный нулями
    int depth[array.size()];

    for (int i = 0; i < array.size(); i++)
       depth[i] = 0;

    // Для каждой вершины заполняем массив
    for (int i = 0; i < array.size(); i++)
        Height (i, depth, array) ;

    // Распечатываем полученный массив
    for(auto c : depth)
        std::cout << c << " ";
    std::cout << std::endl;

    // Ищем максимальное значение в полученном массиве
    int high = depth[0];

    for (auto c : depth)
        if (high < c)
            high = c;
    return high;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<int> array;

    for (int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        array.push_back(temp);
    }

    int result = CreateArrayOfDepth(array);
    std::cout << result << std::endl;
    return 0;
}