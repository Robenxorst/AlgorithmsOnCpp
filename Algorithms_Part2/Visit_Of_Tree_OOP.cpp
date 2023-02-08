// Построить in-order, pre-order и post-order обходы данного
// двоичного дерева.
// Вход. Двоичное дерево.
// Выход. Все его вершины в трёх разных порядках: in-order,
// pre-order и post-order.;

// In-order обход соответствует следующей рекурсивной процедуре,
// получающей на вход корень v текущего поддерева:
// произвести рекурсивный вызов для v.left, напечатать v.key,
// произвести рекурсивный вызов для v.right. Pre-order обход: напечатать v.key,
// произвести рекурсивный вызов для v.left, произвести рекурсивный вызов для
// v.right. Post-order: произвести рекурсивный вызов для v.left,
// произвести рекурсивный вызов для v.right, напечатать v.key.


// Пример:
// Вход:
//5
//4 1 2
//2 3 4
//5 -1 -1
//1 -1 -1
//3 -1 -1

// Выход:
//1 2 3 4 5
//4 2 1 3 5
//1 3 2 5 4

#include <iostream>
#include <vector>

class Binary_Tree{
public:
    // Пользовательский класс - вершина дерева;
    struct List{
        // конструктор нашего класса
        explicit  List(int key = 0, int left = 0, int right = 0) : key(key), left(left), right(right) {}
        // Деструктор по дефолту
        ~List() = default;

        int key;
        int left;
        int right;
    };

    // Конструктор нашего класса дерева - на вход приходит лишь один аргумент,
    // т е нужен explicit
    explicit Binary_Tree(size_t n) : tree_size_(n) {
        // создание массива из List
        for (size_t i = 0; i < tree_size_; i++){
            int key;
            int left;
            int right;
            std::cin >> key >> left >> right;
            ar_tree.push_back(List(key, left, right));
        }
    }
    ~Binary_Tree() = default;

    void GetAnswer() {
        In_order(0);
        std::cout << std::endl;
        Pre_order(0);
        std::cout << std::endl;
        Post_order(0);
        std::cout << std::endl;
    }

    void In_order(const int &number){
        // Левая рекурсия
        if (ar_tree.at(number).left != -1)
            In_order(ar_tree.at(number).left);
        // Распечатка ключа;
        std::cout << ar_tree.at(number).key << " ";
        // Правая рекурсия
        if (ar_tree.at(number).right != -1)
            In_order(ar_tree.at(number).right);
    }

    void Pre_order(const int &number){
        // Распечатка ключа;
        std::cout << ar_tree.at(number).key << " ";
        // Левая рекурсия
        if (ar_tree.at(number).left != -1)
            Pre_order(ar_tree.at(number).left);
        // Правая рекурсия
        if (ar_tree.at(number).right != -1)
            Pre_order(ar_tree.at(number).right);
    }

    void Post_order(const int &number){
        // Левая рекурсия
        if (ar_tree.at(number).left != -1)
            Post_order(ar_tree.at(number).left);
        // Правая рекурсия
        if (ar_tree.at(number).right != -1)
            Post_order(ar_tree.at(number).right);
        // Распечатка ключа;
        std::cout << ar_tree.at(number).key << " ";
    }

private:
    size_t tree_size_;
    std::vector <List> ar_tree;
};

int main(){
    int n; // количество вершин в нашем дереве;
    std::cin >> n;

    // Создали экземпляр класса
    Binary_Tree Object(n);
    // Вызвали его метод;
    Object.GetAnswer();

    return 0;
}