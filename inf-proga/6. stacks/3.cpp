// Создать очередь, содержащую целые числа. После всех чисел, равных максимальному числу, вставить последний нечетный элемент. Например, было  2 8 2 1 6 8 8 1 2 2 8 2 1. Стало  2 8 1 2 1 6 8 1 8 1 1 2 2 8 1 2 1 
#include <iostream>
using namespace std;

struct queue
{
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x)
{
    queue *r = new queue; // создаём новый элемент
    r->inf = x;           // заполняем его информационное поле
    r->next = NULL;       // заполняем ссылочное поле
    if (!h && !t)
    {              // если очередь пуста
        h = t = r; // это голова и хвост ссылаются на этот новый элемент r
    }
    else
    {
        t->next = r; // r будет следующим элементом после хвоста t
        t = r;       // переносим указатель хвоста t на r
    }
}

int pop(queue *&h, queue *&t)
{
    int i = h->inf; // значение информационного поля головы h, т.е. первого элемента
    queue *r = h;      // создаём указатель на голову
    h = h->next;       // переносим указатель h на следующий элемент
    if (!h)            // если h=NULL, т.е. в очереди был один элемент
        t = NULL;      // то и хвост станет NULL
    delete r;          // удаляем первый элемент
    return i;          // возвращаем значение
}

void result(queue *&h, queue *&t)
{
    queue *h_temp = NULL, *t_temp = NULL; // инициализируем временную очередь
    int x; int maxim = -1e9; int odd = 0;
    while (h && t)
    {                  // пока исходная очередь не пуста
        x = pop(h, t); // извлекаем элемент из очереди
        if (x > maxim) maxim = x;  // находим максимальное число
        if (x%2 == 1) odd = x;   // находим последнее нечетное
        push(h_temp, t_temp, x);  // добавляем элементы во временную очередь
    }
    bool flag = 0;
    while (h_temp && t_temp) {  // пока временная очередь не пуста
        x = pop(h_temp, t_temp); // достаем из нее элементы
        push(h, t, x);  // добавляем их в результирующую очередь
        if (x == maxim) { // если текущий элемент максимальный, то после него вставляем еще и минимальный
            push(h, t, odd);
        }
    }
}
int main()
{
    queue *h = NULL, *t = NULL; // инициализируем очередь
    int n; cout << "n = "; cin >> n; 
    int x;
    cout << "Input elements: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> x;      // вводим число
        push(h, t, x); // добавляем число в очередь
    }
    // вызываем функцию, которая меняет очередь в соответствии с заданием
    result(h, t);
    cout << "New queue\n";
    while (h && t)                // пока очередь не пуста
        cout << pop(h, t) << " "; // выводим элемент очереди на экран
    return 0;
}