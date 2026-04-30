#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Money {
private:
    long rubles;
    int kopecks;

    void normalize();

public:
    Money();
    Money(long r, int k);
    Money(const Money& other);

    ~Money();

    Money& operator = (const Money& other);

    Money operator - (const Money& other) const;
    Money operator - (double fraction) const;

    bool operator == (const Money& other) const;
    bool operator != (const Money& other) const;

    friend std::ostream& operator << (std::ostream& out, const Money& m);
    friend std::istream& operator >> (std::istream& in, Money& m);

    friend std::fstream& operator >> (std::fstream& fin, Money& m);
    friend std::fstream& operator << (std::fstream& fout, const Money& m);

    double toDouble() const;
};