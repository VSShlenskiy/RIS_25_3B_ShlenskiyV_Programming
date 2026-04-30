#pragma once
#include <iostream>
using namespace std;

template <class T>
class Set
{
private:
    int size;
    T* data;

public:
    // конструктор
    Set(int s = 0, T k = T())
    {
        size = s;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = k;
    }

    // копирование
    Set(const Set<T>& s)
    {
        size = s.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = s.data[i];
    }

    // деструктор
    ~Set()
    {
        delete[] data;
    }

    // присваивание
    Set<T>& operator=(const Set<T>& s)
    {
        if (this == &s) return *this;

        delete[] data;

        size = s.size;
        data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = s.data[i];

        return *this;
    }

    // доступ по индексу
    T& operator[](int index)
    {
        if (index < size)
            return data[index];
        else
            throw "Index error";
    }

    // !=
    bool operator!=(const Set<T>& s)
    {
        if (size != s.size) return true;

        for (int i = 0; i < size; i++)
            if (data[i] != s.data[i]) return true;

        return false;
    }

    // принадлежность
    bool operator<(T value)
    {
        for (int i = 0; i < size; i++)
            if (data[i] == value) return true;

        return false;
    }

    // размер
    int operator()()
    {
        return size;
    }

    // вывод
    friend ostream& operator<<(ostream& out, const Set<T>& s)
    {
        for (int i = 0; i < s.size; i++)
            out << s.data[i] << " ";
        return out;
    }

    // ввод
    friend istream& operator>>(istream& in, Set<T>& s)
    {
        for (int i = 0; i < s.size; i++)
            in >> s.data[i];
        return in;
    }
};