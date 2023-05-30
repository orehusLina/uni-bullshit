// Основная — линейное хеширование, вспомогательная — метод деления по году
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
using namespace std;
ifstream in("test.txt");

struct people
{
    string userName, job;
    int day_birth, month_birth, year_birth;
    int worktime, salary;
    
    void get(string& s)
    {
        vector<string> vec;
        s += ' ';
        string str = "";
        
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
};


const int m = 20;
const int mod = 10;
people null;
bool isEqual(people x, people y)
{
    return (x.userName == y.userName && x.job == y.job && x.day_birth == y.day_birth &&
        x.month_birth == y.month_birth && x.year_birth == y.year_birth &&
        x.worktime == y.worktime && x.salary == y.salary);
}

void print(people x)
{
    if (isEqual(x, null)) cout << "NULL\n";
    else cout << x.userName << ' ' << x.job << ' ' << x.day_birth << '.' << x.month_birth 
    << '.' << x.year_birth << ' ' << x.worktime << ' ' << x.salary << '\n';
}
void set_null(people& p)
{
    p.userName = "";
    p.job = "";
    p.day_birth = 0;
    p.month_birth = 0;
    p.year_birth = 0;
    p.worktime = 0;
    p.salary = 0;
}

void hash_input(people p, vector<people>& hash_table)
{
    int j = 0;
    while (j != m)
    {
        int hash = (p.day_birth % mod + j) % m;
        if (isEqual(hash_table[hash], null))
        {
            hash_table[hash] = p;
            break;
        }
        else ++j;
    }
}

void print_table(vector<people>& hash_table)
{
    for (int i = 0; i < m; ++i)
    {
        cout << i << ": \t";
        print(hash_table[i]);
    }
}

bool find(people p, vector<people>& hash_table)
{
    int j = 0;
    int hash = (p.day_birth % mod + j) % m;
    while (!isEqual(hash_table[hash], null))
    {
        if (isEqual(hash_table[hash], p)) return 1;
        ++j;
        hash = (p.day_birth % mod + j) % m;
    }
    return 0;
}

int main()
{
    set_null(null);
    vector<people> hash_table(m, null);
    string s;
    people p;
    
    while (!in.eof())
    {
        getline(in, s);
        p.get(s);
        hash_input(p, hash_table);
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
        cout << "\n";
    }
}