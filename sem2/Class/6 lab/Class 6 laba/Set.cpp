#include "Set.h"

// конструктор
Set::Set(int s)
{
    size = s;
    data = new int[size];

    for (int i = 0; i < size; i++)
        data[i] = 0;

    beg.elem = &data[0];
    end.elem = &data[size];
}

// копирование
Set::Set(const Set& s)
{
    size = s.size;
    data = new int[size];

    for (int i = 0; i < size; i++)
        data[i] = s.data[i];

    beg.elem = &data[0];
    end.elem = &data[size];
}

// деструктор
Set::~Set()
{
    delete[] data;
}

// присваивание
Set& Set::operator=(const Set& s)
{
    if (this == &s) return *this;

    delete[] data;

    size = s.size;
    data = new int[size];

    for (int i = 0; i < size; i++)
        data[i] = s.data[i];

    beg.elem = &data[0];
    end.elem = &data[size];

    return *this;
}

// доступ по индексу
int& Set::operator[](int index)
{
    if (index < size)
        return data[index];
    else
        throw "Index out of range";
}

// неравенство
bool Set::operator!=(const Set& s)
{
    if (size != s.size) return true;

    for (int i = 0; i < size; i++)
        if (data[i] != s.data[i]) return true;

    return false;
}

// принадлежность (value  set)
bool Set::operator<(int value)
{
    for (int i = 0; i < size; i++)
        if (data[i] == value) return true;

    return false;
}

// итераторы
Iterator Set::first() { return beg; }
Iterator Set::last() { return end; }

// вывод
ostream& operator<<(ostream& out, const Set& s)
{
    for (int i = 0; i < s.size; i++)
        out << s.data[i] << " ";
    return out;
}

// ввод
istream& operator>>(istream& in, Set& s)
{
    for (int i = 0; i < s.size; i++)
        in >> s.data[i];
    return in;
}