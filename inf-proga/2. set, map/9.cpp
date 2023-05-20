//Дан текст, состоящий из предложений, разделенных знаками препинания из набора «.?!». Предложения в свою очередь состоят из слов, отделенных друг от друга пробелами. Найти слова (без учета регистра) и их количество, которые встречаются одновременно и в повествовательных, и в восклицательных предложениях
#include <iostream>
#include <fstream>
#include <set>
#include <string>
using namespace std;
int main() {
    string s;
    set<string> current;        // сет для текущего предложения
    set<string> narrative;      // сет для слов, встречающихся в повествовательных предложениях
    set<string> exclamation;    // сет для слов, встречающихся в восклицательных предложениях
    ifstream in("9HP.txt");     // считываем файл в поток
    if (in.is_open()) {         
        while (getline(in, s)) { // считываем строки
            for (int i = 0; i < s.length(); ++i) {  // цикл по всем символам
                if (isalpha(s[i])) {     // если символ буква, то набираем все слово
                    string now = "";
                    while (isalpha(s[i])) {
                        now += s[i]; i++;
                    } 
                    current.insert(now); // добавляем слово в сет для текущего предложения
                }
                if (s[i] == '.') {       // если встречается точка - добавляем все 
                    for (auto c : current) {
                        narrative.insert(c);
                    }
                    current.clear();
                }
                if (s[i] == '!') {
                    for (auto c : current) {
                        exclamation.insert(c);
                    }
                    current.clear();
                }
                else if (s[i] == '?') current.clear();
            }
        }
    } 
    in.close();
    for (auto c : narrative) {
       if (exclamation.find(c) != exclamation.end()) {
            cout << c << ' ';
        }
    }
}