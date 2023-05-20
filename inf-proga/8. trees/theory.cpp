#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct tree {  // структура дерево
    int inf;
    tree *left;    // указатель на левого ребенка
    tree *right;   // указатель на правого ребенка
    tree *parent;  // указатель на родителя
};

tree *node(int x) {   // создание нового узла
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void preorder (tree *tr) {   // прямой обход дерева (кор-лев-прав)
    if (tr) {
        cout << tr->inf;     // корень
        preorder(tr->left);  // левое поддерево
        preorder(tr->right); // правое поддерево
    }
}

void postorder(tree *tr) {    // обратный обход (лев-прав-корень)
    if (tr) {
        postorder(tr->left);  // левое поддерево
        postorder(tr->right); // правое поддерево
        cout << tr->inf;      // корень
    }
}

void inorder (tree *tr) {     // симметричный обход (лев-кор-прав)
    if (tr) {
        inorder(tr->left);    // левое поддерево
        cout << tr->inf;      // корень
        inorder(tr->right);   // правое поддерево
    }
}
/*
Матем. выраж. изображ. в виде дерева:
Листья - операнды, внутренние узлы - знаки операций.

Корень - самая верхняя операция. Вычисления производятся с листьев и вверх.

Прямой обход - префиксная запись (+34).
Симметричный обход - инфиксная запись (3+4).
Обратный обход - постфиксная запись (34+).
*/

tree *math_create_tree(string str) { // создание дерева математич. выражения
    tree *tr = NULL;
    for (unsigned int i = 0; i < str.length(); ++i) { // проход по строке
        tree *n = node(str[i]);
        if (str[i] == '-' || str[i] == '+') { // становится корнем
            tr->parent = n;
            n->left = tr;  // имеющееся деерво становится левым
            tr = n;
        }
        else if (str[i] == '/' || str[i] == '*') {
            if (isdigit(tr->inf)) { // если первый знак операции в выражении - корень
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else {  // добавляем справа от корня
                n->parent = tr;
                n->left = tr->right; // имеющийся элемент становится левым
                tr->right->parent = n;
                tr->right = n;
            }
        }
        else {  // цифра
            if (!tr) tr = n; // если первая цифра в выражении - становится корнем
            else {  // нет
                if (!tr->right) {  // у корня нет правого сына - становится им
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                }
                else {  // ищем операнд без правого сына
                    tree *x = tr->right;
                    while (x->right) x = x->right;
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
}

void math_postorder(tree *tr, stack<int> &a) {  // обратный обход, вычисляющий значение матем. выражения
    if (tr) {
        postorder(tr->left);
        postorder(tr->right);
        if (isdigit(tr->inf)) {  // если узел - число, записываем в стек
            int n = tr->inf - '0';
            a.push(n);
        }
        else {  // знак операции
            int b = a.top(); // извлекаем 2 последних элемента стека
            a.pop();
            int c = a.top();
            a.pop();
            if (tr->inf == '+') a.push(b+c);  // и записываем в стек результат данной операции
            if (tr->inf == '-') a.push(c-b);  
            if (tr->inf == '*') a.push(b*c);
            if (tr->inf == '/') a.push(c/b);
        }
    }
}

void math() {  // не робит нихуя
    string str;
    getline(cin, str);
    string znak = "+-/*0123456789()";
    bool flag = true;
    for (unsigned int i = 0; i < str.length(); ++i) 
        if (znak.find_first_of(str[i] == string::npos)) {  // частичная проверка на корректность
            flag = false;
            break;
        }
        if (!flag) cout << "error";
        else {
        
            tree *tr = math_create_tree(str); // создали дерево
            stack<int> a;
            math_postorder(tr, a);  // вызвали обход
            cout << a.top();  // в стеке один элемент - извлекаем его
            a.pop();
        }
}

/*
Дерево бинарного поиска. (Binary Search Tree (BST))
Для любого узла левый ребенок меньше своего родителя, правый - больше.
Для обхода удобно использовать симметричный обход, т.к. в этом случае на экран будет выведена отсортированная последовательность.
Т.к. неравенства строгие, то дерево не содержит повторяющихся элементоа, при вставке в дерево они просто игнорируются.
---Простейшая реализация:
1. Первый элемент всегда является корнем
2. Если вставляемый элемент меньше корня, ищем подходящее место на левой ветке
3. Если вставляемый элемент больше корня - на правой

Удалить элемент из дерева надо таким образом, чтобы дерево по-прежнему оставалось деревом бинарного поиска.
Возможно три случая:
1. Удаление листа. Просто заменяем у родителя указатель на этот лист на NULL
2. Удаление узла с одним ребенком. Для ребенка родителем становится "дед". Для "деда" ребенком становится "внук"
3. Удаление узла с двумя детьми. Находим следующий за удаляемым узел. У него гарантированно не будет левого ребенка. Меняем значения удаляемого и найденного узлов. Если у найденного узла нет детей, выполняем пункт 1, если есть правый ребенок - выполняем пункт 2.
*/

void bst_insert(tree *&tr, int x) {  // ДБП - поиск
    tree *n = node(x);
    if (!tr) tr = n;  // если дерево пустое - корень
    else {
        tree *y = tr;
        while (y) {   // ищем куда вставить
            if (n->inf > y->inf)  // правая ветка
                if (y->right)
                    y = y->right;
                else {
                    n->parent = y;  // узел становится правым ребенком
                    y->right = n;
                    break;
                }
            else if (n->inf < y->inf)  // левая ветка
                if (y->left)
                    y = y->left;
                else {
                    n->parent = y;  // узел становится левым ребенком
                    y->left = n;
                    break;
                }
        }
    }
}

tree *bst_find(tree *tr, int x) {  // bst - поиск
    if (!tr || x==tr->inf) return tr;  // дошли до конца ветки или нашли
    if (x < tr->inf) return bst_find(tr->left, x);  // изем по левой ветке
    else return bst_find(tr->right, x); // ищем по правой ветке
}

tree *bst_min(tree *tr) {   // bst - минимум
    if (!tr->left) return tr;  // нет левого ребенка
    else return bst_min(tr->left);  // идем по левой ветке до конца
}

tree *bst_max(tree *tr) {  // bst - максимум
    if (!tr->right) return tr; // нет правого ребенка
    else return bst_max(tr->right);  // идем по правой ветке до конца
} 

tree *bst_next(tree *tr, int x) {  // bst - следующий элемент
    tree *n = bst_find(tr, x);
    if (n->right)                  // если есть правый ребенок
        return bst_min(n->right);  // min по правой ветке
    tree *y = n->parent;    // родитель
    while (y&&n == y->right) {  // пока не дошли до корня или узел - правый ребенок
        n = y;  // идем вверх по дереву
        y = y->parent;  
    }
    return y;  // возвращаем родителя
}

tree *bst_prev(tree *tr, int x) {  // bst - предыдущий элемент
    tree *n = bst_find(tr, x);
    if (n->left)                   // если есть левый ребенок
        return bst_max(n->left);   // max по левой ветке
    tree *y = n->parent;           // родитель
    while (y&&n == y->left) { // пока не дошли до корня или узел - левый ребенок
        n = y;  // идем вверх по дереву
        y = y->parent;
    }
    return y; // возвращаем родителя
}

void bst_delete(tree *&tr, tree *v) { // bst - удаление узла
    tree *p = v->parent; 
    if (!p) tr = NULL;  // дерево содержит один узел
    else if (!v->left && !v->right) {  // если нет детей
        if (p->left == v) p->left = NULL; // указатель у родителя меняем на NULL
        if (p->right == v) p->right = NULL;
        delete v;            
    }
    else if (!v->left || !v->right) {  // если только один ребенок
        if (!p) {  // если удаляем корень, у которого один ребенок
            if (!v->left) {  // если есть правый ребенок
                tr = v->right;  // он становится корнем
                v->parent = NULL;
            }
            else {  // аналогично для левого
                tr = v->left;
                v->parent = NULL;
            }
        }
        else {
            if (!v->left) {  // если есть правый ребенок
                if (p->left == v) // если удаляемый узел явл. левым ребенком
                    p->left=v->right; // ребенок удаляемого узла становится левым ребенком своего деда
                else
                    p->right = v->right; // ребенок удаляемого узла становится правым ребенком своего деда
                v->right->parent = p; // родителем ребенка становится его дед
            }
            else { // аналогично для левого ребенка
                if (p->left == v)
                    p->left = v->left;
                else
                    p->right = v->left;
                v->left->parent = p;
            }
            delete v;
        }
    }
    else {  // есть оба ребенка
        tree *succ = bst_next(tr, v->inf); // следующий за удаляемым узлом
        v->inf = succ->inf; // присваиваем значение
        if (succ->parent->left == succ) { // если succ левый ребенок
            succ->parent->left = succ->right; // его правый ребенок становится левым ребенком своего деда
            if (succ->right)  // если этот ребенок существует
                succ->right->parent = succ->parent; // его родителем становится дед
        }
        else {  // аналогично если succ - правый ребенок
            succ->parent->right = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        delete succ;
    }

}

void bst_example() {
    int n, x;
    cout << "n = "; cin >> n;
    tree *tr = NULL;
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        cin >> x;
        bst_insert(tr,x);
    }
    inorder(tr);
    cout << endl;
    cout << "min = " << bst_min(tr)->inf << endl;
    cout << "max = " << bst_max(tr)->inf << endl;
    cout << "x = "; cin >> x;
    if (bst_find(tr, x)) {
        cout << "next = " << bst_next(tr, x)->inf << endl;
        cout << "prev = " << bst_prev(tr, x)->inf << endl;
        bst_delete(tr, bst_find(tr,x));
        inorder(tr);
        cout << endl;
    }
    else cout << "Such node doesn't exist\n";
}



int main() {
    //bst_example();
}