// 3. Дана последовательность целых чисел. Все нечетные элементы заменить нулем.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool odd(int n) {  // функция, определяющая нечетные числа
    return n % 2;
}

int main() {
    cout << "n = ";
    int n; cin >> n;   // ввод количества элементов
    vector<int> a; int x;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = ";  // ввод чисел в вектор
        cin >> x;
        a.push_back(x);
    }
    replace_if(a.begin(), a.end(), odd, 0); // замена нечетных на ноль
    cout << "Result: ";
    for (int c : a) {    // вывод результата
        cout << c << " ";
    }
}