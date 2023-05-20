#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> edges (m);
    for (int i = 0; i < m; ++i) {
        string u, v; cin >> u >> v;
        string x = edges[u] + v;
        edges[u] =  x;
    }
    /*
    for (int i = 0; i < n; ++i) {
        sort(edges[i].begin(), edges[i].end());
    } */
    for (int i = 0; i < n; ++i) {
        cout << edges[i].size() << ' ';
        int k = 1;
        for (auto c : edges[i]) {
            cout << c;
            if (n != k) cout << ' ';
            else cout << '\n';
        }
    }
}