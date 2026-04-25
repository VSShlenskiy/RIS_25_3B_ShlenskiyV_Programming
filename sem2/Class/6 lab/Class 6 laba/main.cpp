#include "Set.h"

int main()
{
    Set a(5);
    cout << "Input set A:\n";
    cin >> a;

    cout << "A: " << a << endl;

    // доступ по индексу
    a[2] = 100;
    cout << "After change: " << a << endl;

    // копия
    Set b = a;

    // проверка !=
    if (a != b)
        cout << "Sets are different\n";
    else
        cout << "Sets are equal\n";

    // проверка принадлежности
    int x = 100;
    if (a < x)
        cout << x << " belongs to set\n";
    else
        cout << x << " NOT in set\n";

    // итератор
    cout << "\nIterator output:\n";
    for (Iterator it = a.first(); it != a.last(); it++)
        cout << *it << " ";

    cout << endl;

    // переход на n
    Iterator it = a.first();
    it + 2;
    cout << "\nElement after +2: " << *it << endl;

    return 0;
}