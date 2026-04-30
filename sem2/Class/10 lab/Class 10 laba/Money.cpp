#include "Money.h"
#include <iomanip>

void Money::normalize() {
    if (kopecks >= 100) {
        rubles += kopecks / 100;
        kopecks = kopecks % 100;
    }
    else if (kopecks < 0) {
        int borrow = (abs(kopecks) + 99) / 100;
        rubles -= borrow;
        kopecks += borrow * 100;
    }
}

Money::Money() : rubles(0), kopecks(0) {}

Money::Money(long r, int k) : rubles(r), kopecks(k) {
    normalize();
}

Money::Money(const Money& other) : rubles(other.rubles), kopecks(other.kopecks) {}

Money::~Money() {}

Money& Money::operator = (const Money& other) {
    if (this != &other) {
        rubles = other.rubles;
        kopecks = other.kopecks;
    }
    return *this;
}

Money Money::operator - (const Money& other) const {
    long totalKopecks1 = this->rubles * 100 + this->kopecks;
    long totalKopecks2 = other.rubles * 100 + other.kopecks;
    long resultKopecks = totalKopecks1 - totalKopecks2;
    return Money(resultKopecks / 100, resultKopecks % 100);
}

Money Money::operator - (double fraction) const {
    long rubFromFraction = static_cast<long>(fraction);
    int kopFromFraction = static_cast<int>((fraction - rubFromFraction) * 100 + 0.5);

    Money fractionMoney(rubFromFraction, kopFromFraction);
    return *this - fractionMoney;
}

bool Money::operator == (const Money& other) const {
    return (this->rubles == other.rubles) && (this->kopecks == other.kopecks);
}

bool Money::operator != (const Money& other) const {
    return !(*this == other);
}

double Money::toDouble() const {
    return static_cast<double>(rubles) + static_cast<double>(kopecks) / 100.0;
}

std::ostream& operator << (std::ostream& out, const Money& m) {
    out << m.rubles << "," << std::setw(2) << std::setfill('0') << m.kopecks;
    return out;
}

std::istream& operator >> (std::istream& in, Money& m) {
    std::cout << "Введите рубли: ";
    in >> m.rubles;
    std::cout << "Введите копейки: ";
    in >> m.kopecks;
    m.normalize();
    return in;
}

std::fstream& operator >> (std::fstream& fin, Money& m) {
    fin >> m.rubles >> m.kopecks;
    m.normalize();
    return fin;
}

std::fstream& operator << (std::fstream& fout, const Money& m) {
    fout << m.rubles << " " << m.kopecks << "\n";
    return fout;
}