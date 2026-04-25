#include "Triad.h"
#include "Time.h"
#include "Vector.h"

int main()
{
    Triad a;
    cin >> a;
    cout << a;

    Time b;
    cin >> b;
    cout << b;

    Object* p;

    Vector v(5);

    p = &a;
    v.Add(p);

    p = &b;
    v.Add(p);

    cout << "\nVector output:\n";
    cout << v;

    return 0;
}