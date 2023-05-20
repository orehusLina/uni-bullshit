#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct queue { // создаем структуру очередь
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x) { // функция добавления элемента в очередь
    queue *r = new queue; 
    r->inf = x;           
    r->next = NULL;       
    if (!h && !t) {       
        h = t = r;
    }
    else {
        t->next = r; 
        t = r;       
    }
}

int pop(queue *&h, queue *&t) {  // функция извлечения элементва из очереди
    int i = h->inf; 
    queue *r = h;      
    h = h->next;      
    if (!h) t = NULL;      
    delete r;          
    return i;          
}

void BFS(int x, int n, queue *&h, queue *&t, vector<vector<int>>& Gr, vector<int>& a) { // функция обхода в ширину
    a[x] = 1;           // отмечаем первую вершину посещенной
    push(h, t, x);      // добавляем ее в очередь
    cout << x << ' ';   // выводи посещенную вершину
    int y;              // инцииализируем переменную для новых вершин
    while (h && t) {    // пока очередь не пуста
        x = pop(h, t);  // извлекаем голову очереди
        for (int i = 0; i < Gr[x].size(); ++i) {    // проходим по всем вершинам, смежным с данной
            if (a[Gr[x][i]] == 0) {                 // если какая-то из вершин не посещена
                y = Gr[x][i];                       // запоминаем новую вершину
                a[y] = 1;                           // отмечаем ее посещенной
                push(h, t, y);                      // добавляем ее в очередь
                cout << y << ' ';                   // выводи посещенную вершину
            }
        }
    }
    if (find(a.begin(), a.end(), 0) != a.end()) {   // если в результате какие-то вершины останутся не посещены
        for (int i = 0; i < n; ++i) {               // находим непосещенную вершину
            if (a[i] == 0) BFS(i, n, h, t, Gr, a);  // запускаем для нее BFS
        }
    }
}

int main() {
    int n; n = 7;               // вводим пример графа
    int x; x = 0;               // изначальная вершина (корень)
    queue *h = NULL, *t = NULL; // инициализируем очередь
    vector<int> a(n);           // вектор для посещенных вершин
    vector<vector<int>> Gr (n); // список смежности
    Gr[0] = {1, 2, 4, 5};       // вводим список смежности
    Gr[1] = {0, 3};
    Gr[2] = {0, 5};
    Gr[3] = {1};
    Gr[4] = {0, 6};
    Gr[5] = {0, 2, 6};
    Gr[6] = {4, 5};
    cout << "Example of Graph: " << endl; // выводим интерфейс
    cout << "n = " << n << endl;
    cout << "root = " << x << endl;
    cout << "Adjacency list: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (auto c : Gr[i]) {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl << "RESULT " << endl; // выводим результат BFS
    cout << "BFS: ";
    BFS(x, n, h, t, Gr, a);
    cout << endl;
}