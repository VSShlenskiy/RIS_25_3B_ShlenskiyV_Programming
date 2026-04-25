#include "Time.h"

Time::Time() : Triad() {}
Time::Time(int h, int m, int s) : Triad(h, m, s) {}
Time::~Time() {}

bool Time::operator>(const Time& t)
{
    if (first > t.first) return true;
    if (first == t.first && second > t.second) return true;
    if (first == t.first && second == t.second && third > t.third) return true;
    return false;
}

bool Time::operator<(const Time& t)
{
    return !(*this > t) && !(*this == t);
}

bool Time::operator==(const Time& t)
{
    return first == t.first && second == t.second && third == t.third;
}

void Time::Show()
{
    cout << "\nTime: " << first << ":" << second << ":" << third << endl;
}

istream& operator>>(istream& in, Time& t)
{
    cout << "Hours: "; in >> t.first;
    cout << "Minutes: "; in >> t.second;
    cout << "Seconds: "; in >> t.third;
    return in;
}

ostream& operator<<(ostream& out, const Time& t)
{
    out << "Time: " << t.first << ":" << t.second << ":" << t.third << endl;
    return out;
}