// Дан ориентированный граф. Подсчитать полустепень исхода каждой вершины.
// Ориентированный граф задан следующим образом:
// В первой строке n и m, где n - число вершин, m - число ребер
// Далее m строк каждая из которых задает ребро из первой указанной вершины во вторую.
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("test2.txt");

int main() {
    // преобразуем список ребер в список смежности, где в i строке заданы вершины, в которые можно попасть из i-ой.
    int n, m; in >> n >> m;
    vector<vector<int>> Gr (n+1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        in >> a >> b;
        Gr[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        sort(Gr[i].begin(), Gr[i].end());
    }
    cout << "The adjacency list looks like this: " << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "From " << i << " vertex we can go to: ";
        for (auto c : Gr[i]) {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "The half-step of the " << i << " vertex exodus: " << size(Gr[i]) << endl; 
    }
}