// Необходимо составить
// алгоритм для параллельной обработки запросов несколькими процессорами.
// На вход подается n - количество процессоров и m - число задач,
// а так же массив array[m] содержащий в себе время выполнения одной задачи;

#include <iostream>
#include <vector>

int LeftChild(int i){
    return 2 * i + 1;
}

int RightChild(int i){
    return 2 * i + 2;
}

// Метод утапливания элемента;
void ShiftDown(std::vector <std::vector <long long>> *heap, int i, int size){
    int MinIndex = i;

    // сравниваем с левым элементом
    int l = LeftChild(i);
    if ( l <= size && (*heap).at(l).at(0) < (*heap).at(MinIndex).at(0))
        MinIndex = l;
    // в случае равенства по времени утапливаем по минимальному номеру процессора
    else if (l <= size && (*heap).at(l).at(0) == (*heap).at(MinIndex).at(0))
        if ((*heap).at(l).at(1) < (*heap).at(MinIndex).at(1))
            MinIndex = l;

    // сравниваем с правым элементом
    int r = RightChild(i);
    if (r <= size && (*heap).at(r).at(0) < (*heap).at(MinIndex).at(0))
        MinIndex = r;
    else if (r <= size && (*heap).at(r).at(0) == (*heap).at(MinIndex).at(0))
        if ((*heap).at(r).at(1) < (*heap).at(MinIndex).at(1))
            MinIndex = r;

    if (i != MinIndex){
        // перестановка стаканом;
        std::vector <long long> temp;
        temp.reserve(2);
        temp = (*heap).at(i);
        (*heap).at(i) = (*heap).at(MinIndex);
        (*heap).at(MinIndex) = temp;

        // Топим полученный элемент дальше
        ShiftDown(heap, MinIndex, size);
    }
}

void Build_Heap(int n, int m, const std::vector <long long> array){
    // создаем вектор размера n с двумя значениями внутри каждой ячейки;
    std::vector <std::vector <long long>> heap;
    for (int i = 0; i < n; i++){
        std::vector <long long> a;
        a.push_back(0); // первый элемент отвечает за время начала работы процессора;
        a.push_back(i); // второй элемент - номер процессора;
        heap.push_back(a);
    }
    int size = n - 1; // номер максимального элемента в куче

    for (int i = 0; i < m; i++){
        // распечатка вершины кучи
        std::cout << heap.front().back() << " " << heap.front().front() << std::endl;

        // прибавляем время выполнения нашей задачи к вершине;
        heap.at(0).at(0) += array[i];

        // утапливаем вершину кучи
        ShiftDown(&heap, 0, size);
    }
}

int main(){
    int n; //число процессоров
    int m; // число задач
    std::cin >> n >> m;
    std::vector <long long> array;

    for (int i = 0; i < m; i++){
        long long temp;
        std::cin >> temp;
        array.push_back(temp);
    }

    Build_Heap(n, m, array);
    return 0;
}
