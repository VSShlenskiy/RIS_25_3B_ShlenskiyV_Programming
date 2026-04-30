#pragma once
#include <stack>
#include <vector>
#include <iostream>

template<class T>
std::vector<T> copy_stack_to_vector(std::stack<T> s)
{
    std::vector<T> v;
    while (!s.empty())
    {
        v.push_back(s.top());
        s.pop();
    }
    return v;
}

template<class T>
std::stack<T> copy_vector_to_stack(std::vector<T> v)
{
    std::stack<T> s;
    for (int i = 0; i < v.size(); i++)
        s.push(v[i]);
    return s;
}

template<class T>
class StackVector
{
    std::stack<T> s;
    int len;
public:
    StackVector();
    StackVector(int n);
    ~StackVector();
    void Print();
    T Max();
    void AddMaxToEnd();
    void DelByKey(T key);
    T Srednee();
    void AddSredneeToAll();
};

template<class T>
StackVector<T>::StackVector()
{
    len = 0;
}

template<class T>
StackVector<T>::StackVector(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        s.push(a);
    }
    len = s.size();
}

template<class T>
StackVector<T>::~StackVector() {}

template<class T>
void StackVector<T>::Print()
{
    std::vector<T> v = copy_stack_to_vector(s);
    for (int i = v.size() - 1; i >= 0; i--)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

template<class T>
T StackVector<T>::Max()
{
    std::vector<T> v = copy_stack_to_vector(s);
    T m = v[0];
    for (int i = 1; i < v.size(); i++)
        if (v[i] > m) m = v[i];
    return m;
}

template<class T>
void StackVector<T>::AddMaxToEnd()
{
    T m = Max();
    std::vector<T> v = copy_stack_to_vector(s);
    v.push_back(m);
    s = copy_vector_to_stack(v);
    len = s.size();
}

template<class T>
void StackVector<T>::DelByKey(T key)
{
    std::vector<T> v;
    T t;
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
    len = s.size();
}

template<class T>
T StackVector<T>::Srednee()
{
    std::vector<T> v = copy_stack_to_vector(s);
    T sum;
    for (int i = 0; i < v.size(); i++)
        sum = sum + v[i];
    return sum / static_cast<int>(v.size());
}

template<class T>
void StackVector<T>::AddSredneeToAll()
{
    T sr = Srednee();
    std::vector<T> v;
    while (!s.empty())
    {
        v.push_back(s.top() + sr);
        s.pop();
    }
    for (int i = v.size() - 1; i >= 0; i--)
        s.push(v[i]);
    len = s.size();
}