#pragma once
#include "Print.h"

class Book : public Print
{
private:
    int pages;
    string publisher;

public:
    Book();
    void Show();

    friend istream& operator>>(istream&, Book&);
};