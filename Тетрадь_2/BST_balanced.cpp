// Сбалансированное двочиное дерево поиска


#include <iostream>
#include <cmath>

// АВЛ дерево
struct AVL_tree
{
    // Структура узла АВЛ дерева
    struct Node
    {
    public:
        int val;

        Node* left;
        Node* right;
        Node* parent;
        
        int balance; 

        // Конструктор
        Node(int _val) : val(_val), left(nullptr), right(nullptr), parent(nullptr), balance(0){}
    };

    // Корень
    Node* root = nullptr;

    // Вывод дерева
    void Print(const std::string prefix, Node* _node, bool isLeft)
    {   
        if(_node != nullptr)
        {
            std::cout << prefix << (isLeft ? "├──" : "└──");

            // Вывод значения узла и количества повторений
            std::cout << _node->val << '(' << _node->balance << ')' << std::endl;

            // Рекурсивный вывод остальных уровней дерева
            // Слева
            Print(prefix + (isLeft ? "|    " : "     "), _node->left, true);

            // Справа
            Print(prefix + (isLeft ? "|    " : "     "), _node->right, false);
        }
    }
    // Перегрузка метода вывода
    void Print()
    {
        Print("", root, false);
    }

    // Поиск узла дерева по значению
    Node* Find(int _val)
    {
        // Если корень - пустой указатель
        if(root == nullptr)
        {
            return nullptr;
        }
        
        // Иначе, если корень - узел, который искали
        else if(_val == root->val)
        {
            return root;
        }

        // Иначе, если меньше, идем влево
        else if(_val < root->val)
        {
            AVL_tree Left;
            Left.root = root->left;

            return Left.Find(_val);
        }

        // Иначе, если больше, идем вправо
        else if(_val > root->val)
        {
            AVL_tree Right;
            Right.root = root->right;

            return Right.Find(_val);
        }

        return nullptr;
    }

    // Определение глубины дерева
    int depth = 0;
    int Depth(Node* par, int d)
    {
        // Если корень пустой - дошли до листа, возврат
        if(par == nullptr)
        {
            return d - 1;
        }
        
        // Иначе - добавляем 1 к глубине, идем дальше
        else 
        {
            d++;

            // Проход по левой ветви
            AVL_tree Left;
            Left.root = par->left;
            int a = Left.Depth(Left.root, d);

            // Проход по правой ветви
            AVL_tree Right;
            Right.root = par->right;
            int b = Right.Depth(Right.root, d);

            // Возврат наибольшей глубины
            return(a > b ? a : b);
        }
    }
    // Перегрузка метода поиска глубины
    int Depth(Node* par)
    {
        return Depth(par, depth);
    }

    /* 
    Идем снизу вверх, пересчитываем баланс.
    Если изменился, идем дальше вверх
    Если модуль больше 2, перестройка 
    */
    void UpdateBalance(Node* _node)
    {
        //  Обновление баланса
        int tempBalance = _node->balance;
        int balance = Depth(_node->right) - Depth(_node->left);
        _node->balance = balance;

        // если баланс изменился - продолжаем проход  вверх
        if(tempBalance != balance)
        {
            if(_node->parent)
            {
                UpdateBalance(_node->parent);
            }
        }

        else
        {
            // Первый случай
            if(balance == -2 && _node->left->balance == -1 && (Depth(_node->left->left) == Depth(_node->left->right) && Depth(_node->left->left) == Depth(_node->right)))
            {
                // Перецепление указателей родителей
                _node->left->parent = _node->parent;
                _node->parent = _node->left;
                // Перецепление указателей правого поддерева левого поддерева опорного узла
                Node* T2 = _node->left->right;
                _node->left->right = _node;
                _node->left = T2;
            }

            // Второй случай - симметричный первому
            if(balance == -2 && _node->right->balance == -1 && (Depth(_node->right->right) == Depth(_node->right->left) && Depth(_node->right->right) == Depth(_node->left)))
            {
                // Перецепление указателей родителей
                _node->right->parent = _node->parent;
                _node->parent = _node->right;
                // Перецепление указателей левого поддерева правого поддерева опорного узла
                Node* T2 = _node->right->left;
                _node->right->left = _node;
                _node->right = T2;
            }

            // Обновление баланса
            UpdateBalance(_node);
        }
    }

    // Добавление элементов в дерево
    void Add(int _val)
    {
        // Если узел пустой: вставить в узел
        if(root == nullptr)
        {
            Node* p = new Node(_val);
            root = p;
        }

        // Если уже есть такой
        else if(_val == root->val)
        {
            return;
        }

        // Иначе если новый узел меньше:
        else if(_val < root->val)
        {   
            // Если левый узел пустой
            if(root->left == nullptr)
            {
                root->left = new Node(_val);
                root->left->parent = root;
            }

            // Иначе
            else
            {
                AVL_tree Left;
                Left.root = root->left;
                
                Left.Add(_val);
            }
        }

        // Иначе если новый узел больше:
        else if(_val > root->val)
        {
            // Если правый узел пустой
            if(root->right == nullptr)
            {
                root->right = new Node(_val);
                root->right->parent = root;
            }

            // Иначе
            else
            {
                AVL_tree Right;
                Right.root = root->right;
                
                Right.Add(_val);
            }
        }
    }

    // Добавление новых элементов, обновление баланса и перестройка при необходимости
    void AddAndRebalance(int _val)
    {
        Add(_val);
        
        Node* nodeParent = Find(_val)->parent;
        
        if(nodeParent)
        {
            UpdateBalance(nodeParent);
        }
    }

};


int main()
{
    AVL_tree A;

    A.AddAndRebalance(-5);
    A.AddAndRebalance(3);
    A.AddAndRebalance(6);
    A.AddAndRebalance(7);
    A.AddAndRebalance(23);

    A.Print();
}