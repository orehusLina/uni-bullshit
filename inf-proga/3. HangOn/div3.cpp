/*
    1. Сосчитать количество всех символов в map
    2. Пройтись по всем заглавным и насчитать количество соответствующих маленьких в сумму, удалить их из мэпа
        Пока k > 0:
    3. Найти пары символов одного регистра (их значения ключей больше одного) и попарно уничтожить, при это увеличивая сумму на 1 и уменьшая k на 1
    4. Вывести сумму
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        int k; cin >> k;
        int suma = 0;
        string s; cin >> s;
        vector<int> symb(1000);
        for (auto c : s) {
            symb[int(c)]++;
        }
        for (pair<char, int> c : symb) {
            if (symb[c.first+32] > 0) {
                int g = min(c.second, symb[char(int(c.first)+32)]);
                suma += g;
                symb[c.first]-=g;
                symb[c.first+32]-=g;
                cout << c.first << ' ' << c.second <<  endl;
            }
        }
    }
}