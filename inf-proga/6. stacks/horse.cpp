// Дана шахматная доска. Вывести кратчайший путь конем от клетки А до клетки В. 
// Должны быть введены две клетки в виде, например, А2 и Е6. 
// Путь должен быть выведен в виде списка клеток А2 В4 С6 D8 E6
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

char decode(int n) { // функция, переводящая номер клетки в букву шахматной доски
    return 'A'+(n-1);
}

struct CELL {  // задаем структуру с клетками
  int x, y;
  CELL(int a = -1, int b = -1) : x(a), y(b) {};
};

int operator==(CELL a, CELL b) {  // перегружаем оператор равенства
  return (a.x == b.x) && (a.y == b.y);
}

int operator!=(CELL a, CELL b) {  // перегружаем оператор неравенства
  return !((a.x == b.x) && (a.y == b.y));
}

int CanGo(CELL c) { // функция, проверяющая, принадлежит ли клетка шахматной доске
    int n = 8;
  return !((c.x < 0) || (c.x >= n) || (c.y < 0) || (c.y >= n));
}

struct queue { // создаем структуру очередь
    CELL inf;
    queue *next;
};

CELL translate(string Z9) { // функция, переводящая ввод в структуру клетки
    CELL a;
    a.x = Z9[0]-'A'+1;
    a.y = Z9[1]-'0';
    return a;
}
void push_queue(queue *&h, queue *&t, CELL x) { // функция добавления элемента в очередь
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
CELL pop_queue(queue *&h, queue *&t) {  // функция извлечения элементва из очереди
    CELL i = h->inf; 
    queue *r = h;      
    h = h->next;      
    if (!h) t = NULL;      
    delete r;          
    return i;          
}
void BFS(CELL start, CELL finish, queue *&h, queue *&t, vector<vector<int>>& used, vector<vector<CELL>>& parent) { // функция обхода в ширину
    int dx[] = {1,1,-1,-1,2,2,-2,-2}; // В массивах dx и dy описываем все возможные ходы коня. 
    int dy[] = {2,-2,2,-2,1,-1,1,-1}; // Из клетки (i, j) конь может пойти в одну из клеток (i + dx[k], j + dy[k]), 0 ≤ k ≤ 7
    int n = 8;                        // стандартный размер шахматной доски
    used[start.x][start.y] = 1;       // отмечаем первую клетку посещенной
    parent[start.x][start.y] = -1;    // инициализируем массив предков
    push_queue(h, t, start);          // добавляем ее в очередь
    CELL node, y;                     // инцииализируем переменную для новой клетки
    while (h && t) {                  // пока очередь не пуста
        node = pop_queue(h, t);       // извлекаем голову очереди
        for (int i = 0; i < 8; ++i) {    // проходим по всем клеткам, доступным из данной
            CELL next = CELL(node.x + dx[i], node.y+dy[i]); // идем в следующую клетку
            if (!CanGo(next)) continue;  // если клетка не принадлежит доски, пропускаем ее
            if (used[next.x][next.y] == 0) {    // если клетка не была посещена     
                y = next;                       // запоминаем новую клетку
                used[next.x][next.y] = 1;       // отмечаем ее посещенной
                push_queue(h, t, y);            // добавляем ее в очередь
                parent[next.x][next.y] = node;  // добавляем в массив родителей предыдущую клетку
            }
            if (next == finish) return; // если дошли до нужной клетки, заканчиваем
            push_queue(h, t, next);     // добавляем в очередь новую клетку
        }
    }
}
int main() {
    int n = 8;      // стандартная шахматная доска
    string x, y;    // объявляем переменные для ввода
    cout << "Starting cell: "; cin >> x;  // интерфейс и ввод
    cout << "Ending cell: "; cin >> y;
    CELL start, finish; 
    start = translate(x);  // переводим ввод в структуру с клетками
    finish = translate(y);
    queue *h = NULL, *t = NULL;            // очередь для рассматриваемых клеток
    vector<vector<int>> used(n);           // вектор для посещенных клеток
    vector<vector<CELL>> parent(n);        // массив предков
    CELL empty; empty.x = 0; empty.y = 0;  // инициализиуем пустую клетку
    for (int i = 0; i < n; ++i) {          // задаем размеры векторов векторов
        used[i].resize(n);
        parent[i].resize(n);
    }
    BFS(start, finish, h, t, used, parent); // запускаем обход в ширину
    vector<CELL> path;  // здесь будет путь
    if (!used[finish.x][finish.y]) cout << "No path!"; // если в клетку невозможно попасть, выводим сообщение об этом
    else {
        int counter = 1;
        while (start != finish) {   // восстанавливем путь
            path.push_back(finish);
            finish = parent[finish.x][finish.y];
            counter++;
        }
            path.push_back(start);
        for (int j = counter-1; j >= 0; j--) { // выводи вектор пути в обратном порядке
            cout << decode(path[j].x) << path[j].y << ' ';
        } 
    }
    // На тестовых данных Starting cell: A2, Ending cell: E6 
    // Выводит корректный путь: A2 B4 C6 D4 E6  
    // (D4 отличается от D8 в примере, но такой путь тоже существует и аналогичен)
}