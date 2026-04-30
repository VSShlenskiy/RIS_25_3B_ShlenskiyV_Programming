#include "Set.h"
#include "Money.h"

int main()
{
    // ==== INT ====
    Set<int> A(5, 0);
    cout << "Input int set:\n";
    cin >> A;
    cout << "A: " << A << endl;

    A[2] = 100;
    cout << "After change: " << A << endl;

    Set<int> B = A;

    if (A != B)
        cout << "Sets different\n";
    else
        cout << "Sets equal\n";

    if (A < 100)
        cout << "100 in set\n";

    cout << "Size: " << A() << endl;


    // ==== MONEY ====
    Money m;
    cin >> m;

    Set<Money> M(3, m);
    cin >> M;

    cout << "Money set: " << M << endl;

    if (M < m)
        cout << "Element exists\n";

    return 0;
}