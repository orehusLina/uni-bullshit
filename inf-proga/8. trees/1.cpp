// Дано дерево. Определить количество узлов, имеющих только правого потомка.

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
        cout << tr->inf << ' ';     // корень
        preorder(tr->left);  // левое поддерево
        preorder(tr->right); // правое поддерево
    }
}

void postorder(tree *tr) {    // обратный обход (лев-прав-корень)
    if (tr) {
        postorder(tr->left);  // левое поддерево
        postorder(tr->right); // правое поддерево
        cout << tr->inf << ' ';      // корень
    }
}
int counter = 0;
void inorder (tree *tr) {     // симметричный обход (лев-кор-прав)
    if (tr) {
        inorder(tr->left);    // левое поддерево
        cout << tr->inf << ' ';      // корень
        if (tr->right && !tr->left) { counter++; }
        inorder(tr->right);   // правое поддерево
    }
}

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


int main() {
    int n, x, x1;
    cout << "n = ";
    cin >> n;

    tree *tr = NULL;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        cin >> x1;
        bst_insert(tr, x1);
    }
    
    inorder(tr);
    cout << endl;

    cout << counter;

    return 0;
}