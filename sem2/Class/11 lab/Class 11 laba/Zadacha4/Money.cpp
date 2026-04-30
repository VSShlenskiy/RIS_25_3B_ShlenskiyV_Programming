#include "Money.h"

void Money::normalize()
{
    if (kopecks >= 100)
    {
        rubles += kopecks / 100;
        kopecks = kopecks % 100;
    }
    else if (kopecks < 0)
    {
        int borrow = (std::abs(kopecks) + 99) / 100;
        rubles -= borrow;
        kopecks += borrow * 100;
    }
    if (kopecks < 0 && rubles > 0)
    {
        rubles--;
        kopecks += 100;
    }
}

Money::Money() : rubles(0), kopecks(0) {}

Money::Money(long r, int k) : rubles(r), kopecks(k)
{
    normalize();
}

Money::Money(const Money& other) : rubles(other.rubles), kopecks(other.kopecks) {}

Money::Money(double amount)
{
    rubles = static_cast<long>(amount);
    kopecks = static_cast<int>((amount - rubles) * 100 + 0.5);
    normalize();
}

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
    long totalKopecks1 = this->rubles * 100 + this->kopecks;
    long totalKopecks2 = other.rubles * 100 + other.kopecks;
    long resultKopecks = totalKopecks1 + totalKopecks2;
    return Money(resultKopecks / 100, resultKopecks % 100);
}

Money Money::operator/(const int& divisor) const
{
    if (divisor == 0) return Money(0, 0);
    long totalKopecks = this->rubles * 100 + this->kopecks;
    long resultKopecks = totalKopecks / divisor;
    return Money(resultKopecks / 100, resultKopecks % 100);
}

bool Money::operator>(const Money& other) const
{
    if (this->rubles > other.rubles) return true;
    if (this->rubles == other.rubles && this->kopecks > other.kopecks) return true;
    return false;
}

bool Money::operator<(const Money& other) const
{
    if (this->rubles < other.rubles) return true;
    if (this->rubles == other.rubles && this->kopecks < other.kopecks) return true;
    return false;
}

bool Money::operator==(const Money& other) const
{
    return (this->rubles == other.rubles) && (this->kopecks == other.kopecks);
}

bool Money::operator!=(const Money& other) const
{
    return !(*this == other);
}

double Money::toDouble() const
{
    return static_cast<double>(rubles) + static_cast<double>(kopecks) / 100.0;
}

std::ostream& operator<<(std::ostream& out, const Money& m)
{
    out << m.rubles << "," << std::setw(2) << std::setfill('0') << m.kopecks;
    return out;
}

std::istream& operator>>(std::istream& in, Money& m)
{
    std::cout << "rubles: ";
    in >> m.rubles;
    std::cout << "kopecks: ";
    in >> m.kopecks;
    m.normalize();
    return in;
}