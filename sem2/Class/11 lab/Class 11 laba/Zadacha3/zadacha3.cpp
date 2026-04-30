#include <iostream>
#include "Money.h"
#include "Vector.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    Vector<Money> vec(3);
    std::cout << "Исходный вектор: ";
    vec.Print();

    std::cout << "Добавление максимального в конец" << std::endl;
    vec.AddMaxToEnd();
    vec.Print();

    Money key;
    std::cout << "Введите ключ для удаления:" << std::endl;
    std::cin >> key;
    vec.DelByKey(key);
    std::cout << "После удаления: ";
    vec.Print();

    std::cout << "Добавление среднего арифметического к каждому элементу" << std::endl;
    vec.AddSredneeToAll();
    vec.Print();

    return 0;
}