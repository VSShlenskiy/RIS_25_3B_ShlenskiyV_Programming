#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>
#include "Money.h"
using namespace std;

typedef stack<Money> TStack;
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

TStack make_stack(int n)
{
    Money a;
    TStack st;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        st.push(a);
    }
    return st;
}

TVector copy_stack_to_vector(TStack st)
{
    TVector v;
    while (!st.empty())
    {
        v.push_back(st.top());
        st.pop();
    }
    return v;
}

TStack copy_vector_to_stack(TVector v)
{
    TStack st;
    for (int i = 0; i < v.size(); i++)
        st.push(v[i]);
    return st;
}

void print_stack(TStack st)
{
    TVector v = copy_stack_to_vector(st);
    for (int i = v.size() - 1; i >= 0; i--)
        cout << v[i] << " ";
    cout << endl;
}

Money srednee(TVector v)
{
    Money sum = v[0];
    for (int i = 1; i < v.size(); i++)
        sum = sum + v[i];
    return sum / (int)v.size();
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
    TStack st = make_stack(n);
    cout << "Исходный стек: ";
    print_stack(st);

    TVector v = copy_stack_to_vector(st);
    TVector::iterator i;
    i = max_element(v.begin(), v.end());
    cout << "max = " << *i << endl;
    Money m = *i;

    s = srednee(v);
    cout << "sred = " << s << endl;

    replace_if(v.begin(), v.end(), Greater_s(), m);
    cout << "После замены: ";
    st = copy_vector_to_stack(v);
    print_stack(st);

    v = copy_stack_to_vector(st);
    cout << "Сортировка по возрастанию:" << endl;
    sort(v.begin(), v.end());
    print_stack(copy_vector_to_stack(v));

    cout << "Сортировка по убыванию:" << endl;
    sort(v.begin(), v.end(), Comp_less());
    st = copy_vector_to_stack(v);
    print_stack(st);

    cout << "Введите ключ для поиска:" << endl;
    cin >> s;
    v = copy_stack_to_vector(st);
    i = find_if(v.begin(), v.end(), Equal_s());
    if (i != v.end())
        cout << "Найден: " << *i << endl;
    else
        cout << "Не найден" << endl;

    cout << "Введите ключ для удаления:" << endl;
    cin >> s;
    v = copy_stack_to_vector(st);
    i = remove_if(v.begin(), v.end(), Equal_s());
    v.erase(i, v.end());
    st = copy_vector_to_stack(v);
    cout << "После удаления: ";
    print_stack(st);

    v = copy_stack_to_vector(st);
    i = min_element(v.begin(), v.end());
    s = *i;
    cout << "min = " << s << endl;

    cout << "После деления на минимум:" << endl;
    for_each(v.begin(), v.end(), del);
    st = copy_vector_to_stack(v);
    print_stack(st);

    v = copy_stack_to_vector(st);
    s = srednee(v);
    for_each(v.begin(), v.end(), [](Money& t) { t = t + s; });
    st = copy_vector_to_stack(v);
    cout << "К каждому элементу + среднее арифметическое:" << endl;
    print_stack(st);

    return 0;
}