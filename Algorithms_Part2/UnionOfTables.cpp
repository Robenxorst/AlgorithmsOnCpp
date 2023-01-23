// Объеденение таблиц:
// На входе n - количество таблиц и m - кол во команд
// Далее следует массив с количеством записей в каждой таблице.
// За ним соответствующие запросы;

#include <iostream>
#include <vector>
#include <queue>

// Определяем идентификатор множества
size_t Find(size_t i, std::vector<size_t> *parent){
    if (i != (*parent).at(i))
        // используем эвристический подход
        // для автоматического сжатия путей поиска
        (*parent).at(i) = Find((*parent).at(i), parent);
    return (*parent).at(i);
}

// Операция обьединения множеств
// Всегда подвешиваем source к dest
void Union(size_t dest, size_t source, std::vector<size_t> *parent,
           std::vector<size_t> *tables, size_t *max){
    size_t dest_id = Find(dest, parent);
    size_t source_id = Find(source, parent);
    if (dest_id != source_id){
        // Если сумма двух объединяемых элементов больше максимума, то меняем его
        if ( *max < (*tables).at(dest_id)+(*tables).at(source_id))
            *max = (*tables).at(dest_id)+(*tables).at(source_id);
        //теперь в dest_id будет лежать новое значение
        (*tables).at(dest_id) += (*tables).at(source_id);
        // прописываем ссылку из source в dest;
        (*parent).at((*parent).at(source)) = (*parent).at(dest);
    }
}

int main(){
    size_t n, m;
    std::cin >> n >> m;
    // вектор таблиц;
    std::vector<size_t> tables;
    // вектор вершин деревьев(ID множества - это корень дерева);
    std::vector<size_t> parent;
    for (size_t i = 0; i < n; i++){
        size_t temp;
        std::cin >> temp;
        tables.push_back(temp);
        // Автоматически создаем множества для каждого элемента;
        parent.push_back(i); // parent[i] = i;
    }
    // вектор команд;
    std::queue <std::vector <size_t>> commands;
    for (size_t i = 0; i < m; i++){
        size_t dest, source;
        std::cin >> dest >> source;
        std::vector<size_t> temp;
        // массив начинается с 0;
        temp.push_back(dest-1);
        temp.push_back(source-1);
        commands.push(temp);
    }

    // Определим максимальный элемент в изначальном массиве
    size_t max = *max_element(tables.begin(), tables.end());
    while (!commands.empty()){
        size_t dest = commands.front().at(0);
        size_t source = commands.front().at(1);
        commands.pop();
        Union(dest, source, &parent, &tables, &max);
        std::cout << max << std::endl;//в любом случае распечатываем max
    }

    return 0;
}