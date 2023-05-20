// Создать стек, содержащий целые числа. Перед  всеми максимальными числами вставить минимальное число. Порядок следования в результате должен совпадать с порядком следования ввода. Например, было 2 8 4 1 2 8 8 1 2 8 Стало 2 1 8 4 1 2 1 8 1 8 1 2 1 8
#include <iostream>
using namespace std;

struct stack   // создаем структуру стек
{
    int inf;
    stack *next;
};

void push(stack *&h, int x) // функция добавления элемента в стек
{ // вставка
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

char pop(stack *&h)  // функция извлечения элемента из стека
{ // удаление
    int i = h -> inf;
    stack *r = h;
    h = h -> next;
    delete r;
    return i;
}

int main()
{
    char a, b;
    stack *head = NULL;                // инициализируем указатель на стек
    cout << "n = ";
    int n; cin >> n; int x;
    cout << "Enter elements: "; // интерфейс
    for (int i = 0; i < n; ++i) {   // ввод чисел
        cin >> x;
        push(head, x);
    }
    stack *tempHead = NULL; // указатель на временный стек
    int minim = 1e9, maxim = -1e9;
    for (int i = 0; i < n; ++i) { // проходим по стеку и находим максимальный и минимальный элементы
        x = pop(head);
        if (x > maxim) maxim = x;
        if (x < minim) minim = x;
        push(tempHead, x);   // добавляем все элементы во временный стек
    }
    int counter = n;
    for (int i = 0; i < n; ++i) {
        x = pop(tempHead);  // достаем элементы из временного стека
        if (x == maxim) {   // если находим максимальный элемент, то вставляем перед ним минимум
            push(head, minim);
            counter++;
        }
        push(head, x);  // вставляем сам элемент на место
    }
    for (int i = 0; i < counter; ++i) {  // стек готов, но для вывода добавляем еще два переворачивающих его цикла
        x = pop(head);
        push(tempHead, x);
    }
    cout << "Result: ";
    for (int i = 0; i < counter; ++i) {
        x = pop(tempHead);
        cout << x << ' '; 
    }
}