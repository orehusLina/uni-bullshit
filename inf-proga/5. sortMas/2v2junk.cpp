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
/*
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
*/
void print(vector<vector<int>> &num, int n)
{ // вывод в файлs
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            out << num[i][j] << ' ';
        }
        out << endl;
    }
}
vector<int> counter_sort(vector<int> num, int n)
{
    int minim = num[0];
    int maxim = num[0];
    vector<int> temp_res;
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
    int counter = 0;
    for (int i = minim; i <= maxim; i++) 
    {
        if (B[i])
        {
            for (int j = 0; j < B[i]; j++) 
            {
                num[counter] = i;
                counter++;
                temp_res.push_back(i);
            }
        }
    }
    return temp_res;
}


int main()
{
    int temp; int n; in >> n;
    vector<int> num; 
    vector<vector<int>> numbers (n);
    while (in.peek() != EOF)
    {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in >> temp;
                numbers[i].push_back(temp);
            }
        }
        /*
        for (auto c : num) cout << c << ' ';
        cout << endl;
        //ounter_sort(num, n);
        //for (auto c : num) cout << c << ' ';
        num.clear();
        cout << endl << endl;
        */
    }
    vector<int> temp_vec;
    for (int i = 0; i < n; ++i) {
        temp_vec = counter_sort(numbers[i], n);
        for (auto c : temp_vec) cout << c << ' ';
        cout << endl;
        temp_vec.clear();
    }


    /*
    vector<int> test;
    test.push_back(4567);
    test.push_back(8765);
    test.push_back(899);
    test.push_back(1400);
    for (auto c : test) cout << c <<' ';
    cout << endl;
    counter_sort(test, 4);
    for (auto c : test) cout << c <<' ';
    
    */

    /*
    int n; in >> n;
    vector<vector<int>> num (n);
    vector<int> res;
    vector<int> temp;
    temp = inFile();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            num[i].push_back(temp[i*n + j]);
        }
        for (auto c : num[i]) cout << c <<' ';
        res = counter_sort(num[i], n);
        for (auto c : res) cout << c <<' ';
        cout << endl;
    }
    //print (num, n);
    */
}