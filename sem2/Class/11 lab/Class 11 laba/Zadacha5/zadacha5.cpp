#include <iostream>
#include "Money.h"
#include "StackVector.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    StackVector<Money> sv(3);
    std::cout << "Исходный стек: ";
    sv.Print();

    std::cout << "Добавление максимального в конец" << std::endl;
    sv.AddMaxToEnd();
    sv.Print();

    Money key;
    std::cout << "Введите ключ для удаления:" << std::endl;
    std::cin >> key;
    sv.DelByKey(key);
    std::cout << "После удаления: ";
    sv.Print();

    std::cout << "Добавление среднего арифметического к каждому элементу" << std::endl;
    sv.AddSredneeToAll();
    sv.Print();

    return 0;
}