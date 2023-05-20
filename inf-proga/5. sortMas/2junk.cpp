// 2. Строки по возрастанию с помощью сортировки подсчетом.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <iomanip>
using namespace std;

ifstream in("test.txt");
ofstream out("output.txt");

vector<int> inFile()
{ // ввод из файла
    vector<int> numbers;
    int temp;
    while (in.peek() != EOF)
    {
        in >> temp;
        numbers.push_back(temp);
    }
    return numbers;
}

void print(vector<int> &numbers)
{ // вывод в файлs
    int n = sqrt(numbers.size());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            out << numbers[i * n + j] << ' ';
        }
        out << endl;
    }
}
vector<int> counter_sort(vector<int>& num, int n, vector<int>&res)
{
    vector<int> temp_res;
    int minim = num[0];
    int maxim = num[0];
    for (int i = 0; i < n; i++)
    {
        if (maxim < num[i])
            maxim = num[i];
        if (minim > num[i])
            minim = num[i];
    }
    int k = abs(maxim - minim);
    int *B = new int[k];
    for (int i = minim; i <= maxim; i++)
        B[i] = 0;
    int temp = minim;
    while (temp <= maxim)
    {
        for (int i = 0; i < n; i++)
            if (num[i] == temp)
                B[temp]++;
        temp++;
    }
    //int counter = 0;
    for (int i = minim; i <= maxim; i++) 
    {
        if (B[i])
        {
            for (int j = 0; j < B[i]; j++) 
            {
                res.push_back(i);
                //counter++;
            }
        }
    }
    return temp_res;
}

int counterSortMas(vector<int>& num, int n, vector<int>& res) {
    int dim = sqrt(n);
    vector<int> temp;
    vector<int> temp_res;
    for (int i = 0; i < dim; ++i) {
        cout << "J";
        for (int j = 0; j < dim; ++j) {
            cout << num[i*dim+j] << ' ';
            temp.push_back(num[i*dim+j]);
        }

        temp_res = counter_sort(temp, dim,);
        cout <<"TEMP0" << temp_res[0];
        for (int c : temp) { cout << c << ' ' ; res.push_back(c); }
        for (int c : res) cout << c << ' ';
        temp.clear();
    }
}

int main()
{
    vector<int> num;
    vector<int> res;
    num = inFile();
    int n = num.size();
    counterSortMas(num, n, res);
    cout << res[0];
    print(res);
    vector<int> test;
    for (int i = 200; i > 150; i -= 10) {
        test.push_back(i);
    }
    for (auto c : test) cout << c << ' ';
    cout << endl;
    counter_sort(test, test.size());
    for (auto c : test) cout << c << ' ';
    return 0;
}