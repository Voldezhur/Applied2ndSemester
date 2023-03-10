// АВЛ дерево


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

    // Левый поворот относительно опорного узла _node
    void lTurn(Node* _node)
    {
        // Перецепление указателей родителей
        _node->left->parent = _node->parent;
        _node->parent = _node->left;

        if(_node->left->parent)
        {
            if(_node->val < _node->left->parent->val)
            {
                _node->left->parent->left = _node->left;
            }
            else
            {
                _node->left->parent->right = _node->left;
            }
        }

        // Перецепление указателей правого поддерева левого поддерева опорного узла
        Node* T2 = _node->left->right;
        _node->left->right = _node;
        _node->left = T2;

        if(_node == root)
        {
            root = _node->parent;
        }
    }
    
    // Правый поворот относительно опорного узла _node
    void rTurn(Node* _node)
    {
        // Перецепление указателей родителей
        _node->right->parent = _node->parent;
        _node->parent = _node->right;
   
        if(_node->right->parent)
        {
            if(_node->val < _node->right->parent->val)
            {
                _node->right->parent->left = _node->right;
            }
            else
            {
                _node->right->parent->right = _node->right;
            }
        }

        // Перецепление указателей левого поддерева правого поддерева опорного узла
        Node* T2 = _node->right->left;
        _node->right->left = _node;
        _node->right = T2;

        if(_node == root)
        {
            root = _node->parent;
        }
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
            return;
        }

        // Первый случай
        if(balance == -2 && _node->left->balance == -1 && (Depth(_node->left->left) - 1 == Depth(_node->left->right) && Depth(_node->left->left) - 1 == Depth(_node->right)))
        {
            lTurn(_node);
        }

        // Второй случай - симметричный первому
        else if(balance == 2 && _node->right->balance == 1 && (Depth(_node->right->right) - 1 == Depth(_node->right->left) && Depth(_node->right->right) - 1 == Depth(_node->left)))
        {
            rTurn(_node);
        }

        // Третий случай - двойной поворот
        else if(balance == -2 && _node->left->balance == 1 && _node->left->right->balance == -1)
        {
            if(Depth(_node->right) == Depth(_node->left->left) == Depth(_node->left->right->left) == Depth(_node->left->right->right) + 1)
            {
                lTurn(_node->left);
                rTurn(_node);
            }
        }

        // Четвертый случай - симметрично третьему
        else if(balance == 2 && _node->right->balance == -1 && _node->right->left->balance == 1)
        {
            if(Depth(_node->left) == Depth(_node->right->right) == Depth(_node->right->left->right) == Depth(_node->right->left->left) + 1)
            {
                rTurn(_node->right);
                lTurn(_node);
            }
        }

        // Обновление баланса
        UpdateBalance(_node);
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

    // Удаление узла по значению
    void Remove(int _val)
    {
        // Поиск нужного узла
        Node* removing = this->Find(_val);

        // Если такого нет
        if(!removing)
        {
            return;
        }

        // Найти родителя удаляемого листа
        Node* parent = Find(_val)->parent;

        // 1: Если у узла нет потомков
        if(removing->left == nullptr && removing->right == nullptr)
        {
            // Если он слева, приравнять левого потомка к пустому указателю
            if(parent->left && parent->left->val == _val)
            {
                parent->left = nullptr;
            }

            // Если он справа, приравнять правого потомка к пустому указателю
            else
            {
                parent->right = nullptr;
            }

            delete removing;
        }
    
        // 2: Если у узла есть оба потомка и у левого есть правое поддерево
        else if(removing->left && removing->right && removing->left->right)
        {
            // Найти максимальный узел правого поддерева
            Node* max = removing->left->right;

            while(max->right)
            {
                max = max->right;
            }

            // Вставить максимальный узел вместо удаляемого, затем удалить оставшийся максимальный узел через метод Remove()
            int value = max->val;
            Remove(value);
            removing->val = value;
        }
    
        // 3: Если у узла есть оба потомка и у левого нет правого поддерева
        else if(removing->left && removing->right)
        {
            // Вставить корень левого поддерева на место удаляемого узла
            int value = removing->left->val;
            Remove(value);
            removing->val = value;
        }

        // 4.1: Если у узла есть только правый потомок
        else if(removing->left && !removing->right)
        {
            // Если он слева, приравнять левого потомка к пустому указателю
            if(parent->left && parent->left->val == _val)
            {
                parent->left = removing->right;
            }

            // Если он справа, приравнять правого потомка к пустому указателю
            else
            {
                parent->right = removing->right;
            }

            delete removing;
        }

        // 4.2: Если у узла есть только левый потомок
        else if(!removing->left && removing->right)
        {
            // Если он слева, приравнять левого потомка к пустому указателю
            if(parent->left && parent->left->val == _val)
            {
                parent->left = removing->left;
            }

            // Если он справа, приравнять правого потомка к пустому указателю
            else
            {
                parent->right = removing->left;
            }

            delete removing;
        }
    }

};


int main()
{
    AVL_tree A;

    // Заполнение дерева элементами по возрастанию
    A.AddAndRebalance(-5);
    A.AddAndRebalance(3);
    A.AddAndRebalance(6);
    A.AddAndRebalance(7);
    A.AddAndRebalance(23);
    A.AddAndRebalance(50);
    A.AddAndRebalance(52);
    A.AddAndRebalance(70);
    A.AddAndRebalance(102);
    A.AddAndRebalance(111);

    // Вывод дерева
    A.Print();
    std::cout << '\n';

    // Удаление
    std::cout << "Нужно удалить элемент?\ny/n\n";
    char inp;
    std::cin >> inp;

    if(inp == 'y' or inp == 'Y')
    {
        std::cout << "Какой элемент удалить? (по значению)\n";
        int n;
        std::cin >> n;
        
        A.Remove(n);    

        A.Print();
    }
}