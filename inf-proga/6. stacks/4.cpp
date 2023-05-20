// Создать стек, содержащий буквы латинского алфавита. В новый стек записать сначала гласные, потом согласные буквы. Порядок следования букв в новом стеке должен совпадать с первоначальным. Например, было q w e r t u i o p s d a.  Cтало  e u i o a q w r t p s d
#include <iostream>
using namespace std;

struct stack   // создаем структуру стек
{
    char inf;
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
    char i = h -> inf;
    stack *r = h;
    h = h -> next;
    delete r;
    return i;
}
bool isVowel(char c) {  // функция, определяющая гласные
    if (c=='a' || c=='e' || c=='o' || c=='u' || c=='i' || c=='y') return true;
    else return false;
}

int main()
{
    char a, b;
    stack *head = NULL;                // инициализируем указатель на стек
    cout << "n = ";
    int n; cin >> n; char x;
    cout << "Enter letters: \n";
    for (int i = 0; i < n; ++i) {  // ввод букв
        cin >> x;
        push(head, x);
    }
    stack *vowelsHead = NULL; int counter_vow = 0;  // указатель на стек гласных + счетчик
    stack *consonantsHead = NULL; int counter_con = 0; // указатель на стек согласные + счетчик
    for (int i = 0; i < n; ++i) {
        x = pop(head);  // достаем элементы из главного стека
        if (isVowel(x)) { push(vowelsHead, x); counter_vow++; } // распределяем их по стекам гласных и согласных
        else { push(consonantsHead, x); counter_con++; }
    }
    for (int i = 0; i < counter_vow; ++i) {
        x = pop(vowelsHead); //добавляем все гласные в результирующий стек
        push(head, x);
    }
    for (int i = 0; i < counter_con; ++i) {
        x = pop(consonantsHead); // добавляем все согласные в результирующий стек
        push(head, x);
    }
    stack *tempHead = NULL;
    for (int i = 0; i < n; ++i) {  // переворачиваем стек для корректного вывода
        x = pop(head);
        push(tempHead, x);
    }
    cout << "Result: ";
    for (int i = 0; i < n; ++i) {
        x = pop(tempHead);
        cout << x << ' '; 
    }
}