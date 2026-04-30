#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Print : public Object
{
protected:
    string name;
    string author;

public:
    Print();
    Print(string, string);

    virtual void Show();

    friend istream& operator>>(istream&, Print&);
};