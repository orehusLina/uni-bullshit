// 11. Даны две последовательности целых чисел. В первой последовательности удалить все четные элементы, во второй — все нечетные. Отсортировать данные последовательности. Объединить их в одну отсортированную последовательность.
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
using namespace std;
bool odd(int n) { // функция, определяющая нечетные числа
    return n%2;
}
bool even(int n) {
    return !(n%2);
}
int main(){
    int n, m;
    cout << "n = "; cin >> n; // ввод размерности первой последовательности
    cout << "m = "; cin >> m; // ввод размерности второй последовательности
    list<int> a;              // объявление списков
    list<int> b; int x;
    for (int i = 0; i < n; i++) {   // ввод первого списка
        cout << "a[" << i << "] = ";
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < m; i++) {
        cout << "b[" << i << "] = "; // ввод второго списка
        cin >> x;
        b.push_back(x);
    } 
    a.remove_if(even);
    b.remove_if(odd); 
    a.sort(); b.sort();                              // сортируем листы
    a.merge(b);                                     // объединяем в одну отсортированную последовательность
    for (int &c : a) cout << c <<' ';               // выводим
}