//Дано математическое выражение в постфиксной форме. Вычислить его значение
#include <iostream>
using namespace std;
int operation(char op, int a, int b) {
    if (op=='+') return a+b;
    else if (op == '*') return a*b;
    else if (op == '/') return a/b;
    else if (op == '-') return a-b;
}

struct stack
{
    int inf;
    stack *next;
};
void push(stack *&h, int x)
{ // вставка
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

char pop(stack *&h)
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
    stack *head = NULL; // инициализация
    string s; cin >> s; int res;
    for (char c : s) {
        if (isdigit(c)) {
            push (head, int(c-'0'));
        }
        else {
            b = pop(head);
            a = pop(head);
            res = operation(c, a, b);
            push(head, res);
        }
    }
    cout << res;
    /*
    char x; string s; cin >> s;
    for (char c : s)
    { // создаем стек
        push(head, c);
    }
    int res = -1e9; 
    char now;
    int a, b;
    while(head) {
        now = pop(head);
        cout << now << endl;
        if (!(isdigit(now))) {
            a = int(pop(head)-'0');
            b = int(pop(head)-'0');
            // + − ∗/
            res = operation(now, a, b);
            push(head, char(res));
        }
    }
    cout << res;
    */
    return 0;
}





/*
void reverse(stack *&h)
{                            //"обращение"стека
    stack *head1 = NULL;     // инициализация буферного стека
    while (h)                // пока стек не пуст
        push(head1, pop(h)); // переписываем из одного стека в другой
    h = head1;               // переобозначаем указатели
}

stack *result(stack *&h)
{
    stack *res = NULL; // инициализация
    stack *h1 = NULL;
    while (h)
    {
        int x = pop(h); // удаляем первый элемент
        push(res, x);   // записываем в результат
        while (h)
        {
            int y = pop(h); // удаляем элемент из стека
            if (x != y)
                push(h1, y); // записываем в новый стек
        }
        reverse(h1); // переворачиваем стек
        h = h1;      // переобозначаем указатели
        h1 = NULL;
    }
    reverse(res); // переворачиваем результирующий стек
    return res;
}
*/