#include <iostream>
#include <set>
#include "Money.h"
using namespace std;

typedef set<Money> TSet;
typedef TSet::iterator it;

TSet make_set(int n)
{
    TSet s;
    Money m;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        s.insert(m);
    }
    return s;
}

void print_set(TSet s)
{
    for (it i = s.begin(); i != s.end(); i++)
        cout << *i << " ";
    cout << endl;
}

Money max_element(TSet s)
{
    it i = s.begin();
    Money m = *i;
    while (i != s.end())
    {
        if (*i > m) m = *i;
        i++;
    }
    return m;
}

void add_max_to_end(TSet& s)
{
    Money m = max_element(s);
    s.insert(m);
}

it find_key(TSet s, Money key)
{
    it i = s.begin();
    while (i != s.end())
    {
        if (*i == key) return i;
        i++;
    }
    return s.end();
}

void del_by_key(TSet& s, Money key)
{
    it pos = find_key(s, key);
    if (pos != s.end())
        s.erase(pos);
}

Money srednee(TSet s)
{
    Money sum;
    int n = 0;
    it i = s.begin();
    while (i != s.end())
    {
        sum = sum + *i;
        n++;
        i++;
    }
    return sum / n;
}

void add_srednee(TSet& s)
{
    Money sr = srednee(s);
    TSet temp;
    it i = s.begin();
    while (i != s.end())
    {
        temp.insert(*i + sr);
        i++;
    }
    s = temp;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    TSet s;
    int n;
    cout << "N? ";
    cin >> n;
    s = make_set(n);

    cout << "Исходное множество: ";
    print_set(s);

    cout << "Добавление максимального элемента в конец" << endl;
    add_max_to_end(s);
    print_set(s);

    Money key;
    cout << "Введите ключ для удаления:" << endl;
    cin >> key;
    del_by_key(s, key);
    cout << "После удаления: ";
    print_set(s);

    cout << "Каждый элемент + среднее арифметическое" << endl;
    add_srednee(s);
    print_set(s);

    return 0;
}