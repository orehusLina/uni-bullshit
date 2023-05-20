// 4. Дана последовательность целых чисел. Найти все такие цифры, которые встречаются и в двузначных, и в трехзначных числах.
#include <iostream>
#include <map>
#include <set>
using namespace std;
bool dvyz(int x) {          // функция определяющая двузначные числа
    if (x > 9 && x < 100) return true;
    return false;
}
bool trez(int x) {          // функция определяющая трехзначные числа
    if (x > 99 && x < 1000) return true;
    return false;
}

int main() {
    set<int> exists2;  // сет цифр, встречающихся в двухначных числах
    set<int> exists3;  // сет цифр, встречающихся в трехзначных числах
    set<int> num;      // сет для всех введенных чисел
    cout << "n = ";
    int n; cin >> n; int x;
    for (int i = 0; i < n; ++i) {   // ввод всех чисел
        cin >> x;
        num.insert(x);
    }
    for (int c : num) {     // цикл по всем введенным числам
        if (dvyz(c)) {      // если число двузначное, то закидываем его цифры в соответствующие сеты
            exists2.insert(c%10);
            exists2.insert(c/10);
        }
        if (trez(c)) {      // если число трехзначное, то закидываем его цифры в соответствующие сеты
            exists3.insert(c%10);
            exists3.insert(c/10%10);
            exists3.insert(c/100);
        }
    }
    cout << "Result: ";  // для красоты
    for (int c : exists2) {   // цикл по всем цифрам, встречающимся в двузнчных числах
        if (exists3.find(c) != exists3.end()) {  // если эта цифра встречается в сете трехзначных, то выводим ее
            cout << c << ' ';
        }
    }
}