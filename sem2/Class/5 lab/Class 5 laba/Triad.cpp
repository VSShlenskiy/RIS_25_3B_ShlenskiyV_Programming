#include "Triad.h"

Triad::Triad() { first = second = third = 0; }
Triad::Triad(int a, int b, int c) { first = a; second = b; third = c; }
Triad::~Triad() {}

void Triad::Set_first(int a) { first = a; }
void Triad::Set_second(int b) { second = b; }
void Triad::Set_third(int c) { third = c; }

int Triad::Get_first() { return first; }
int Triad::Get_second() { return second; }
int Triad::Get_third() { return third; }

bool Triad::operator>(const Triad& t)
{
    if (first > t.first) return true;
    if (first == t.first && second > t.second) return true;
    if (first == t.first && second == t.second && third > t.third) return true;
    return false;
}

bool Triad::operator<(const Triad& t)
{
    return !(*this > t) && !(*this == t);
}

bool Triad::operator==(const Triad& t)
{
    return first == t.first && second == t.second && third == t.third;
}

void Triad::Show()
{
    cout << "\nTriad: " << first << " " << second << " " << third << endl;
}

istream& operator>>(istream& in, Triad& t)
{
    cout << "first: "; in >> t.first;
    cout << "second: "; in >> t.second;
    cout << "third: "; in >> t.third;
    return in;
}

ostream& operator<<(ostream& out, const Triad& t)
{
    out << "Triad: " << t.first << " " << t.second << " " << t.third << endl;
    return out;
}