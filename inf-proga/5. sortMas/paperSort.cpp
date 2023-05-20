// вставками
#include <iostream>
using namespace std;
int main()
{
    int n = 9; int counter = 1;
    int mas[n] = {2, 5, 1, 3, 8, 9, 4, 10, 6};
    int i = 0;
    while (i <= n - 1)
    {
        cout << i << endl; counter++;
        for (int i = 0; i < n; i++) cout << mas[i] << " ";
        cout << endl; counter++;
        int j = i;
        while (mas[j] < mas[j - 1] && j > 0)
        {
            swap(mas[j - 1], mas[j]); counter++;
            for (int i = 0; i < n; i++) cout << mas[i] << " ";
            cout << endl;
            j--;
        }
        i++;
    }
    cout << counter;
    //for (int i = 0; i < n; i++) cout << mas[i] << " ";
    return 0;
}