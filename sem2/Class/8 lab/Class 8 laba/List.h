#pragma once
#include "Object.h"

class List
{
private:
    Object** data;
    int size;
    int cur;

public:
    List(int n = 10);
    ~List();

    void Add(Object*);
    void Del();
    void Show();
    void ShowOne(int);
};