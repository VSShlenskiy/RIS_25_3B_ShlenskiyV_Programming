#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Vector
{
    Object** beg;
    int size;
    int cur;
public:
    Vector(int);
    ~Vector();

    void Add(Object*);
    friend ostream& operator<<(ostream&, const Vector&);
};