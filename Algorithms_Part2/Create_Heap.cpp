// Алгоритм получает на вход массив и делает
// из него МИНИМАЛЬНУЮ кучу(наверху минимальный элемент).
// На выходе имеем необходимые
// перестановки номеров элементов.


#include <iostream>
#include <vector>
#include <queue>

int LeftChild(int i){
    return 2 * i + 1;
}

int RightChild(int i){
    return 2 * i + 2;
}

// Метод утапливания элемента;
void SiftDown(long long** array, int i, const int size, int *count, std::queue<std::vector <int>> *queue){
    int MinIndex = i;
    int l = LeftChild(i);
    int r = RightChild(i);

    if ( l <= size && (*array)[l] < (*array)[MinIndex])
        MinIndex = l;
    if ( r <= size && (*array)[r] < (*array)[MinIndex])
        MinIndex = r;

    if (i != MinIndex){
        (*count)++;// увеличиваем счетчик операций
        // кладем нужные элементы в очередь
        std::vector <int> temp;
        temp.push_back(MinIndex);
        temp.push_back(i);
        queue->push(temp);

        // обмен стаканчиком;
        long long t = (*array)[i];
        (*array)[i] = (*array)[MinIndex];
        (*array)[MinIndex] = t;

        // Проверяем не надо ли утапливать элемент дальше
        // (менять со следующими детьми)
        SiftDown(array, MinIndex, size, count, queue);
    }
}

void BuildHeap(long long *array, int n, int *count, std::queue<std::vector <int>> *queue){
    int size = n-1; // номер максимального элемента в массиве

    // двигаемся с середины массива к его началу,
    // т е всплываем к вершине дерева
    for(int i = (n - 1) / 2; i != -1; i--){
        SiftDown(&array, i, size, count, queue);
    }
}

int main(){
    int n; //размер входного массива
    std::cin >> n;
    long long array[n]; // входной массив чисел
    for( int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        array[i] = temp;
    }
    std::queue<std::vector <int>> queue; // очередь с выходными элементами;

    int count = 0; // Изначально количество необходимых операций нулевое;

    BuildHeap(array, n, &count, &queue); // перестановка массива

    // распечатка результата
    std::cout << count << std::endl;
    while ( count-- > 0){
        std::vector <int> print = queue.front();
        std::cout << print.back() << " ";
        print.pop_back();
        std::cout << print.back() << std::endl;
        print.pop_back();
        queue.pop();
    }

    return 0;
}