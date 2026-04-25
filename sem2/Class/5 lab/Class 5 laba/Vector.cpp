#include "Vector.h"

Vector::Vector(int n)
{
    beg = new Object * [n];
    size = n;
    cur = 0;
}

Vector::~Vector()
{
    delete[] beg;
}

void Vector::Add(Object* p)
{
    if (cur < size)
        beg[cur++] = p;
}

ostream& operator<<(ostream& out, const Vector& v)
{
    for (int i = 0; i < v.cur; i++)
        v.beg[i]->Show();
    return out;
}