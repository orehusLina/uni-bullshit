// выбором
#include <iostream>
using namespace std;
int main()
{
    int n = 9; int counter = 0;
    int mas[n] = {8, 1, 2, 5, 10, 3, 9, 6, 7};
    for (int i = 0; i < n; i++)
    {
        cout << i << endl;  counter++;
        int min = mas[i];
        int min_index = i;
        for (int j = i + 1; j <= n - 1; j++) {
            if (min > mas[j])
            {
                min_index = j;
                min = mas[j];
            }
        }
        for (int k = 0; k < n; k++)
        cout << mas[k] << " ";
        cout << endl;

        if (i != min_index) {
            swap(mas[i], mas[min_index]);
            for (int q = 0; q < n; q++)
            cout << mas[q] << " ";
            cout << endl; counter++;
        }
    }
    cout << counter;
    return 0;
}