#pragma once
#include <iostream>
#include "Iterator.h"
using namespace std;

class Set
{
private:
    int size;
    int* data;
    Iterator beg;
    Iterator end;

public:
    Set(int s = 0);
    Set(const Set& s);
    ~Set();

    Set& operator=(const Set& s);

    int& operator[](int index);

    bool operator!=(const Set& s);

    bool operator<(int value); // принадлежность

    Iterator first();
    Iterator last();

    friend ostream& operator<<(ostream&, const Set&);
    friend istream& operator>>(istream&, Set&);
};