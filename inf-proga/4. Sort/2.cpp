// 2. По году рождения с помощью сортировки подсчетом.
// В файле содержатся данные о сотрудниках предприятия: фамилия, должность, дата рождения (день, месяц, год), стаж работы, зарплата.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

ifstream in("testENG.txt");
ofstream out("output.txt");

struct date
{ // дата
    int dd, mm, yy;
};

struct people
{                   // данные о человеке
    string Surname; // фамилия
    string position;
    date DateOfBirth; // дата рождения
    int experience;
    int Salary; // зарплата
};

date Str_to_Date(string str)
{ // из строки в дату
    date x;
    string temp = str.substr(0, 2); // день
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2); // месяц
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4); // год
    x.yy = atoi(temp.c_str());
    return x;
}

vector<people> inFile()
{ // ввод из файла
    vector<people> x;
    people temp;
    while (in.peek() != EOF)
    {
        in >> temp.Surname;  // фамилия
        in >> temp.position; // должность
        string tmp;          // дата рождения
        in >> tmp;
        temp.DateOfBirth = Str_to_Date(tmp);
        in >> temp.experience;
        in >> temp.Salary; // зарплата
        x.push_back(temp);
    }
    return x;
}

void print(people x)
{                                          // вывод в файл
    out << setw(40) << left << x.Surname;  // по левому краю, 10 позиций для фамилии
    out << setw(40) << left << x.position; // по левому краю, 10 позиций для должности
    if (x.DateOfBirth.dd < 10)
        out << left << '0' << x.DateOfBirth.dd << '.'; // добавляем 0
    else
        out << left << x.DateOfBirth.dd << '.';
    if (x.DateOfBirth.mm < 10)
        out << '0' << x.DateOfBirth.mm << '.';
    else
        out << x.DateOfBirth.mm << '.';
    out << left << setw(6) << x.DateOfBirth.yy; // на год 6 позиций
    out << setw(10) << left << x.experience;
    out << left << setw(10) << x.Salary << endl; // запрлата
}

bool operator<(people a, people b)
{ // переопределяем оператор < в соотвествии с условием
    if (a.DateOfBirth.yy < b.DateOfBirth.yy)
        return true;
    return false;
}

void counter_sort(vector<people> &x)
{
    people min1 = x[0];
    people max1 = x[0];
    for (int i = 0; i < x.size(); i++)
    {
        if (max1 < x[i])
            max1 = x[i];
        if (x[i] < min1)
            min1 = x[i];
    }
    int k = abs(max1.DateOfBirth.yy - min1.DateOfBirth.yy + 1);
    vector<vector<people>> B2 (max1.DateOfBirth.yy + 1);
    int temp = min1.DateOfBirth.yy;
    while (temp <= max1.DateOfBirth.yy)
    {
        for (int i = 0; i < x.size(); i++) {
            if (x[i].DateOfBirth.yy == temp)
                B2[temp].push_back(x[i]); }
        temp++; 
    }
    for (auto c : B2) {
        for (people r : c) {
            print(r);
        }
    } 
}

int main()
{
    vector<people> x;
    x = inFile();
    counter_sort(x);
    return 0;
}
