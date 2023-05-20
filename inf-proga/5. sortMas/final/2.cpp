//2. Строки по возрастанию с помощью сортировки подсчетом.
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("test.txt");
ofstream out("output.txt");

void counter_sort(int *temp, int *res, int n) {
    int maxim = -1e9, minim = 1e9;
    for (int i = 0; i < n; ++i) {
        if (temp[i] > maxim) maxim = temp[i];
        if (temp[i] < minim) minim= temp[i];
    }
    int k = maxim - minim + 1;
    int B[maxim+1];
    for (int i = 0; i <= maxim; ++i) {
        B[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        B[temp[i]]++;
    }
    int counter = 0;
    for (int i = minim; i <= maxim; ++i) {
        for (int j = 0; j < B[i]; ++j) {
            res[counter] = i;
            counter++;
        }
    }
}

void print(int **mas, int n) {
    for (int i = 0; i < n; ++i, out << endl) {
        for (int j = 0; j < n; ++j) {
            out << mas[i][j] << ' ';
        }
    }
}

int main() {
    int n; in >> n;
    int **mas = new int *[n];
    for (int i = 0; i < n; ++i) {
        mas[i] = new int[n];
    }

    while (in.peek() != EOF) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in >> mas[i][j];
            }
        }
    }

    print(mas, n);
    int *temp = new int[n]; int *res = new int[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            temp[j] = mas[i][j];
        }
        for (int j = 0; j < n; ++j) {
            res[j] = 0;
        }
        counter_sort(temp, res, n);
        for (int j = 0; j < n; ++j) {
            mas[i][j] = res[j];
        }
    }
    out << endl << "Result: " << endl;
    print(mas, n);
}