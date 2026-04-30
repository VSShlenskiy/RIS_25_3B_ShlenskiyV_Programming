#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef set<int> TSet;
typedef TSet::iterator it;

TSet make_set(int n)
{
    TSet s;
    for (int i = 0; i < n; i++)
    {
        int a = rand() % 100 - 50;
        s.insert(a);
    }
    return s;
}

void print_set(TSet s)
{
    for (it i = s.begin(); i != s.end(); i++)
        cout << *i << " ";
    cout << endl;
}

int max_element(TSet s)
{
    it i = s.begin();
    int m = *i;
    while (i != s.end())
    {
        if (*i > m) m = *i;
        i++;
    }
    return m;
}

void add_max_to_end(TSet& s)
{
    int m = max_element(s);
    s.insert(m);
}

it find_key(TSet s, int key)
{
    it i = s.begin();
    while (i != s.end())
    {
        if (*i == key) return i;
        i++;
    }
    return s.end();
}

void del_by_key(TSet& s, int key)
{
    it pos = find_key(s, key);
    if (pos != s.end())
        s.erase(pos);
}

double srednee(TSet s)
{
    double sum = 0;
    int n = 0;
    it i = s.begin();
    while (i != s.end())
    {
        sum += *i;
        n++;
        i++;
    }
    return sum / n;
}

void add_srednee(TSet& s)
{
    double sr = srednee(s);
    TSet temp;
    it i = s.begin();
    while (i != s.end())
    {
        temp.insert(*i + (int)sr);
        i++;
    }
    s = temp;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(0));

    TSet s;
    int n;
    cout << "N? ";
    cin >> n;
    s = make_set(n);

    cout << "Исходное множество: ";
    print_set(s);

    cout << "Добавление максимального элемента в конец" << endl;
    add_max_to_end(s);
    print_set(s);

    int key;
    cout << "Введите ключ для удаления: ";
    cin >> key;
    del_by_key(s, key);
    cout << "После удаления: ";
    print_set(s);

    cout << "Каждый элемент + среднее арифметическое" << endl;
    add_srednee(s);
    print_set(s);

    return 0;
}