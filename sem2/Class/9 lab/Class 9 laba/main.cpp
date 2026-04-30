#include "Book.h"
#include "List.h"
#include <iostream>
using namespace std;

int main()
{
    List list(10);
    char cmd;

    do
    {
        cout << "\nCommands:\n";
        cout << "+ add\n- delete\ns show all\nz show one\nq quit\n";
        cin >> cmd;

        switch (cmd)
        {
        case '+':
        {
            Book* b = new Book;
            cin >> *b;
            list.Add(b);
            break;
        }
        case '-':
            list.Del();
            break;

        case 's':
            list.Show();
            break;

        case 'z':
        {
            int k;
            cin >> k;
            list.ShowOne(k);
            break;
        }
        }

    } while (cmd != 'q');

    return 0;
}