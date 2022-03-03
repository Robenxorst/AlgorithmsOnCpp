#include <iostream>
#include <algorithm>// swap
#include <vector>
// библиотека оценки по времени
#include "TimeDuration.hpp"
// библиотеки для GetRandomNumber
#include <cstdlib> // нужен для вызова функций rand(), srand()
#include <ctime> // нужен для вызова функции time()

//В первой строке задано два целых числа n и m — количество отрезков
// и точек на прямой, соответственно.
// Следующие n строк содержат по два целых числа a_i
//  и b_i(a_i <= b_i) - координаты концов отрезков.
// Последняя строка содержит m целых чисел — координаты точек.
// Все координаты не превышают 10^8
//  по модулю. Точка считается принадлежащей отрезку,
//  если она находится внутри него или на границе.
//  Для каждой точки в порядке появления во вводе выведите,
//  скольким отрезкам она принадлежит.

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
// Функция хорошо и грамотно работает
int GetRandomNumber(const int &min, const int &max)
{
    // Установить генератор случайных чисел
    srand(time(NULL));

    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);

    return num;
}

int MidThird(std::vector <int> &A, const int &left, const int &right){
    int x = A[left];
    int y = A[(right + left)/2];
    int z = A[right];
    int min =  ( x<y && x<z )?x:(y<z?y:z);
    int max =  ( x>y && x>z )?x:(y>z?y:z);

    int m = ((x + y + z) - min - max);
    if (x == m)
        return left;
    if (y == m)
        return (right + left)/2;

    return right;
}

void PrintArray(std::vector <int> &A){
    int c = 0;
    // распечатка полученного массива
    while (c != A.size()){
        std::cout << A[c] << " ";
        c++;
    }
    std::cout << std::endl;
}
// правильная реализация разбиения на три части по лекциям Олимпиадного программирования
std::vector <int> Partition1 (std::vector <int> &A, const int &left, const int &right){
    // массив разбивается на три части: < x , > x, = x;
    std::vector <int> res;
    int rand = GetRandomNumber(left, right);
    int x = A[rand]; // выбрали опорный элемет как рандомный
    std::cout << "x mid :" << x << std::endl;


    int i = left;
    int j = right;
    // идем по массиву с двух сторон
    // - с начала и с конца
    // до тех пор, пока i не будет правве j
    while ( i <= j){
        while(A[i] < x){// после цикла i указывает на элемент >= x
            i += 1;
        }
        while(A[j] > x){// j указывает на элемент <= x
            j -= 1;
        }
        if (i <= j){
            std::swap(A[i], A[j]);
            i += 1;
            j -= 1;
        }
    }
    PrintArray(A);// распечатка полученного массива
    res.push_back(j);
    res.push_back(i);
    if ( (right - i) > (j - left)) // размер правого массива больше
        res.push_back(1);
    else // размер левого массива боольше
        res.push_back(0);
    return res; // возвращаем позиции начала и конца блока с x в массиве
}

// Старая реализация функции Partition по Степику
// выбирает определенный опорный элемент
// и ставит его на нужное место в массиве А,
// возвращая его позицию в данном массиве(массив разбивается на две части);
int Partition0 (std::vector <int> &A, const int &left, const int &right){
    int mid = MidThird(A, left, right);
    //int rand = getRandomNumber(left, right);
    std::swap(A[left], A[mid]);
    int x = A[left];
    std::cout << "x mid :" << x << std::endl;
    // опорный элемент - медиана из трех чисел массива

    int j = left;
    int i = left + 1;
    // массив разбивается на три части: < x , > x, = x;
    while (i <= right) {
        // двигаемся слево направо по массиву,
        // сравнивая каждый элемент с опорным

        if (A[i] <= x) { // если элемент меньше x
            j += 1;
            std::swap(A[j], A[i]);
        }
        i++;
    }
    std::swap(A[left], A[j]); // ставим x на его законное место
    PrintArray(A);
    return j; // возвращаем позицию x в массиве;
}

void QuickSort(std::vector <int> &A, int &left, int &right, const int &Elimination){
    if (left >= right)
        return ;// если на входе пустой или единичный массив
        // избавление от рекурсии правого вызова
        // Elimination = 1 - элиминируем правый вызов рекурсии, 0 - левый;
        if (Elimination == 1){ //размер правого массива больше
        // избавляемся от правого рекурсивного вызова
            while (left < right){
                std::vector <int> pos = Partition1(A, left, right); // операция разделения нашего массива на части
                // pos[0] = j; pos[1] = i; pos[2] = Elimination;
                std::cout << "j = " << pos[0] << " " << "i = " << pos[1] << std::endl;
                QuickSort(A, left, pos[0], pos[2]); //сортируем левую часть
                left = pos[1];
            }
        }
        else if (Elimination == 0){// размер левого массива больше
            // избавляемся от левой рекурсии
            while (left < right){
                std::vector <int> pos = Partition1(A, left, right); // операция разделения нашего массива на части
                // pos[0] = j; pos[1] = i; pos[2] = Elimination;
                std::cout << "j = " << pos[0] << " " << "i = " << pos[1] << std::endl;
                QuickSort(A, pos[1], right, pos[2]); //сортируем левую часть
                right = pos[0];
            }
        }
}

