//Дано математическое выражение в постфиксной форме. Вычислить его значение
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

int operation(char op, int a, int b) {  // функция, возвращающая резулуьтат применения операции к двум числам 
    if (op=='+') return a+b;            
    else if (op == '*') return a*b;
    else if (op == '/') return a/b;
    else if (op == '-') return a-b;
}

int main()
{
    char a, b;
    stack *head = NULL;                // инициализируем указатель на стек
    cout << "Enter string in postfix form: " << endl; // интерфейс
    string s; cin >> s;                // считываем строку (постфиксная запись выражения)
    int res;                           // инициализируем результат
    for (char c : s) {                 // цикл по элементам строки
        if (isdigit(c)) {              // если символ является цифрой
            push (head, int(c - '0')); // добавляем его в стек (предварительно кастуем char к int)
        }
        else {                         // если нам встретилась операция
            b = pop(head);             // извлекаем 2 верхних элемента стека (числа)
            a = pop(head);
            res = operation(c, a, b);  // применяем к ним встреченную операцию
            push(head, res);           // записываем результат в стек
        }
    }
    cout << "Result: " << res;                       // выводим результат
    // на примере 532431-*+2+4/+1+4*+ дает корректный результат 33
    return 0;
}