#pragma once
class Set;

class Iterator
{
    friend class Set;
private:
    int* elem;
public:
    Iterator() { elem = 0; }
    Iterator(const Iterator& it) { elem = it.elem; }

    bool operator!=(const Iterator& it) { return elem != it.elem; }

    // префиксный ++it
    Iterator& operator++()
    {
        ++elem;
        return *this;
    }

    // постфиксный it++
    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++elem;
        return temp;
    }

    void operator+(int n) { elem += n; }

    int& operator*() { return *elem; }
};