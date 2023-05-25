// Cоздать граф, используя список смежности, выполнить задание и вывести результат на экран.
// Дан неориентированный граф. Вывести количество вершин, смежных с данной.
// Формат входных данных: а в первой строке число n - количество вершин в графе, далее n строк, в которых i-я строка:
// сначала количество вершин, смежных с данной, затем сами вершины
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream in("test1.txt");

void print(vector<vector<int>> Gr, int n) {
    for (int i = 1; i <= n; ++i) {
        cout << "Neighbors of " << i << " vertex: ";
        for (int j = 1; j <= size(Gr[i])-1; ++j) {
            cout << Gr[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    int n; in >> n; int m;
    vector<vector<int>> Gr(n+1);
    for (int i = 1; i <= n; ++i) {
        int m; in >> m;
        Gr[i].push_back(0);
        int x;
        for (int j = 1; j <= m; ++j) {
            in >> x;
            Gr[i].push_back(x);
        }
    }
    
    cout << "The adjacency list looks like this: ";
    cout << endl;
    print(Gr, n);

    cout << "Enter a vertex: ";
    int k; cin >> k;
    cout << "Number of adjacent vertices = " << size(Gr[k])-1;
}