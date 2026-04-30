#pragma once
#include "Money.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

int make_file(const char* f_name) {
    std::fstream stream(f_name, std::ios::out | std::ios::trunc);
    if (!stream) return -1;

    int n;
    Money m;
    std::cout << "Сколько записей создать? ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> m;
        stream << m;
    }
    stream.close();
    return n;
}

int print_file(const char* f_name) {
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;

    Money m;
    int i = 0;
    std::cout << "--- Содержимое файла ---" << std::endl;
    while (stream >> m) {
        std::cout << "[" << i + 1 << "] " << m << std::endl;
        i++;
    }
    stream.close();
    return i;
}

int del_equal(const char* f_name, const Money& value) {
    std::fstream temp("temp.txt", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        temp.close();
        return -1;
    }

    Money m;
    int deleted = 0;
    int total = 0;
    while (stream >> m) {
        total++;
        if (m != value) {
            temp << m;
        }
        else {
            deleted++;
        }
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    return deleted;
}

int decrease_equal(const char* f_name, const Money& targetValue) {
    std::fstream temp("temp.txt", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        temp.close();
        return -1;
    }

    Money m;
    Money delta(1, 50);
    int changed = 0;
    int total = 0;
    Money zero(0, 0);

    while (stream >> m) {
        total++;
        if (m == targetValue) {
            if (m.toDouble() >= delta.toDouble()) {
                m = m - delta;
            }
            else {
                m = zero;
            }
            changed++;
        }
        temp << m;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    return changed;
}

int add_after_value(const char* f_name, const Money& searchValue, int k, const Money& newValue) {
    std::fstream temp("temp.txt", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        temp.close();
        return -1;
    }

    Money m;
    int added = 0;
    bool foundAndAdded = false;

    while (stream >> m) {
        temp << m;
        if (m == searchValue && !foundAndAdded) {
            for (int i = 0; i < k; i++) {
                temp << newValue;
                added++;
            }
            foundAndAdded = true;
        }
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    return added;
}