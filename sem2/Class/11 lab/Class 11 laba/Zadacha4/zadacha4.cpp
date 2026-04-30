#include <iostream>
#include <stack>
#include <vector>
#include "Money.h"

typedef std::stack<Money> St;
typedef std::vector<Money> Vec;

St make_stack(int n)
{
    St s;
    Money t;
    for (int i = 0; i < n; i++)
    {
        std::cin >> t;
        s.push(t);
    }
    return s;
}

Vec copy_stack_to_vector(St s)
{
    Vec v;
    while (!s.empty())
    {
        v.push_back(s.top());
        s.pop();
    }
    return v;
}

St copy_vector_to_stack(Vec v)
{
    St s;
    for (int i = 0; i < v.size(); i++)
        s.push(v[i]);
    return s;
}

void print_stack(St s)
{
    Vec v = copy_stack_to_vector(s);
    for (int i = v.size() - 1; i >= 0; i--)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

Money max_element(St s)
{
    Money m = s.top();
    St temp = s;
    while (!temp.empty())
    {
        if (temp.top() > m) m = temp.top();
        temp.pop();
    }
    return m;
}

void add_max_to_end(St& s)
{
    Money m = max_element(s);
    Vec v = copy_stack_to_vector(s);
    v.push_back(m);
    s = copy_vector_to_stack(v);
}

void delete_by_key(St& s, Money key)
{
    Vec v;
    Money t;
    bool deleted = false;
    while (!s.empty())
    {
        t = s.top();
        s.pop();
        if (!deleted && t == key)
        {
            deleted = true;
        }
        else
        {
            v.push_back(t);
        }
    }
    for (int i = v.size() - 1; i >= 0; i--)
        s.push(v[i]);
}

Money srednee(St s)
{
    Money sum;
    int n = 0;
    while (!s.empty())
    {
        sum = sum + s.top();
        s.pop();
        n++;
    }
    return sum / n;
}

void add_srednee_to_all(St& s)
{
    Money sr = srednee(s);
    Vec v;
    while (!s.empty())
    {
        v.push_back(s.top() + sr);
        s.pop();
    }
    for (int i = v.size() - 1; i >= 0; i--)
        s.push(v[i]);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    St s;
    int n;
    Money key;
    std::cout << "N? ";
    std::cin >> n;
    s = make_stack(n);
    std::cout << "Исходный стек: ";
    print_stack(s);

    std::cout << "Добавление максимального в конец" << std::endl;
    add_max_to_end(s);
    print_stack(s);

    std::cout << "Введите ключ для удаления:" << std::endl;
    std::cin >> key;
    delete_by_key(s, key);
    std::cout << "После удаления: ";
    print_stack(s);

    std::cout << "Добавление среднего арифметического к каждому элементу" << std::endl;
    add_srednee_to_all(s);
    print_stack(s);

    return 0;
}