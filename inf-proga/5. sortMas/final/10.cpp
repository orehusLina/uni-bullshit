// 10. Нечетные строки по убыванию, четные по возрастанию помощью гномьей сортировки.
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("test.txt");
ofstream out("output.txt");

void dwarf_sort(int **mas, int n)
{
    int temp[n]; 
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
                temp[i] = mas[k][i];
            }
        if (k%2 == 1) {
            int i = 1;
            while (i < n) {
                if (i == 0) i++;
                if (temp[i-1] <= temp[i]) i++;
                else {
                    swap(temp[i-1], temp[i]);
                    i--;
                }
            }
        }
        else {
            int i = 1;
            while (i < n) {
                if (i == 0) i++;
                if (temp[i-1] >= temp[i]) i++;
                else {
                    swap(temp[i-1], temp[i]);
                    i--;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            mas[k][i] = temp[i];
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
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)

                in >> mas[i][j];
    }
    print(mas, n);
    dwarf_sort(mas, n);
    out << endl;
    out << "Sorted: " << endl;
    print(mas, n);
    return 0;
}