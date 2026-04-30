#include <iostream>
#include <deque>
#include <algorithm>
#include <functional>
#include "Money.h"
using namespace std;

typedef deque<Money> TDeque;
Money s;

struct Greater_s
{
    bool operator()(Money t)
    {
        if (t > s) return true;
        return false;
    }
};

struct Comp_less
{
    bool operator()(Money t1, Money t2)
    {
        if (t1 > t2) return true;
        return false;
    }
};

struct Equal_s
{
    bool operator()(Money t)
    {
        return t == s;
    }
};

TDeque make_deque(int n)
{
    Money a;
    TDeque d;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        d.push_back(a);
    }
    return d;
}

void print_deque(TDeque d)
{
    for (int i = 0; i < d.size(); i++)
        cout << d[i] << " ";
    cout << endl;
}

Money srednee(TDeque d)
{
    Money sum = d[0];
    for (int i = 1; i < d.size(); i++)
        sum = sum + d[i];
    return sum / (int)d.size();
}

void del(Money& t)
{
    t = t / s;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "N? ";
    cin >> n;
    TDeque d;
    d = make_deque(n);
    cout << "Исходная очередь: ";
    print_deque(d);

    TDeque::iterator i;
    i = max_element(d.begin(), d.end());
    cout << "max = " << *i << endl;
    Money m = *i;

    s = srednee(d);
    cout << "sred = " << s << endl;

    replace_if(d.begin(), d.end(), Greater_s(), m);
    cout << "После замены: ";
    print_deque(d);

    cout << "Сортировка по возрастанию:" << endl;
    sort(d.begin(), d.end());
    print_deque(d);

    cout << "Сортировка по убыванию:" << endl;
    sort(d.begin(), d.end(), Comp_less());
    print_deque(d);

    cout << "Введите ключ для поиска:" << endl;
    cin >> s;
    i = find_if(d.begin(), d.end(), Equal_s());
    if (i != d.end())
        cout << "Найден: " << *i << endl;
    else
        cout << "Не найден" << endl;

    cout << "Введите ключ для удаления:" << endl;
    cin >> s;
    i = remove_if(d.begin(), d.end(), Equal_s());
    d.erase(i, d.end());
    cout << "После удаления: ";
    print_deque(d);

    i = min_element(d.begin(), d.end());
    s = *i;
    cout << "min = " << s << endl;

    cout << "После деления на минимум:" << endl;
    for_each(d.begin(), d.end(), del);
    print_deque(d);

    cout << "К каждому элементу + среднее арифметическое:" << endl;
    s = srednee(d);
    for_each(d.begin(), d.end(), [](Money& t) { t = t + s; });
    print_deque(d);

    return 0;
}