#include <iostream>
#include <deque>
#include "Money.h"
using namespace std;

typedef deque<Money> Deq;

Deq make_deque(int n)
{
    Deq d;
    Money m;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        d.push_back(m);
    }
    return d;
}

void print_deque(Deq d)
{
    for (int i = 0; i < d.size(); i++)
        cout << d[i] << " ";
    cout << endl;
}

Money max_element(Deq d)
{
    Money m = d[0];
    for (int i = 1; i < d.size(); i++)
        if (d[i] > m) m = d[i];
    return m;
}

void add_max_to_end(Deq& d)
{
    Money m = max_element(d);
    d.push_back(m);
}

int find_key(Deq d, Money key)
{
    for (int i = 0; i < d.size(); i++)
        if (d[i] == key) return i;
    return -1;
}

void del_by_key(Deq& d, Money key)
{
    int pos = find_key(d, key);
    if (pos != -1)
        d.erase(d.begin() + pos);
}

Money srednee(Deq d)
{
    Money s;
    for (int i = 0; i < d.size(); i++)
        s = s + d[i];
    return s / (int)d.size();
}

void add_srednee(Deq& d)
{
    Money sr = srednee(d);
    for (int i = 0; i < d.size(); i++)
        d[i] = d[i] + sr;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Deq d;
    int n;
    cout << "Размер очереди: ";
    cin >> n;
    d = make_deque(n);

    cout << "Исходная очередь: ";
    print_deque(d);

    add_max_to_end(d);
    cout << "После добавления max в конец: ";
    print_deque(d);

    Money key;
    cout << "Ключ для удаления:" << endl;
    cin >> key;
    del_by_key(d, key);
    cout << "После удаления: ";
    print_deque(d);

    add_srednee(d);
    cout << "После добавления среднего: ";
    print_deque(d);

    system("pause");
    return 0;
}