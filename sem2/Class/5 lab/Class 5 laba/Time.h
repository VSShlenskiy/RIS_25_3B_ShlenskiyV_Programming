#pragma once
#include "Triad.h"

class Time : public Triad
{
public:
    Time();
    Time(int h, int m, int s);
    ~Time();

    bool operator>(const Time&);
    bool operator<(const Time&);
    bool operator==(const Time&);

    void Show();

    friend istream& operator>>(istream&, Time&);
    friend ostream& operator<<(ostream&, const Time&);
};