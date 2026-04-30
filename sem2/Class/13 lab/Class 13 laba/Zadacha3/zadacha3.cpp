#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include "Money.h"
using namespace std;

typedef set<Money> TSet;
typedef vector<Money> TVector;
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

TSet make_set(int n)
{
    Money a;
    TSet st;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        st.insert(a);
    }
    return st;
}

void print_set(TSet st)
{
    TSet::iterator i;
    for (i = st.begin(); i != st.end(); i++)
        cout << *i << " ";
    cout << endl;
}

Money srednee(TSet st)
{
    Money sum;
    int n = 0;
    TSet::iterator i;
    for (i = st.begin(); i != st.end(); i++)
    {
        sum = sum + *i;
        n++;
    }
    return sum / n;
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
    TSet st = make_set(n);
    cout << "Исходное множество: ";
    print_set(st);

    TVector v(st.begin(), st.end());
    TVector::iterator i;
    i = max_element(v.begin(), v.end());
    cout << "max = " << *i << endl;
    Money m = *i;

    s = srednee(st);
    cout << "sred = " << s << endl;

    replace_if(v.begin(), v.end(), Greater_s(), m);
    st.clear();
    st.insert(v.begin(), v.end());
    cout << "После замены: ";
    print_set(st);

    v.assign(st.begin(), st.end());
    cout << "Сортировка по возрастанию:" << endl;
    sort(v.begin(), v.end());
    print_set(TSet(v.begin(), v.end()));

    cout << "Сортировка по убыванию:" << endl;
    sort(v.begin(), v.end(), Comp_less());
    print_set(TSet(v.begin(), v.end()));

    cout << "Введите ключ для поиска:" << endl;
    cin >> s;
    TSet::iterator si = find_if(st.begin(), st.end(), Equal_s());
    if (si != st.end())
        cout << "Найден: " << *si << endl;
    else
        cout << "Не найден" << endl;

    cout << "Введите ключ для удаления:" << endl;
    cin >> s;
    v.assign(st.begin(), st.end());
    i = remove_if(v.begin(), v.end(), Equal_s());
    v.erase(i, v.end());
    st.clear();
    st.insert(v.begin(), v.end());
    cout << "После удаления: ";
    print_set(st);

    v.assign(st.begin(), st.end());
    i = min_element(v.begin(), v.end());
    s = *i;
    cout << "min = " << s << endl;

    cout << "После деления на минимум:" << endl;
    for_each(v.begin(), v.end(), del);
    st.clear();
    st.insert(v.begin(), v.end());
    print_set(st);

    v.assign(st.begin(), st.end());
    s = srednee(st);
    for_each(v.begin(), v.end(), [](Money& t) { t = t + s; });
    st.clear();
    st.insert(v.begin(), v.end());
    cout << "К каждому элементу + среднее арифметическое:" << endl;
    print_set(st);

    return 0;
}