#include <iostream>
#include <clocale>
#include <cmath>
#include <string>

using namespace std;

int NOD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void reduceFraction(int& numerator, int& denominator) {
    if (denominator == 0) return;

    int divisor = NOD(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

double addFractions(double a, double b) {
    cout << a << " + " << b << " = ";
    return a + b;
}

double addFractions(int a, int b, int c, int d) {
    cout << a << "/" << b << " + " << c << "/" << d << " = ";

    int numerator = a * d + c * b;
    int denominator = b * d;

    reduceFraction(numerator, denominator);

    return static_cast<double>(numerator) / denominator;
}

void printFractionResult(int a, int b, int c, int d) {
    int numerator = a * d + c * b;
    int denominator = b * d;

    reduceFraction(numerator, denominator);

    cout << "Результат в виде обыкновенной дроби: " << numerator;
    if (denominator != 1) {
        cout << "/" << denominator;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "а) Сложение десятичных дробей:\n\n";
    double dec1 = 2.5;
    double dec2 = 3.75;
    double resultDec = addFractions(dec1, dec2);
    cout << resultDec << "\n\n";

    dec1 = 0.125;
    dec2 = 0.875;
    resultDec = addFractions(dec1, dec2);
    cout << resultDec << "\n\n";

    cout << "б) Сложение обыкновенных дробей:\n\n";

    int num1 = 1, den1 = 2;
    int num2 = 1, den2 = 3;

    double resultFrac = addFractions(num1, den1, num2, den2);
    cout << resultFrac << "\n";
    printFractionResult(num1, den1, num2, den2);
    cout << endl;

    num1 = 3; den1 = 4;
    num2 = 2; den2 = 5;

    resultFrac = addFractions(num1, den1, num2, den2);
    cout << resultFrac << "\n";
    printFractionResult(num1, den1, num2, den2);
    cout << endl;

    num1 = 1; den1 = 4;
    num2 = 1; den2 = 4;

    resultFrac = addFractions(num1, den1, num2, den2);
    cout << resultFrac << "\n";
    printFractionResult(num1, den1, num2, den2);
    cout << endl;

    cout << "Пример с отрицательными дробями:\n";
    num1 = -1; den1 = 3;
    num2 = 2; den2 = 5;

    resultFrac = addFractions(num1, den1, num2, den2);
    cout << resultFrac << "\n";
    printFractionResult(num1, den1, num2, den2);
    cout << endl;

    return 0;
}