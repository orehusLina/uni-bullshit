// Дано дерево. Вывести путь от узла A до узла B
#include <iostream>
using namespace std;

struct tree {
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x) {
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
}

void preorder(tree *tr)
{ // прямой обход (К-Л-П)
    if (tr)
    {
        cout << tr->inf; // корень
        preorder(tr->left); // левое
        preorder(tr->right); // правое
    }
}

void postorder(tree *tr)
{ // обратный обход (Л-П-К)
    if (tr)
    {
        postorder(tr->left); // левое
        postorder(tr->right); // правое
        cout << tr->inf; // корень
    }
}

void inorder(tree *tr)
{ // симметричный обход (Л-К-П)

    if (tr)
    {

        inorder(tr->left); // левое

        cout << tr->inf; // корень

        inorder(tr->right); // правое
    }
}

void insert(tree *&tr, int x)
{ // вставка

    tree *n = node(x);

    if (!tr)
        tr = n; // если дерево пустое - корень

    else
    {

        tree *y = tr;

        while (y)
        { // ищем куда вставлять

            if (n->inf > y->inf) // правая ветка

                if (y->right)

                    y = y->right;

                else
                {

                    n->parent = y; // узел становится правым ребенком

                    y->right = n;

                    break;
                }

            else if (n->inf < y->inf) // левая ветка

                if (y->left)

                    y = y->left;

                else
                {

                    n->parent = y; // узел становится левым ребенком

                    y->left = n;

                    break;
                }
        }
    }
}

tree *find(tree *tr, int x)
{ // поиск

    if (!tr || x == tr->inf) // нашли или дошли до конца ветки

        return tr;

    if (x < tr->inf)

        return find(tr->left, x); // ищем по левой ветке

    else

        return find(tr->right, x); // ищем по правой ветке
}

tree *Min(tree *tr)
{ // поиск min

    if (!tr->left)
        return tr; // нет левого ребенка

    else
        return Min(tr->left); // идем по левой ветке до конца
}

tree *Max(tree *tr)
{ // поиск max

    if (!tr->right)
        return tr; // нет правого ребенка

    else
        return Max(tr->right); // идем по правой ветке до конца
}

tree *Next(tree *tr, int x)
{ // поиск следующего

    tree *n = find(tr, x);

    if (n->right) // если есть правый ребенок

        return Min(n->right); // min по правой ветке

    tree *y = n->parent; // родитель

    while (y && n == y->right)
    { // пока не дошли до корня или узел - правый ребенок

        n = y; // идем вверх по дереву

        y = y->parent;
    }

    return y; // возвращаем родителя
}

tree *Prev(tree *tr, int x)
{ // поиск предыдущего

    tree *n = find(tr, x);

    if (n->left) // если есть левый ребенок

        return Max(n->left); // max по левой ветке

    tree *y = n->parent; // родитель

    while (y && n == y->left)
    { // пока не дошли до корня или узел - левый ребенок

        n = y; // идем вверх по дереву

        y = y->parent;
    }

    return y; // возвращаем родителя
}

void Delete(tree *&tr, tree *v)
{ // удаление узла

    tree *p = v->parent;

    if (!p)
        tr = NULL; // дерево содержит один узел

    else if (!v->left && !v->right)
    { // если нет детей

        if (p->left == v) // указатель у родителя меняем на NULL

            p->left = NULL;

        if (p->right == v)

            p->right = NULL;

        delete v;
    }

    else if (!v->left || !v->right)
    { // если только один ребенок

        if (!p)
        { // если удаляем корень, у которого 1 ребенок

            if (!v->left)
            { // если есть правый ребенок

                tr = v->right; // он становится корнем

                v->parent = NULL;
            }

            else
            { // аналогично для левого

                tr = v->left;

                v->parent = NULL;
            }
        }

        else
        {

            if (!v->left)
            { // если есть правый ребенок

                if (p->left == v) // если удаляемый узел явл. левым ребенком

                    p->left = v->right; // ребенок удаляемого узла становится левым ребенком своего "деда"

                else

                    p->right = v->right; ////ребенок удаляемого узла становится правым ребенком своего "деда"

                v->right->parent = p; // родителем ребенка становится его "дед"
            }

            else
            { // аналогично для левого ребенка

                if (p->left == v)

                    p->left = v->left;

                else

                    p->right = v->left;

                v->left->parent = p;
            }

            delete v;
        }
    }

    else
    { // есть оба ребенка

        tree *succ = Next(tr, v->inf); // следующий за удаляемым узлом

        v->inf = succ->inf; // присваиваем значение

        if (succ->parent->left == succ)
        { // если succ левый ребенок

            succ->parent->left = succ->right; // его правый ребенок становится левым ребенком своего "деда"

            if (succ->right) // если этот ребенок существует

                succ->right->parent = succ->parent; // его родителем становится "дед"
        }

        else
        { // аналогично если succ - правsq ребенок

            succ->parent->right = succ->right;

            if (succ->right)

                succ->right->parent = succ->parent;
        }

        delete succ;
    }
}

void pathToRoot(tree *tr, tree *w)

{

    tree *p = w;

    while (tr != p)

    {

        cout << p->inf << " ";
        p = p->parent;
    }
}

void pathToNode(tree *tr, tree *p)

{

    cout << tr->inf << " ";

    if (p->inf == tr->inf)

        return;

    else if (p->inf < tr->inf)

        pathToNode(tr->left, p);

    else

        pathToNode(tr->right, p);
}

void path(tree *tr, int a, int b)

{

    tree *p = tr;

    if (a <= tr->inf && b >= tr->inf)

    {
        pathToRoot(tr, find(tr, a));
        pathToNode(tr, find(tr, b));
    }

    else if (a < tr->inf && b < tr->inf)
        path(tr->left, a, b);

    else
        path(tr->right, a, b);
}

int main()

{

    int n, x;

    cout << "n=";
    cin >> n;

    tree *tr = NULL;

    for (int i = 0; i < n; i++)
    {

        cin >> x;

        insert(tr, x);
    }

    inorder(tr);
    cout << endl;

    preorder(tr);
    cout << endl;

    postorder(tr);

    cout << endl;

    cout << "Enter A B ";

    int a, b;

    cin >> a >> b;

    path(tr, a, b);

    cout << endl;

    return 0;
}