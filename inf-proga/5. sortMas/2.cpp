// 2. Строки по возрастанию с помощью сортировки подсчетом.
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("test.txt");
ofstream out("output.txt");

void counter_sort(int *temp1, int n)
{
    int min = temp1[0];
    int max = temp1[0];
    for (int i = 0; i < n; i++)
    {
        if (max < temp1[i])
            max = temp1[i];
        if (min > temp1[i])
            min = temp1[i];
    }
    int k = abs(max - min);
    int *B = new int[k];
    for (int i = min; i <= max; i++)
        B[i] = 0;
    int temp = min;
    while (temp <= max)
    {
        for (int i = 0; i < n; i++)
            if (temp1[i] == temp)
                B[temp]++;
        temp++;
    }
    int counter = 0;
    for (int i = min; i <= max; i++)
        if (B[i])
        {
            for (int j = 0; j < B[i]; j++)
                temp1[counter] = i;
                counter++;
        }
}

void print(int **mas, int n)
{
    for (int i = 0; i < n; i++, out << endl)
        for (int j = 0; j < n; j++)
            out << mas[i][j] << " ";
}

int main()
{
    int n;
    in >> n;
    int **mas = new int *[n];
    for (int i = 0; i < n; i++)
        mas[i] = new int[n];
    int temp;
    while (in.peek() != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                in >> temp;
                mas[i][j] = temp;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        int *temp1 = new int[n];
        for (int m = 0; m < n; m++) temp1[m] = mas[k][m];
        counter_sort(temp1, n);
        for (int m = 0; m < n; m++) mas[k][m] = temp1[m];
    }
    print(mas, n);

    return 0;
}