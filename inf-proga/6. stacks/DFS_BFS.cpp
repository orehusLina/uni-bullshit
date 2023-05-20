#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct stack {  // создаем структуру стек
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x) { // функция добавления элемента в стек
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

char pop_stack(stack *&h) {  // функция извлечения элемента из стека
    int i = h -> inf;
    stack *r = h;
    h = h -> next;
    delete r;
    return i;
}

struct queue { // создаем структуру очередь
    int inf;
    queue *next;
};

void push_queue(queue *&h, queue *&t, int x) { // функция добавления элемента в очередь
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

int pop_queue(queue *&h, queue *&t) {  // функция извлечения элементва из очереди
    int i = h->inf; 
    queue *r = h;      
    h = h->next;      
    if (!h) t = NULL;      
    delete r;          
    return i;          
}

void DFS(int x, int n, stack *&current, vector<vector<int>>& Gr, vector<int>& a) { // функция обхода в глубину
    a[x] = 1;                        // помечаем изначальную вершину как посещенную
    push_stack(current, x);          // добавляем текущую вершину в стек
    cout << x << ' ';                // выводим текущую вершину
    bool fl = false; int y;          // объявляем переменные
    while (current) {                // пока стек не пуст
        x = current->inf;            // извлечкаем значение текущей вершины
        for (int i = 0; i < Gr[x].size(); ++i) {  // проходим по всем смежным с ней вершинам
            if (a[Gr[x][i]] == 0) {  // если найдется непосещенная
                y = Gr[x][i];        // запоминаем новую вершину
                fl = true;           // отмечаем нахождение новой вершины        
                break;               // завершаем текущий цикл
            }
        }
        if (fl == true) {            // если имеется необработанная новая вершина
            a[y] = 1;                // отмечаем ее посещенной
            push_stack(current, y);  // добавляем ее в стек
            cout << y << ' ';        // выводим ее как часть пути
            fl = false;              // возвращаем флагу значение false
        }
        else pop_stack(current);     // удаляем из очереди последнюю вершину
    }
    if (find(a.begin(), a.end(), 0) != a.end()) {  // если в результате останутся необработанные вершины
        for (int i = 0; i < n; ++i) {   // находим первую такую вершину
            if (a[i] == 0) DFS(i, n, current, Gr, a);  // обрабатываем ее
        }
    }
}

void BFS(int x, int n, queue *&h, queue *&t, vector<vector<int>>& Gr, vector<int>& a) { // функция обхода в ширину
    a[x] = 1;                 // отмечаем первую вершину посещенной
    push_queue(h, t, x);      // добавляем ее в очередь
    cout << x << ' ';         // выводи посещенную вершину
    int y;                    // инцииализируем переменную для новых вершин
    while (h && t) {          // пока очередь не пуста
        x = pop_queue(h, t);  // извлекаем голову очереди
        for (int i = 0; i < Gr[x].size(); ++i) {    // проходим по всем вершинам, смежным с данной
            if (a[Gr[x][i]] == 0) {                 // если какая-то из вершин не посещена
                y = Gr[x][i];                       // запоминаем новую вершину
                a[y] = 1;                           // отмечаем ее посещенной
                push_queue(h, t, y);                // добавляем ее в очередь
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
    int n; n = 7;           // создаем пример графа
    stack *current = NULL;  // стек для рассматриваемых вершин (дфс)
    queue *h = NULL, *t = NULL; // очередь для рассматриваемых вершин (бфс)
    vector<int> a(n);           // вектор для посещенных вершин
    vector<vector<int>> Gr (n); // список смежности
    int x; x = 0;            // первая рассматриваемая вершина (корень)
    Gr[0] = {1, 2, 4, 5};    // заполняем список смежности
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
    cout << endl << "RESULT " << endl;  
    cout << "DFS: "; 
    DFS(x, n, current, Gr, a); // выводи результат DFS
    cout << endl;
    for (int i = 0; i < n; ++i) {  // очищаем список посещенных вершин
        a[i] = 0;
    }
    cout << "BFS: ";  
    BFS(x, n, h, t, Gr, a);   // выводим результат BFS
}