// BFS. Дан невзвешенный граф неориентированный граф. Найти кратчайший путь между вершинами A и В.
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream in("test5.txt");

int n, m;
int dst[100000];
vector<vector<int>> g;
vector<int> used; // вектор посещенных вершин
vector<int> p; // вектор предков

void graph() {
	in >> n;
	in >> m;
	g.resize(n); // выделение памяти в векторах
    used.resize(n);
    p.resize(n);
	int v, u;
	for (int i = 0; i < m; ++i) { // добавление ребер в список смежности
		in >> v >> u;
        if (v > n || u > n) continue;
		v--; u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	for (int i = 0; i < n; ++i) {
		sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты
	}
}

int main() {
    graph();

    int a, b;
    cout << "Enter A: "; cin >> a;
    cout << "Enter B: "; cin >> b;
    a--; b--;   
    queue<int> q;
    q.push(a);
    used[a] = true;
    dst[a] = 0;         //теперь при добавлении каждой вершины в очередь мы вычисляем расстояние до неё
    p[a] = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int neighbor: g[cur]) {
            if (!used[neighbor]) {
                q.push(neighbor);
                used[neighbor] = true;
                dst[neighbor] = dst[cur] + 1;   // расчёт расстояния
                p[neighbor] = cur;
            }
        }
    }
    if (!dst[b]) {
        cout << "There is no such way\n";
    }
    else {
        cout << "Distance = " << dst[b] << endl; 
        vector<int> path;
	    for (int v=b; v!=-1; v=p[v])
		    path.push_back (v);
	    reverse (path.begin(), path.end());
	    cout << "Path: ";
	    for (size_t i=0; i<path.size(); ++i)
		    cout << path[i] + 1 << " ";
    }
}