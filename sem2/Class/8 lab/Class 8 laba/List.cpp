#include "List.h"
#include <iostream>
using namespace std;

List::List(int n)
{
    size = n;
    cur = 0;
    data = new Object * [size];
}

List::~List()
{
    delete[] data;
}

void List::Add(Object* p)
{
    if (cur < size)
        data[cur++] = p;
}

void List::Del()
{
    if (cur > 0)
        cur--;
}

void List::Show()
{
    for (int i = 0; i < cur; i++)
        data[i]->Show();
}

void List::ShowOne(int k)
{
    if (k < cur)
        data[k]->Show();
}