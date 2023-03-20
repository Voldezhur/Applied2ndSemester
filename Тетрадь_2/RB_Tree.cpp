// КЧ Дерево


#include <iostream>
#include <cmath>

// КЧ дерево
struct RB_tree
{
    // Структура узла АВЛ дерева
    struct Node
    {
    public:
        int val;

        Node* left;
        Node* right;
        Node* parent;
        
        bool isBlack;

        // Конструктор
        Node(int _val) : val(_val), left(nullptr), right(nullptr), parent(nullptr), isBlack(false){}
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
            std::cout << _node->val << '(' << (_node->isBlack ? "black" : "red") << ')' << std::endl;

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
            RB_tree Left;
            Left.root = root->left;

            return Left.Find(_val);
        }

        // Иначе, если больше, идем вправо
        else if(_val > root->val)
        {
            RB_tree Right;
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
               
        // Перецепление указателей правого поддерева левого поддерева опорного узла
        Node* T2 = _node->left->right;
        _node->left->right = _node;
        _node->left = T2;
    }
    
    // Правый поворот относительно опорного узла _node
    void rTurn(Node* _node)
    {
        // Перецепление указателей родителей
        _node->right->parent = _node->parent;
        _node->parent = _node->right;
                
        // Перецепление указателей левого поддерева правого поддерева опорного узла
        Node* T2 = _node->right->left;
        _node->right->left = _node;
        _node->right = T2;
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
            RB_tree Left;
            Left.root = par->left;
            int a = Left.Depth(Left.root, d);

            // Проход по правой ветви
            RB_tree Right;
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

    // Красно-красное нарушение
    void RR_Violation(Node* _node)
    {
        // Если родитель слева своего родителя
        if(_node->parent->val < _node->parent->parent->val)
        {
            // Случай 1
            if(!_node->parent->isBlack && !_node->parent->parent->right->isBlack)
            {
                // Перекраска отца и дяди
                _node->parent->isBlack = true;
                _node->parent->parent->right->isBlack = true;

                // Перекраска деда и проверка на КК нарушениие, если дед не корень
                if(_node->parent->parent->parent)
                {
                    _node->parent->parent->isBlack = false;
                    
                    // Проверка на КК нарушение
                    Node* D = _node->parent->parent;
        
                    if(D->parent && D->parent->parent && D->parent->parent->right && D->parent->parent->left)
                    {
                        RR_Violation(_node->parent->parent);
                    }
                }
            }

            // Случай 2 и 3
            if(!_node->parent->isBlack && _node->parent->parent->right->isBlack)
            {
                // Если цепочка образует линию - случай 2
                if(_node->val < _node->parent->val)
                {
                    // Перекрашивание
                    _node->parent->parent->isBlack = false;
                    _node->parent->isBlack = true;

                    // Поворот направо относительно деда
                    rTurn(_node->parent->parent);
                }

                // Если цепочка образует угол - случай 3
                else
                {
                    // Перекрашивание
                    _node->isBlack = true;
                    _node->parent->parent->isBlack = false;

                    // Двойной поворот
                    lTurn(_node->parent);
                    rTurn(_node->parent);
                }
            }
        }

        // Если родитель справа своего родителя
        else
        {
            // Случай 1
            if(!_node->parent->isBlack && !_node->parent->parent->left->isBlack)
            {
                // Перекраска отца и дяди
                _node->parent->isBlack = true;
                _node->parent->parent->left->isBlack = true;

                // Перекраска деда и проверка на КК нарушениие, если дед не корень
                if(_node->parent->parent->parent)
                {
                    _node->parent->parent->isBlack = false;
                    
                    // Проверка на КК нарушение
                    Node* D = _node->parent->parent;
        
                    if(D->parent && D->parent->parent && D->parent->parent->right && D->parent->parent->left)
                    {
                        RR_Violation(_node->parent->parent);
                    }
                }
            }

            // Случай 2 и 3
            else if(!_node->parent->isBlack && _node->parent->parent->left->isBlack)
            {
                // Если цепочка образует линию - случай 2
                if(_node->val < _node->parent->val)
                {
                    // Перекрашивание
                    _node->parent->parent->isBlack = false;
                    _node->parent->isBlack = true;

                    // Поворот направо относительно деда
                    lTurn(_node->parent->parent);
                }

                // Если цепочка образует угол - случай 3
                else
                {
                    // Перекрашивание
                    _node->isBlack = true;
                    _node->parent->parent->isBlack = false;

                    // Двойной поворот
                    rTurn(_node->parent);
                    lTurn(_node->parent);
                }
            }
        }
    }

    // Добавление элементов в дерево
    void Add(int _val)
    {
        bool added = false; // Флаг для проверки того, добавили ли узел в дерево

        // Если узел пустой: вставить в узел
        if(root == nullptr)
        {
            Node* p = new Node(_val);
            p->isBlack = true;
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

                added = true;
            }

            // Иначе
            else
            {
                RB_tree Left;
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

                added = true;
            }

            // Иначе
            else
            {
                RB_tree Right;
                Right.root = root->right;
                
                Right.Add(_val);
            }
        }

        // Проверка на КК нарушение
        if(added)
        {
            Node* D = Find(_val);
            
            if(D->parent && D->parent->parent && D->parent->parent->right && D->parent->parent->left)
            {
                RR_Violation(Find(_val));
            }
        }
    }
};


int main()
{
    RB_tree A;

    A.Add(-5);
    A.Add(-7);
    A.Add(3);
    A.Add(6);
    A.Add(1);
    A.Add(23);
    A.Print();
}