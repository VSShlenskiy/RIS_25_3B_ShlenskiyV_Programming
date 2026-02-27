#include <iostream>
#include <clocale>
#include <cstdarg>
#include <climits>
#include <cmath>

using namespace std;

int minInt(int count, ...) {
    va_list args;
    va_start(args, count);

    int minValue = INT_MAX;

    for (int i = 0; i < count; i++) {
        int current = va_arg(args, int);
        if (current < minValue) {
            minValue = current;
        }
    }

    va_end(args);
    return minValue;
}

double minDouble(int count, ...) {
    va_list args;
    va_start(args, count);

    double minValue = INFINITY;

    for (int i = 0; i < count; i++) {
        double current = va_arg(args, double);
        if (current < minValue) {
            minValue = current;
        }
    }

    va_end(args);
    return minValue;
}

double min(char type, int count, ...) {
    va_list args;
    va_start(args, count);

    double result;

    if (type == 'i') {
        int minInt = INT_MAX;
        for (int i = 0; i < count; i++) {
            int current = va_arg(args, int);
            if (current < minInt) {
                minInt = current;
            }
        }
        result = minInt;
    }
    else if (type == 'd') {
        double minDouble = INFINITY;
        for (int i = 0; i < count; i++) {
            double current = va_arg(args, double);
            if (current < minDouble) {
                minDouble = current;
            }
        }
        result = minDouble;
    }
    else {
        result = 0;
    }

    va_end(args);
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "min(int, 5 параметров: 42, 17, 33, 8, 25) = ";
    cout << min('i', 5, 42, 17, 33, 8, 25) << "\n";

    cout << "min(double, 5 параметров: 3.14, 2.71, 1.618, 0.707, 2.236) = ";
    cout << min('d', 5, 3.14, 2.71, 1.618, 0.707, 2.236) << "\n\n";

    cout << "min(int, 10 параметров: 100, 45, 67, 12, 89, 34, 56, 23, 78, 91) = ";
    cout << min('i', 10, 100, 45, 67, 12, 89, 34, 56, 23, 78, 91) << "\n";

    cout << "min(double, 10 параметров: 5.5, 3.3, 7.8, 2.2, 9.1, 4.4, 6.6, 1.1, 8.8, 0.5) = ";
    cout << min('d', 10, 5.5, 3.3, 7.8, 2.2, 9.1, 4.4, 6.6, 1.1, 8.8, 0.5) << "\n\n";

    cout << "min(int, 12 параметров: 150, 73, 42, 18, 95, 61, 27, 84, 36, 109, 52, 14) = ";
    cout << min('i', 12, 150, 73, 42, 18, 95, 61, 27, 84, 36, 109, 52, 14) << "\n";

    cout << "min(double, 12 параметров: 12.34, 56.78, 9.01, 23.45, 67.89, 3.21, 45.67, 89.01, 34.56, 78.91, 5.43, 7.89) = ";
    cout << min('d', 12, 12.34, 56.78, 9.01, 23.45, 67.89, 3.21, 45.67, 89.01, 34.56, 78.91, 5.43, 7.89) << "\n\n";

    cout << "min(int, с отрицательными: -5, -10, -3, -7, -1) = ";
    cout << min('i', 5, -5, -10, -3, -7, -1) << "\n";

    return 0;
}