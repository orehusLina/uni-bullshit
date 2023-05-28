// BFS. Дан неориентированный граф. Определить содержит ли он циклы. Если да, то вывести их.
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream in("test3.txt");

void bfs(int x, queue<int>& q, vector<int>& used, vector<int>& path, vector<vector<int>>& Gr) {
    used[x] = 1;
    path.push_back(x);
    q.push(x);
    int y;
    while(!q.empty()) {
        y = q.front();
        for (int i = 0; i < Gr[y].size(); ++i) {
            if (Gr[y][i] == 0) {
                used[Gr[y][i]] = 1;
                path.push_back(Gr[y][i]);
                q.push(Gr[y][i]);
            }
        }
        q.pop();
    }
}

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
    queue<int> q;
    vector<int> used (n);
    vector<int> path;
    bfs(0, q, used, path, Gr);
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << ' ';
    }
}