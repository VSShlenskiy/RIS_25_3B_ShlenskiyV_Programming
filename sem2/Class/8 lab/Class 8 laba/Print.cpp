#include "Print.h"

Print::Print() { name = ""; author = ""; }

Print::Print(string n, string a)
{
    name = n;
    author = a;
}

void Print::Show()
{
    cout << "\nName: " << name;
    cout << "\nAuthor: " << author << endl;
}

istream& operator>>(istream& in, Print& p)
{
    cout << "Name: "; in >> p.name;
    cout << "Author: "; in >> p.author;
    return in;
}