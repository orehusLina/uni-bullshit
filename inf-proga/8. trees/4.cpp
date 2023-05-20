// Дано дерево. Определить сумму узлов, находящихся на k-ом уровне.
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;
ifstream in("input.txt");
struct tree {
    int inf;
    tree *right;
    tree *left;
};

tree *node(int x) {
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    return n;
}

void create(tree *&tr, int n) {
    int x;
    if (n > 0) {
        cin >> x;
        tr = node(x);
        int nl = n / 2;
        int nr = n - nl - 1;
        create(tr->left, nl);
        create(tr->right, nr);
    }
}

void preorder(tree *tr) {
    if (tr) {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

int levels(tree *tr, int k, int l) {
    int res;
    if (tr) {
        if (k == l)
            res = tr->inf;
        else if (k > l)
            res = levels(tr->left, k, l + 1) + levels(tr->right, k, l + 1);
        else
            res = 0;
    }
    else
        res = 0;
    return res;
}

void print(tree *tr, int k) {
    if (!tr)
        cout << "Empty tree\n";
    else {
        queue<tree *> cur, next;
        tree *r = tr;
        cur.push(r);
        int j = 0;
        while (cur.size()) {
            if (j == 0) {
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    cout << ' ';
            }
            tree *buf = cur.front();
            cur.pop();
            j++;
            if (buf) {
                cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << ' ';
            }
            if (!buf) {
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << ' ';
                cout << ' ';
            }
            if (cur.empty()) {
                cout << endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}

int main() {
    tree *tr = NULL;
    int n, x;
    cout << "n = "; cin >> n;
    create(tr, n);
    int k = int(log((float)n) / log((float)2.0));
    print(tr, k);
    preorder(tr);
    cout << endl;
    int lvl;
    cout << "Choose the level: "; cin >> lvl;
    cout << "Sum of elements on a chosen level = " << endl;
    cout << levels(tr, lvl-1, 0);
    return 0;
}