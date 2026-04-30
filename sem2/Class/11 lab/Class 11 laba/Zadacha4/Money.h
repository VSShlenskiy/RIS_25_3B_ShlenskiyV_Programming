#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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
    Money(double amount);
    ~Money();

    Money& operator=(const Money& other);
    Money operator+(const Money& other) const;
    Money operator/(const int& divisor) const;
    bool operator>(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    double toDouble() const;

    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);
};