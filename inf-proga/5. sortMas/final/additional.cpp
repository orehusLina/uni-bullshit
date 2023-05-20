// 2. Строки по возрастанию с помощью сортировки подсчетом.
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
ifstream in("test.txt");
ofstream out("output.txt");

void Sort(int *mas, int n)
{
    int p = 10;
    int k = 3;
    vector<int> vec[p];
    int i = 0;
    while (i < k)
    {
        cout << "JOPA" << endl;
        for (int j = 0; j < n; j++)
        {
            string stroka = to_string(mas[j]);
            stroka = stroka[i];
            int num = stoi(stroka);
            vec[num].push_back(mas[j]);
            //int m = mas[j] / pow(p, i);
            //vec[m % p].push_back(mas[j]);
        }
        int l = 0;
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < vec[i].size(); j++)
            {
                mas[l] = vec[i][j];
                l++;
            }
        }
        for (int j = 0; j < n; ++j) {
            cout << mas[j] << ' ';
        }
        cout << endl;
        cout << endl;
        for (int i = 0; i < p; i++)
            vec[i].clear();
        i++;
    }
}

/*
void MSD(int *temp, int n, int max) {
    // p = 10
    int k = 0;
    while (max > 0) {
        k++;            // нашли максимальный разряд
        max/=10;
    }
    vector<vector<int>> digits (10); // создали 10 дополнительных векторо под разряды
    for (int i = 0; i < k; ++i) {
        cout << "JOPA" << endl;
        for (int j = 0; j < n; ++j) {
            string stroka = to_string(temp[j]);
            stroka = stroka[i];
            int num = stoi(stroka);
            cout << "num: " << num << " temp[j]: " << temp[j] << endl;
            digits[num].push_back(temp[j]);
        }
        for (int j = 0; j < k; ++j) {
            int counter = 0;
            for (auto c : digits[j]) {
                temp[counter] = c;
                counter++;
                cout << c << ' ';
            }
            cout << endl;
        }
        for (int j = 0; j < n; ++j) {
            cout << temp[j] << ' ';
        }
        cout << endl;
        for (int j = 0; j < n; ++j) {
            digits[j].clear();
        }
    }

}
*/
void print(int **mas, int n)
{
    for (int i = 0; i < n; ++i, out << endl)
    {
        for (int j = 0; j < n; ++j)
        {
            out << mas[i][j] << ' ';
        }
    }
}

int main()
{
    int n;
    in >> n;
    int **mas = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        mas[i] = new int[n];
    }
    int maxim = -1e9;
    while (in.peek() != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                in >> mas[i][j];
                if (mas[i][j] > maxim)
                    maxim = mas[i][j];
            }
        }
    }

    print(mas, n);
    int *temp = new int[n];
    int *res = new int[n];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            temp[j] = mas[i][j];
        }
        Sort(temp, n);
        for (int j = 0; j < n; ++j)
        {
            mas[i][j] = temp[j];
        }
    }
    out << endl
        << "Result: " << endl;
    print(mas, n);
}