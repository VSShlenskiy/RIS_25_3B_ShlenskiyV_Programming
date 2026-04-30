#include "Money.h"

void Money::normalize()
{
    if (kopecks >= 100)
    {
        rubles += kopecks / 100;
        kopecks %= 100;
    }
    else if (kopecks < 0)
    {
        rubles -= (abs(kopecks) + 99) / 100;
        kopecks = (kopecks % 100 + 100) % 100;
    }
}

Money::Money() : rubles(0), kopecks(0) {}

Money::Money(long r, int k) : rubles(r), kopecks(k)
{
    normalize();
}

Money::Money(const Money& other) : rubles(other.rubles), kopecks(other.kopecks) {}

Money::~Money() {}

Money& Money::operator=(const Money& other)
{
    if (this != &other)
    {
        rubles = other.rubles;
        kopecks = other.kopecks;
    }
    return *this;
}

Money Money::operator+(const Money& other) const
{
    long k1 = rubles * 100 + kopecks;
    long k2 = other.rubles * 100 + other.kopecks;
    return Money((k1 + k2) / 100, (k1 + k2) % 100);
}

Money Money::operator/(const int& divisor) const
{
    if (divisor == 0) return Money(0, 0);
    long k = rubles * 100 + kopecks;
    return Money(k / 100 / divisor, k % 100 / divisor);
}

bool Money::operator>(const Money& other) const
{
    if (rubles > other.rubles) return true;
    if (rubles == other.rubles && kopecks > other.kopecks) return true;
    return false;
}

bool Money::operator==(const Money& other) const
{
    return (rubles == other.rubles && kopecks == other.kopecks);
}

bool Money::operator!=(const Money& other) const
{
    return !(*this == other);
}

ostream& operator<<(ostream& out, const Money& m)
{
    out << m.rubles << "," << setw(2) << setfill('0') << m.kopecks;
    return out;
}

istream& operator>>(istream& in, Money& m)
{
    cout << "Рубли: ";
    in >> m.rubles;
    cout << "Копейки: ";
    in >> m.kopecks;
    m.normalize();
    return in;
}