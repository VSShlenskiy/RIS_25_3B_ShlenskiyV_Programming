#pragma once
#include <iostream>
using namespace std;

class Money
{
private:
    long rub;
    int kop;

public:
    Money(long r = 0, int k = 0)
    {
        rub = r;
        kop = k;
    }

    Money(const Money& m)
    {
        rub = m.rub;
        kop = m.kop;
    }

    Money& operator=(const Money& m)
    {
        rub = m.rub;
        kop = m.kop;
        return *this;
    }

    bool operator!=(const Money& m)
    {
        return rub != m.rub || kop != m.kop;
    }

    bool operator==(const Money& m)
    {
        return rub == m.rub && kop == m.kop;
    }

    friend ostream& operator<<(ostream& out, const Money& m)
    {
        out << m.rub << "," << m.kop;
        return out;
    }

    friend istream& operator>>(istream& in, Money& m)
    {
        cout << "rub: "; in >> m.rub;
        cout << "kop: "; in >> m.kop;
        return in;
    }
};