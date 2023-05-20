// 6. Дана последовательность целых чисел. Найти сумму элементов, кратных 𝑋. Вывести минимальный элемент. Все четные элементы заменить на максимальный.
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
int X; // объявление предиката
bool neKratnoX(int n) {  //функция, определяющая числа не кратные Х
    return n%X!=0;
}
bool even(int n) { // функция, определяющая четные числа
    return n%2==0;
}
using namespace std;
int main() {
    cout << "n = ";
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {  // ввод вектора с клавиатуры
        cout << "a[" << i << "] = ";
        cin >> a[i];
    }
    cout <<"X = "; cin >> X;
    vector<int> temp(a); // копия вектора а
    replace_if(temp.begin(), temp.end(), neKratnoX, 0); //замена некратных чисел на нули (в копии вектора)
    cout << "Sum of elements, divisible by X = ";
    cout << accumulate(temp.begin(), temp.end(), 0) << '\n'; //сумма всех элементов, не равных нулю
    cout << "Min element = " << *min_element(a.begin(), a.end()) << '\n'; // вывод минимального элемента
    int maxim = *max_element(a.begin(), a.end()); 
    replace_if(a.begin(), a.end(), even, maxim); // замена всех четных элементов максимальным
    cout << "All even elements, replaced with the maximal one:" << '\n';
    for (int c : a) cout << c << ' ';
}