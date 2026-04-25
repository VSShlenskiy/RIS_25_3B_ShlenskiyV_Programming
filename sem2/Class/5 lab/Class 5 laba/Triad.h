#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Triad : public Object
{
protected:
    int first, second, third;
public:
    Triad();
    Triad(int, int, int);
    virtual ~Triad();

    void Set_first(int);
    void Set_second(int);
    void Set_third(int);

    int Get_first();
    int Get_second();
    int Get_third();

    bool operator>(const Triad&);
    bool operator<(const Triad&);
    bool operator==(const Triad&);

    virtual void Show();

    friend istream& operator>>(istream&, Triad&);
    friend ostream& operator<<(ostream&, const Triad&);
};