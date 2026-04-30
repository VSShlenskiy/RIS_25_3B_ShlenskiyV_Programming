#include "Money.h"
#include "file_work.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");
    Money p, tempMoney;
    int k, c;
    char file_name[30];
    int nom;
    double fractionalNumber;

    do {
        std::cout << "\n--- МЕНЮ ---" << std::endl;
        std::cout << "1. Создать новый файл" << std::endl;
        std::cout << "2. Вывести содержимое файла" << std::endl;
        std::cout << "3. Удалить все записи, равные заданному значению" << std::endl;
        std::cout << "4. Уменьшить все записи, равные заданному значению, на 1.50" << std::endl;
        std::cout << "5. Добавить K записей после элемента с заданным значением" << std::endl;
        std::cout << "6. Демонстрация вычитания дробного числа из Money" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> c;

        switch (c) {
        case 1:
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            k = make_file(file_name);
            if (k < 0) std::cout << "Ошибка создания файла!" << std::endl;
            else std::cout << "Файл создан, записей: " << k << std::endl;
            break;

        case 2:
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            k = print_file(file_name);
            if (k == 0) std::cout << "Файл пуст." << std::endl;
            else if (k < 0) std::cout << "Ошибка чтения файла!" << std::endl;
            else std::cout << "Всего записей: " << k << std::endl;
            break;

        case 3:
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            std::cout << "Введите значение для удаления (рубли и копейки): ";
            std::cin >> tempMoney;
            k = del_equal(file_name, tempMoney);
            if (k < 0) std::cout << "Ошибка работы с файлом!" << std::endl;
            else std::cout << "Удалено записей: " << k << std::endl;
            break;

        case 4:
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            std::cout << "Введите значение, которое нужно уменьшить (рубли и копейки): ";
            std::cin >> tempMoney;
            k = decrease_equal(file_name, tempMoney);
            if (k < 0) std::cout << "Ошибка работы с файлом!" << std::endl;
            else std::cout << "Изменено записей: " << k << std::endl;
            break;

        case 5: {
            int K;
            Money newRecord;
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            std::cout << "Введите значение, после которого добавить (рубли и копейки): ";
            std::cin >> tempMoney;
            std::cout << "Сколько записей (K) добавить? ";
            std::cin >> K;
            std::cout << "Введите новое значение для добавления (рубли и копейки): ";
            std::cin >> newRecord;
            k = add_after_value(file_name, tempMoney, K, newRecord);
            if (k < 0) std::cout << "Ошибка работы с файлом!" << std::endl;
            else std::cout << "Добавлено записей: " << k << std::endl;
            break;
        }

        case 6: {
            Money m1;
            double num;
            std::cout << "Демонстрация Money - double." << std::endl;
            std::cout << "Введите уменьшаемую сумму (m1):" << std::endl;
            std::cin >> m1;
            std::cout << "Введите вычитаемое дробное число (например, 15.25): ";
            std::cin >> num;
            Money result = m1 - num;
            std::cout << m1 << " - " << num << " = " << result << std::endl;
            break;
        }
        }
    } while (c != 0);

    return 0;
}