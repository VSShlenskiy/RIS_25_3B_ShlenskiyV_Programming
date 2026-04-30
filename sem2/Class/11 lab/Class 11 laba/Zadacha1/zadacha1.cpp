#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef deque<int> Deq;

Deq make_deque(int n)
{
    Deq d;
    for (int i = 0; i < n; i++)
    {
        int a = rand() % 100 - 50;
        d.push_back(a);
    }
    return d;
}

void print_deque(Deq d)
{
    for (int i = 0; i < d.size(); i++)
        cout << d[i] << " ";
    cout << endl;
}

int find_max(Deq d)
{
    int m = d[0];
    int pos = 0;
    for (int i = 1; i < d.size(); i++)
    {
        if (d[i] > m)
        {
            m = d[i];
            pos = i;
        }
    }
    return pos;
}

int max_element(Deq d)
{
    int m = d[0];
    for (int i = 1; i < d.size(); i++)
        if (d[i] > m) m = d[i];
    return m;
}

void add_max_to_end(Deq& d)
{
    int m = max_element(d);
    d.push_back(m);
}

int find_key(Deq d, int key)
{
    for (int i = 0; i < d.size(); i++)
        if (d[i] == key) return i;
    return -1;
}

void del_by_key(Deq& d, int key)
{
    int pos = find_key(d, key);
    if (pos != -1)
        d.erase(d.begin() + pos);
}

double srednee(Deq d)
{
    double s = 0;
    for (int i = 0; i < d.size(); i++)
        s += d[i];
    return s / d.size();
}

void add_srednee(Deq& d)
{
    double sr = srednee(d);
    for (int i = 0; i < d.size(); i++)
        d[i] = d[i] + (int)sr;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(0));

    Deq d;
    int n;
    cout << "Введите размер очереди: ";
    cin >> n;
    d = make_deque(n);

    cout << "Исходная очередь: ";
    print_deque(d);

    cout << "Максимальный элемент добавлен в конец" << endl;
    add_max_to_end(d);
    print_deque(d);

    int key;
    cout << "Введите ключ для удаления: ";
    cin >> key;
    del_by_key(d, key);
    cout << "После удаления: ";
    print_deque(d);

    cout << "Добавлено среднее арифметическое к каждому элементу" << endl;
    add_srednee(d);
    print_deque(d);

    system("pause");
    return 0;
}