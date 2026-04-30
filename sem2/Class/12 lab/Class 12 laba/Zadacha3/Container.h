#pragma once
#include <iostream>
#include <set>
using namespace std;

template<class T>
class Container
{
    set<T> s;
    int len;

public:
    Container();
    Container(int n);
    ~Container();
    void Print();
    T Max();
    void AddMax();
    void DelByKey(T key);
    T Srednee();
    void AddSrednee();
};

template<class T>
Container<T>::Container()
{
    len = 0;
}

template<class T>
Container<T>::Container(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        s.insert(a);
    }
    len = s.size();
}

template<class T>
Container<T>::~Container() {}

template<class T>
void Container<T>::Print()
{
    typename set<T>::iterator i = s.begin();
    while (i != s.end())
    {
        cout << *i << " ";
        i++;
    }
    cout << endl;
}

template<class T>
T Container<T>::Max()
{
    typename set<T>::iterator i = s.begin();
    T m = *i;
    while (i != s.end())
    {
        if (*i > m) m = *i;
        i++;
    }
    return m;
}

template<class T>
void Container<T>::AddMax()
{
    T m = Max();
    s.insert(m);
    len = s.size();
}

template<class T>
void Container<T>::DelByKey(T key)
{
    typename set<T>::iterator i = s.begin();
    while (i != s.end())
    {
        if (*i == key)
        {
            s.erase(i);
            break;
        }
        i++;
    }
    len = s.size();
}

template<class T>
T Container<T>::Srednee()
{
    T sum;
    int n = 0;
    typename set<T>::iterator i = s.begin();
    while (i != s.end())
    {
        sum = sum + *i;
        n++;
        i++;
    }
    return sum / n;
}

template<class T>
void Container<T>::AddSrednee()
{
    T sr = Srednee();
    set<T> temp;
    typename set<T>::iterator i = s.begin();
    while (i != s.end())
    {
        temp.insert(*i + sr);
        i++;
    }
    s = temp;
    len = s.size();
}