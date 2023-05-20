// Реализуйте аналог игры "Виселица": Создать контейнер, содержащий алфавит, и определяющий, угадывалась ли данная буква. Сгенерируйте слово, заменив буквы подчеркиванием, и запрашивайте у пользователя букву. Если буква угадана, выводите ее на нужном месте. В любой момент пользователь может набрать все слово целиком (должна быть предоставлена такая возможность).  Должен быть счетчик ходов и определено максимальное число ходов. Если слово не угадано за максимальное число ходов - выводится сообщение о проигрыше, если угадано - о победе.  Желательно вывести алфавит и зачеркивать уже выбранные буквы.   
//Можно попробовать вместо максимального числа ходов нарисовать виселицу (это необязательно)
/*
1. Создать генератор слов, выбрать из него загаданное слово +
2. Создать map со всеми буквами, установить 1 во всех буквах, содержащихся в слове +
3. Создать вектор с отгадываемым словом, изначально заолненный нижними подчеркиваниями
4. Сделать приветственное слово: привет в виселицу бла-бла, введите букву, если хотите отгадать слово целиком введите 0
5. Если полученное значение 0 - вывести интерфейс ввода слова, принять слово, сделать проверку и соответствующий вывод
6. Иначе проверить наличие буквы в словаре -
7. Если буква присутствует, вывести ее в нужном месте слова, увеличить счетчик ходов на 1, вывести виселицу от этого значения, алфавит с зачеркнутыми буквами
8. Если буква отсутствует, вывести состояние отгадываемого слова на данный момент и виселицу, алфавит с зачеркнутыми буквами
9. Если слово угадано - вывести сообщение о победе
10. Если счетчик достиг максимального количества ходов и слово не угадано - вывести сообщение о проигрыше
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <cstring>
using namespace std;
string wordGenerator() {   // функция, выбирающее случайное слово из файла с 30 словами
    ifstream in("words.txt");
    string selected, line;
    srand(time(NULL));
    while (in.peek() != EOF) {
        for (unsigned i = 1; getline(in, line); ++i)
        if ((uintmax_t) rand() * i <= RAND_MAX)
        selected = line;
    }  
    return(selected);
}

void hangman(int n){ //функция выводящая на экран изображение виселицы (бесстыже украдена)
    switch (n) {
    case 9: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ / \\|  "); break;
    case 8: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ /  |  "); break;
    case 7: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_    |  "); break;
    case 6: printf("  ____ |\n |   | |\n |   O |\n |  /| |\n_|_    |  "); break;
    case 5: printf("  ____ |\n |   | |\n |   O |\n |   | |\n_|_    |  "); break;
    case 4: printf("  ____ |\n |   | |\n |   O |\n |     |\n_|_    |  "); break;
    case 3: printf("  ____ |\n |     |\n |     |\n |     |\n_|_    |  "); break;
    case 2: printf("       |\n |     |\n |     |\n |     |\n_|_    |  "); break;
    case 1: printf("       |\n       |\n       |\n       |\n___    |  "); break;
    case 0: printf("       |\n       |\n       |\n       |\n       |  "); break;
    }
}

int main() {
    string targetWord = wordGenerator();  // генерируем случайное слово
    set<char> available_letters;  // создаем сет из доступных (оставшихся) букв
    map<char, int> alphabet;      
    string stringAlphabet = "abcdefghijklmnopqrstuvwxyz";
    for (auto c : stringAlphabet) {
        alphabet[c] = 0;             // создали алфавит, заполненный нулями
        available_letters.insert(c);
    }
    cout << endl;
    for (auto c : targetWord) alphabet[c] = 1; // узнали, какие буквы встречаются в загаданном слове

    int length = targetWord.length();  // запомнили длину загаданного слова
    int leftLetters = length;          // переменная для количества оставшихся букв (поможет узнать о выигрыше игрока)
    vector<char> guessing_word (length);  // создаем вектор, заполненный нижними подчеркиваниями
    for (int i = 0; i <= length; ++i) {   // здесь будет фиксироваться процесс отгадывания слова
        guessing_word.assign(i, '_');     // заполняем вектор отгадываемого слова нижними подчеркиваниями
    }

    int e = 1;             // приветствуем игрока
    while (e--) {
    cout << "Enter your sex: w / m / nonbinar" << endl;
    string sex; cin >> sex;
    if (sex == "m") cout << "Welcome to the game, HANGMAN" << endl;
    else if (sex == "w") cout << "Welcome to the game, HANGWOMAN" << endl;
    else if (sex == "nonbinar") cout << "Welcome to the game, HANGSOMEONE" << endl;
    else { cout << "Why can't you read? Try again." << endl; e++; }
    }
    cout << endl;

    int turns = 1;  // инициализируем номер хода
    while (turns < 10) {   // максимальное количество ходов - 9
        cout << "Enter a letter: ";
        char x; cin >> x;   // считываем угадываемую букву
        if (available_letters.find(x) == available_letters.end()) {  // если такая буква недоступна, выводим сообщение об этом
            cout << "Why can't you enter an available letter? Try again!" << endl; // (пассивно-агрессивно выводим сообщение об этом)
            continue; // переходим к следующей итерации, чтобы можно было снова ввести букву (ход не засчитывается)
        }
        if (alphabet[x] == 0) {  // если такой буквы нет в загаданном слове
            for (int i = 0; i < length; ++i) cout << guessing_word[i] << ' '; // выводим текущий статус отгадывания слова
            cout << endl;
            cout << "No such letter! " << endl;  // соответствующее сообщение
        } 
        else {  // если буква отгадана
            for (int i = 0; i < length; ++i) {
                if (targetWord[i] == x) {
                    guessing_word[i] = x;  // добавляем эту букву в текущий статус отгадываемого слова (там, где было подчеркивание)
                    leftLetters--;         // уменьшаем счетчик оставшихся букв
                }
            }
            for (int i = 0; i < length; ++i) cout << guessing_word[i] << ' '; // выводим текущий статус отгадывания слова
            cout << endl;
            cout << "Are you ready to enter a word? Enter y/n: ";  // предлагаем ввести слово полностью
            string ready; cin >> ready;
            if (ready == "y") {   // в случае согласия считываем попытку угадывания слова целиком
            cout << "Then do it! ";
            string s; cin >> s;
            if (s == targetWord) { // проверяем, было ли слово отгадано
                cout << "Congratulations! You're alive! (you won) " << endl;  // выводим сообщение о победе
                return 0;      // завершаем программу
            }
            else cout << "Wrong guess, but keep going" << endl;  // мотивирующее сообщение
            }
        }
        if (leftLetters == 0) { // если осталось 0 загаданных букв, то игрок выиграл
            cout << "Congratulations! You're alive! (you won)" << endl; // сообщаем об этом
            return 0;           // завершаем программу
        }
        alphabet.erase(x);      // стираем букву из алфавита (она уже не понадобится)
        available_letters.erase(x); // стираем букву из доступных букв
        hangman(turns);             // вызываем функцию, отрислвывающую виселицу, в зависимости от номера хода
        cout << endl;
        if (turns != 9) {       // на последнем шаге уже не выводим оставшиеся буквы
            cout << "Remaining letters: "; // в ином случае выводим оставшиеся буквы
            for (auto c : alphabet) cout << c.first << ' '; cout << endl;
        }
        turns++;    // увеличиваем счетчик шагов
    }
    cout << "We're sorry, but you are DEAD!"; // если программа не была завершена к этому моменту (в случае победы), то игрок умер, извещаем его об этом
    system("pause"); 
    return 0;
}