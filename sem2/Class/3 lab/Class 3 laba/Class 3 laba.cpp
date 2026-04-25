#include <iostream>
#include <cmath>

using namespace std;

class Money {
private:
    long rubles;
    int kopey;

    void normalize() {
        if (kopey < 0) {
            long carry = (abs(kopey) + 99) / 100;
            rubles -= carry;
            kopey += carry * 100;
        }
        if (kopey >= 100) {
            rubles += kopey / 100;
            kopey %= 100;
        }
    }

public:
    Money() {
        this->rubles = 1000;
        this->kopey = 55;
    }

    Money(long rub, int kop) {
        this->rubles = rub;
        this->kopey = kop;
        normalize();
    }

    Money(const Money& other) {
        this->rubles = other.rubles;
        this->kopey = other.kopey;
    }

    ~Money() {}

    void SetRub(long rub) {
        this->rubles = rub;
    }

    long GetRub() {
        return this->rubles;
    }

    void SetKop(int kop) {
        this->kopey = kop;
        normalize();
    }

    int GetKop() {
        return this->kopey;
    }

    Money& operator=(const Money& other) {
        if (this != &other) {
            this->rubles = other.rubles;
            this->kopey = other.kopey;
        }
        return *this;
    }

    Money subtract(double value) const {
        long long total_kopey = rubles * 100LL + kopey;

        long long sub_kopey = static_cast<long long>(round(value * 100));

        long long result_kopey = total_kopey - sub_kopey;

        long new_rubles = result_kopey / 100;
        int new_kopey = result_kopey % 100;

        if (new_kopey < 0) {
            new_rubles -= 1;
            new_kopey += 100;
        }

        return Money(new_rubles, new_kopey);
    }

    Money operator-(double value) const {
        return subtract(value);
    }

    bool operator == (const Money& other) const {
        return (rubles == other.rubles && kopey == other.kopey);
    }

    bool operator != (const Money& other) const {
        return !(*this == other);
    }

    void input() {
        cout << "Введите кол-во рублей: "; cin >> rubles;
        cout << "Введите кол-во копеек: "; cin >> kopey;
        normalize();
    }

    void print() const {
        cout << rubles << ",";
        if (kopey < 10) cout << "0";
        cout << kopey;
    }

    friend istream& operator>>(istream& in, Money& other);
    friend ostream& operator<<(ostream& out, const Money& other);
};

istream& operator>>(istream& in, Money& other) {
    cout << "Введите кол-во рублей: "; in >> other.rubles;
    cout << "Введите кол-во копеек: "; in >> other.kopey;
    other.normalize();
    return in;
}

ostream& operator<<(ostream& out, const Money& other) {
    out << other.rubles << ",";
    if (other.kopey < 10) out << "0";
    out << other.kopey;
    return out;
}

int main() {
    setlocale(LC_ALL, "ru");

    Money m1(10, 50);
    cout << "m1 = " << m1 << endl;

    double x = 2.75;
    Money m2 = m1.subtract(x);
    cout << "m1 - " << x << " = " << m2 << endl;

    Money m3(100, 30);
    Money m4 = m3 - 15.45;
    cout << "\n" << m3 << " - 15.45 = " << m4 << endl;

    Money a(5, 50);
    Money b(5, 50);
    Money c(10, 0);

    cout << "\nСравнение:" << endl;
    cout << a << " == " << b << " ? " << (a == b ? "Да" : "Нет") << endl;
    cout << a << " == " << c << " ? " << (a == c ? "Да" : "Нет") << endl;
    cout << a << " != " << c << " ? " << (a != c ? "Да" : "Нет") << endl;

    cout << "\nВведите новую сумму:" << endl;
    Money m5;
    cin >> m5;
    cout << "Вы ввели: " << m5 << endl;

    Money m6(3, 20);
    Money m7 = m6 - 5.50;
    cout << "\n" << m6 << " - 5.50 = " << m7 << endl;

    return 0;
}