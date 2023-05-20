// 12. Диагонали, параллельные главной по возрастанию с помощью сортировки чет-нечет.
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("test.txt");
ofstream out("output.txt");

void parity_sort(int *mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 2; j <= n - 1; j += 2)
                if (mas[j - 1] > mas[j])
                    swap(mas[j - 1], mas[j]);
        }
        else
        {
            for (int j = 1; j <= n - 1; j += 2)
                if (mas[j - 1] > mas[j])
                    swap(mas[j - 1], mas[j]);
        }
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

    while (in.peek() != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                in >> mas[i][j];
            }
        }
    }
    print(mas, n);
    int l = 2;
    for (int k = n - 2; k >= 0; k--)
    {
        int *temp1 = new int[l];
        int *temp2 = new int[l];
        for (int m = 0; m < l; m++)
        {
            temp1[m] = mas[k + m][m];
            temp2[m] = mas[m][k + m];
        }
        parity_sort(temp1, l);
        parity_sort(temp2, l);
        for (int m = 0; m < l; m++)
        {
            mas[k + m][m] = temp1[m];
            mas[m][k + m] = temp2[m];
        }
        l++;
    }
    out << endl << "Sorted: " << endl;
    print(mas, n);
    return 0;
}