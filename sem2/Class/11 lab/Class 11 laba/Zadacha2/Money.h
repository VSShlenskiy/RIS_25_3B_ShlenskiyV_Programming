#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Money
{
private:
    long rubles;
    int kopecks;
    void normalize();

public:
    Money();
    Money(long r, int k);
    Money(const Money& other);
    ~Money();

    Money& operator=(const Money& other);
    Money operator+(const Money& other) const;
    Money operator/(const int& divisor) const;
    bool operator>(const Money& other) const;
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    friend ostream& operator<<(ostream& out, const Money& m);
    friend istream& operator>>(istream& in, Money& m);
};