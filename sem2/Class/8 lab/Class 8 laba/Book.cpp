#include "Book.h"

Book::Book() : Print()
{
    pages = 0;
    publisher = "";
}

void Book::Show()
{
    Print::Show();
    cout << "Pages: " << pages << endl;
    cout << "Publisher: " << publisher << endl;
}

istream& operator>>(istream& in, Book& b)
{
    in >> (Print&)b;
    cout << "Pages: "; in >> b.pages;
    cout << "Publisher: "; in >> b.publisher;
    return in;
}