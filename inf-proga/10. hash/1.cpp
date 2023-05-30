// Метод деления по дню рождения
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
ifstream in("test.txt");
// 
const int mod = 10;

struct people
{
    string userName, job;
    int day_birth, month_birth, year_birth;
    int worktime, salary;
    // 
    void get(string& s)
    {
        vector<string> vec;
        s += ' ';
        string str = "";
        // 
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == ' ' || s[i] == '.')
            {
                if (!str.empty()) vec.push_back(str);
                str.clear();
            }
            else str += s[i];
        }
        userName = vec[0];
        job = vec[1];
        day_birth = stoi(vec[2]);
        month_birth = stoi(vec[3]);
        year_birth = stoi(vec[4]);
        worktime = stoi(vec[5]);
        salary = stoi(vec[6]);
    }
    // 
    void print()
    {
        cout << userName << ' ' << job << ' ' << day_birth << '.' <<
         month_birth << '.' << year_birth << ' ' << worktime << ' ' << salary << '\n';
    }
};

struct list
{
    // 
    people value;
    list* next;
    list* prev;
};

void push_back(list*& s, list*& e, people x)
{
    list* r = new list;
    r->value = x;
    r->next = NULL;
    // 
    if (!s && !e)
    {
        r->prev = NULL;
        s = r;
    }
    else
    {
        e->next = r;
        r->prev = e;
    }
    e = r;
}
void erase(list*& s, list*& e, list*& it)
{
    if (it == s && it == e)
    {
        s = NULL; e = NULL;
    }
    else if (it == s)
    {
        s = s->next;
        s->prev = NULL;
    }
    else if (it == e)
    {
        e = e->prev;
        e->next = NULL;
    }
    else
    {
        it->prev->next = it->next;
        it->next->prev = it->prev;
    }
    delete it;
}

bool isEqual(people x, people y)
{
    return (x.userName == y.userName && x.job == y.job && x.day_birth == y.day_birth &&
        x.month_birth == y.month_birth && x.year_birth == y.year_birth &&
        x.worktime == y.worktime && x.salary == y.salary);
}

void hash_input(people p, vector<pair<list*, list*>>& hash_table)
{
    int hash = p.year_birth % mod;
    list*& e = hash_table[hash].second;
    list*& s = hash_table[hash].first;
    push_back(s,e,p);
}

void print_table(vector<pair<list*, list*>>& hash_table)
{
    for (int i = 0; i < mod; ++i)
    {
        cout << i << ": "; 
        list*& s = hash_table[i].first;
        list*& e = hash_table[i].second;
        for (auto it = s; it != NULL; it = it->next)
        {
            cout << '\t';
            it->value.print();
        }
        cout << '\n';
    }
}

bool find(people p, vector<pair<list*, list*>>& hash_table)
{
    int hash = p.year_birth % mod; 
    list*& s = hash_table[hash].first;
    list*& e = hash_table[hash].second;
    for (auto it = s; it != NULL; it = it->next)
    {
        if (isEqual(it->value, p)) return 1;
    }
    return 0;
}

void del(people p, vector<pair<list*, list*>>& hash_table)
{
    int hash = p.year_birth % mod;
    list*& s = hash_table[hash].first;
    list*& e = hash_table[hash].second;
    for (auto it = s; it != NULL; it = it->next)
    {
        if (isEqual(it->value, p))
        {
            erase(s,e,it);
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    vector<pair<list*, list*>> hash_table(mod);
    for (int i = 0; i < mod; ++i) hash_table[i] = { NULL, NULL };
    string s;
    people p;
    
    while (!in.eof())
    {
        getline(in, s);
        p.get(s);
        hash_input(p,hash_table);
    }
    print_table(hash_table);
    cout << ":\n";
    getline(cin, s);
    p.get(s);
    if (!find(p, hash_table))
    {
        cout << "\n";
    }
    else
    {
        cout << "Do you want to delete this person? [Y/n]\n";
        char c;
        cin >> c;
        if (c == 'Y')
        {
            del(p, hash_table);
            print_table(hash_table);
        }
    }
}