// Дано дерево. Определить количество листьев.
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

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

int counter = 0;
void leafs(tree *tr) {
    if (tr)
    {
        leafs(tr->left);
        if (!tr->left && !tr->right) {
            cout << tr->inf << " ";
            counter++;
        }
        leafs(tr->right);
    }
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
    cin >> n;
    create(tr, n);
    int k = int(log((float)n) / log((float)2.0));
    print(tr, k);
    preorder(tr);
    cout << endl;
    cout << "Leafs: ";
    leafs(tr);
    cout << endl;
    cout << "Amount of leafs: " << counter;
}