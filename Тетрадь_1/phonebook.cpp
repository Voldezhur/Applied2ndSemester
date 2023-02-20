// Телефонная книга


#include <iostream>

// Структура Двоичного дерева поиска
struct BST
{
    // Структура узла дерева
    struct Node
    {
    public:
        int val;
        int count;

        Node* left;
        Node* right;
        
        // Конструктор
        Node(int _val) : val(_val), count(1), left(nullptr), right(nullptr){}
    };

    // Корневой узел
    Node* root = nullptr;


    // Вывод дерева
    void Print(const std::string prefix, Node* _node, bool isLeft)
    {   
        if(_node != nullptr)
        {
            std::cout << prefix << (isLeft ? "├──" : "└──");

            // Вывод значения узла и количества повторений
            std::cout << _node->val << '(' << _node->count << ')' << std::endl;

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


    // Добавление элемента в дерево
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
            root->count++;
        }

        // Иначе если новый узел меньше:
        else if(_val < root->val)
        {   
            // Если левый узел пустой
            if(root->left == nullptr)
            {
                root->left = new Node(_val);
            }

            // Иначе
            else
            {
                BST Left;
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
            }

            // Иначе
            else
            {
                BST Right;
                Right.root = root->right;
                
                Right.Add(_val);
            }
        }
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
            BST Left;
            Left.root = root->left;

            return Left.Find(_val);
        }

        // Иначе, если больше, идем вправо
        else if(_val > root->val)
        {
            BST Right;
            Right.root = root->right;

            return Right.Find(_val);
        }

        return nullptr;
    }


    // Поиск родителя по значению
    Node* FindParent(int _val)
    {
        // Если корень - пустой указатель
        if(root == nullptr)
        {
            return nullptr;
        }
        
        // Иначе, если среди потомков есть узел со значением val
        else if(root->left && root->left->val == _val || root->right && root->right->val == _val)
        {
            return root;
        }

        // Иначе, если меньше, идем влево
        else if(_val < root->val)
        {
            BST Left;
            Left.root = root->left;

            return Left.FindParent(_val);
        }

        // Иначе, если больше, идем вправо
        else if(_val > root->val)
        {
            BST Right;
            Right.root = root->right;

            return Right.FindParent(_val);
        }

        return nullptr;
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
        Node* parent = FindParent(_val);

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


    // Переменная для определения глубины
    int depth = 0;
    // Определение глубины дерева
    int Depth(int d)
    {
        // Если корень пустой - дошли до листа, возврат
        if(root == nullptr)
        {
            return d;
        }
        
        // Иначе - добавляем 1 к глубине, идем дальше
        else 
        {
            d++;

            // Проход по левой ветви
            BST Left;
            Left.root = root->left;
            int a = Left.Depth(d);

            // Проход по правой ветви
            BST Right;
            Right.root = root->right;
            int b = Right.Depth(d);

            // Возврат наибольшей глубины
            return(a > b ? a : b);
        }
    }
    // Перегрузка метода поиска глубины
    int Depth()
    {
        return Depth(depth);
    }
};


int main()
{
    
}