// Функция сортировки написанная на Cи
void quickSort(std::vector <int> &numbers, int left, int right)
{
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    int rand = GetRandomNumber(left, right);
    std::swap(numbers[left], numbers[rand]);
    std::cout << "x rand :" << numbers[left] << std::endl;
//    int mid = MidThird(numbers, left, right);
//    std::swap(numbers[left], numbers[mid]);
//    std::cout << "x mid :" << numbers[left] << std::endl;
    int pivot = numbers[left]; // разрешающий элемент

    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            left++; // сдвигаем левую границу вправо
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            right--; // сдвигаем правую границу влево
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    PrintArray(numbers);
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}

// Тесты исключительно на быструю сортировку

//int main(){
//    TimeDuration ld("identifier");
//    std::vector <int> array;
//    size_t n;// количество элементов в массиве;
//    std::cin >> n;
//
//    while (n > 0) {
//        int temp;
//        std::cin >> temp;
//        array.push_back(temp);
//        n--;
//    }
//
//    int left = 0; // начальный левый элемент
//    int right = static_cast<int>(array.size()) - 1; // начальный правый элемент
//    const int e = 1;
//    QuickSort(array, left, right, e); // в сортировку отправляется
//    // весь массив на начальном этапе
//    PrintArray(array);
//
//    return 0;
//}

int SearchX(const std::vector <int> &X, const int &Key){
    int N = 0;

    int i = 0;
    while (i < X.size()){
        if (X[i] <= Key)
           N++;
        i++;
    }

    std::cout << "This is N: " << N << std::endl;
    return N;
}

int SearchY(const std::vector <int> &Y, const int &Key){
    int M = 0;

    int i = 0;
    while (i < Y.size()){
        if (Y[i] < Key)
            M++;
        i++;
    }

    std::cout << "This is M: " << M << std::endl;
    return M;
}

int main(){
    TimeDuration ld("identifier");
    std::vector <int> arrX; // координаты начала отрезков
    std::vector <int> arrY; // координаты конца отрезков
    std::vector <int> arrPoint; // координаты конца точек
    std::vector <int> arrRes; // результирующий вектор
    size_t n;// количество отрезков;
    std::cin >> n;
    size_t m; // количество точек на прямой;
    std::cin >> m;

    while (n > 0) { // считываем координаты отрезков
        int x;
        std::cin >> x;
        arrX.push_back(x);
        int y;
        std::cin >> y;
        arrY.push_back(y);
        n--;
    }

    while (m > 0) { // считываем координаты точек
        int point;
        std::cin >> point;
        arrPoint.push_back(point);
        m--;
    }

    int left = 0; // начальный левый элемент
    int right = static_cast<int>(arrX.size()) - 1; // начальный правый элемент
    const int e = 1;
    QuickSort(arrX, left, right, e); // сортируем начала отрезков
    PrintArray(arrX); // распечатка массива
    QuickSort(arrY, left, right, e); // сортируем концы отрезков
    //PrintArray(arrY); // распечатка массива

    int k = 0;
    while (k < arrPoint.size()){
        int N = SearchX(arrX, arrPoint[k]);
        int M = SearchY(arrY, arrPoint[k]);
        arrRes.push_back(N - M);
        k++;
    }

    PrintArray(arrRes); // распечатка массива
    return 0;
}

// Компактное, верное , но замороченное решение
//#include <iostream>
//#include <algorithm>
//
//int main() {
//    int segment_count, point_count;
//    std::cin >> segment_count >> point_count;
//    std::vector<int> segments_begins(segment_count);
//    std::vector<int> segments_ends(segment_count);
//    for(auto begin = segments_begins.begin(), end = segments_ends.begin();
//        segment_count; --segment_count, ++begin, ++end)
//        std::cin >> *begin >> *end;
//
//    std::sort(segments_begins.begin(), segments_begins.end());
//    std::sort(segments_ends.begin(), segments_ends.end());
//
//    while(point_count--) {
//        int point;
//        std::cin >> point;
//        auto less = std::lower_bound(segments_ends.begin(), segments_ends.end(), point)
//                    - segments_ends.begin();
//        auto greater = std::upper_bound(segments_begins.begin(), segments_begins.end(), point)
//                       - segments_begins.begin();
//        std::cout << greater - less << " ";
//    }
//    std::cout << std::endl;
//    return 0;
//}