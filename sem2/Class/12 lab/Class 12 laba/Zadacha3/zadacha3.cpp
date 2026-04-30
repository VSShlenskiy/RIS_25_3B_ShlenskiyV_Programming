#include <iostream>
#include "Money.h"
#include "Container.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "N? ";
    cin >> n;
    Container<Money> c(n);

    cout << "Исходный контейнер: ";
    c.Print();

    cout << "Добавление максимального элемента в конец" << endl;
    c.AddMax();
    c.Print();

    Money key;
    cout << "Введите ключ для удаления:" << endl;
    cin >> key;
    c.DelByKey(key);
    cout << "После удаления: ";
    c.Print();

    cout << "Каждый элемент + среднее арифметическое" << endl;
    c.AddSrednee();
    c.Print();

    return 0;
}