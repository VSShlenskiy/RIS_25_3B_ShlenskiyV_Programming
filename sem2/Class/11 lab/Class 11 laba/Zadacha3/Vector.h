#pragma once
#include <deque>
#include <iostream>

template<class T>
class Vector
{
    std::deque<T> d;
    int len;
public:
    Vector();
    Vector(int n);
    ~Vector();
    void Print();
    T Max();
    void AddMaxToEnd();
    int Find(T key);
    void DelByKey(T key);
    T Srednee();
    void AddSredneeToAll();
};

template<class T>
Vector<T>::Vector()
{
    len = 0;
}

template<class T>
Vector<T>::Vector(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        d.push_back(a);
    }
    len = d.size();
}

template<class T>
Vector<T>::~Vector() {}

template<class T>
void Vector<T>::Print()
{
    for (int i = 0; i < d.size(); i++)
        std::cout << d[i] << " ";
    std::cout << std::endl;
}

template<class T>
T Vector<T>::Max()
{
    T m = d[0];
    for (int i = 1; i < d.size(); i++)
        if (d[i] > m) m = d[i];
    return m;
}

template<class T>
void Vector<T>::AddMaxToEnd()
{
    T m = Max();
    d.push_back(m);
}

template<class T>
int Vector<T>::Find(T key)
{
    for (int i = 0; i < d.size(); i++)
        if (d[i] == key) return i;
    return -1;
}

template<class T>
void Vector<T>::DelByKey(T key)
{
    int pos = Find(key);
    if (pos != -1)
        d.erase(d.begin() + pos);
}

template<class T>
T Vector<T>::Srednee()
{
    T s;
    for (int i = 0; i < d.size(); i++)
        s = s + d[i];
    return s / static_cast<int>(d.size());
}

template<class T>
void Vector<T>::AddSredneeToAll()
{
    T sr = Srednee();
    for (int i = 0; i < d.size(); i++)
        d[i] = d[i] + sr;
}