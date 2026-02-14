#include <iostream>
#include <clocale>
#include <cmath>
#include <chrono>

using namespace std;

//input parametrs
double a = 0, b = 0.85;
double eps = 10e-7;

//functions
double iterationMethod(double x) {
    return x + x - 1 / (3 + sin(3.6 * x));
}
double methodDoubleDivision(double x) {
    return x - 1 / (3 + sin(3.6 * x));
}
//methods
void methodDoubleDivisionFunc() {
    double e = 1e-8, a = 0, b = 0.85;
    double ya, yb, yc;
    int n = 0;
    if (a > b) swap(a, b);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    while (b - a > e) {
        ya = methodDoubleDivision(a);
        yb = methodDoubleDivision(b);
        yc = methodDoubleDivision((a + b) / 2);
        if (ya * yc < 0) {
            b = (a + b) / 2;
        }
        else if (yc * yb < 0) {
            a = (a + b) / 2;
        }
        else {
            cout << "Корней нет" << "\n";
                cout << n;
                return;
        }
        n++;
    }
    long double delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count();
    cout << "[a,b]: 0 0.85" << endl;
    cout << "Корень: " << (a + b) / 2 << "\n";
    cout << "Количество итераций: " << n << endl;
    std::cout << "Время выполнения: " << delta << " микросекунд\n";
}
void methodNuton() {
    double a, b;
    cout << "Интервал [a, b]: ";
    cin >> a >> b;

    // f(x)
    auto f = [](double x)
        {
            return acos(x) - sqrt(1.0 - 0.3 * pow(x, 3));
        };

    // f'(x)
    auto df = [](double x)
        {
            return -1.0 / sqrt(1.0 - x * x)
                + 0.45 * x * x / sqrt(1.0 - 0.3 * pow(x, 3));
        };

    // f''(x)
    auto ddf = [](double x)
        {
            return -x / pow(1.0 - x * x, 1.5)
                + 0.9 * x / sqrt(1.0 - 0.3 * pow(x, 3))
                + 0.2025 * pow(x, 4) / pow(1.0 - 0.3 * pow(x, 3), 1.5);
        };

    double x = (a + b) / 2.0;
    double x_prev;
    int iter = 0;
    const double eps = 1e-10;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    do
    {
        x_prev = x;
        x = x_prev - f(x_prev) / df(x_prev);
        iter++;
    } while (fabs(x - x_prev) > eps);
    long double delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count();
    cout << "Корень x = " << x << endl;
    cout << "Итераций: " << iter << endl;
    std::cout << "Время выполнения: " << delta << " микросекунд\n";
}
void methodIteraciiFunc() {
    cout << "[a, b] = 0, 1" << endl;
    double x0 = (a + b) / 2;
    double x1 = iterationMethod(x0);
    int iter = 0;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    while (abs(x0 - x1) > eps) {
        x0 = x1;
        x1 = iterationMethod(x0);
        iter++;
    }
    long double delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count();
    cout << "Кол-во иттераций " << iter << endl;
    cout << "Корень находится " << x1 << endl;
    std::cout << "Время выполнения: " << delta << " микросекунд\n";

}

int main()
{
    setlocale(LC_ALL, "Ru");
    methodDoubleDivisionFunc();
    methodNuton();
    methodIteraciiFunc();
    return 0;
}
