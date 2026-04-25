#include <iostream>
#include <string>

using namespace std;

class Triad {
protected:
    int first;
    int second;
    int third;

public:
    Triad() {
        this->first = 0;
        this->second = 0;
        this->third = 0;
    }

    Triad(int first, int second, int third) {
        this->first = first;
        this->second = second;
        this->third = third;
    }

    Triad(const Triad& other) {
        this->first = other.first;
        this->second = other.second;
        this->third = other.third;
    }

    virtual ~Triad() {}

    void SetFirst(int first) {
        this->first = first;
    }
    int GetFirst() const {
        return this->first;
    }

    void SetSecond(int second) {
        this->second = second;
    }
    int GetSecond() const {
        return this->second;
    }

    void SetThird(int third) {
        this->third = third;
    }
    int GetThird() const {
        return this->third;
    }

    Triad& operator=(const Triad& other) {
        if (this != &other) {
            this->first = other.first;
            this->second = other.second;
            this->third = other.third;
        }
        return *this;
    }

    bool operator==(const Triad& other) const {
        return (first == other.first &&
            second == other.second &&
            third == other.third);
    }

    bool operator!=(const Triad& other) const {
        return !(*this == other);
    }

    bool operator<(const Triad& other) const {
        if (first != other.first) return first < other.first;
        if (second != other.second) return second < other.second;
        return third < other.third;
    }

    bool operator>(const Triad& other) const {
        return other < *this;
    }

    bool operator<=(const Triad& other) const {
        return !(*this > other);
    }

    bool operator>=(const Triad& other) const {
        return !(*this < other);
    }

    friend ostream& operator<<(ostream& out, const Triad& other);
    friend istream& operator>>(istream& in, Triad& other);
};

ostream& operator<<(ostream& out, const Triad& other) {
    out << "first: " << other.first << endl;
    out << "second: " << other.second << endl;
    out << "third: " << other.third << endl;
    return out;
}

istream& operator>>(istream& in, Triad& other) {
    cout << "first: "; in >> other.first;
    cout << "second: "; in >> other.second;
    cout << "third: "; in >> other.third;
    return in;
}

class Time : public Triad {
public:
    Time() : Triad(0, 0, 0) {}

    Time(int hours, int minutes, int seconds) : Triad(hours, minutes, seconds) {}

    Time(const Time& other) : Triad(other) {}

    ~Time() {}

    void setHours(int hours) {
        first = hours;
    }

    int getHours() const {
        return first;
    }

    void setMinutes(int minutes) {
        second = minutes;
    }

    int getMinutes() const {
        return second;
    }

    void setSeconds(int seconds) {
        third = seconds;
    }

    int getSeconds() const {
        return third;
    }

    long toSeconds() const {
        return getHours() * 3600L + getMinutes() * 60 + getSeconds();
    }

    bool operator==(const Time& other) const {
        return this->toSeconds() == other.toSeconds();
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    bool operator<(const Time& other) const {
        return this->toSeconds() < other.toSeconds();
    }

    bool operator>(const Time& other) const {
        return this->toSeconds() > other.toSeconds();
    }

    bool operator<=(const Time& other) const {
        return !(*this > other);
    }

    bool operator>=(const Time& other) const {
        return !(*this < other);
    }

    void addHours(int h) {
        first += h;
    }

    void addMinutes(int m) {
        second += m;
        if (second >= 60) {
            first += second / 60;
            second %= 60;
        }
    }

    void addSeconds(int s) {
        third += s;
        if (third >= 60) {
            second += third / 60;
            third %= 60;
        }
        addMinutes(0);
    }

    string toString() const {
        string result = "";
        if (first < 10) result += "0";
        result += to_string(first) + ":";
        if (second < 10) result += "0";
        result += to_string(second) + ":";
        if (third < 10) result += "0";
        result += to_string(third);
        return result;
    }

    friend ostream& operator<<(ostream& out, const Time& time);
    friend istream& operator>>(istream& in, Time& time);
};

ostream& operator<<(ostream& out, const Time& time) {
    out << time.getHours() << "ч "
        << time.getMinutes() << "м "
        << time.getSeconds() << "с";
    return out;
}

istream& operator>>(istream& in, Time& time) {
    int h, m, s;
    cout << "Введите часы: "; in >> h;
    cout << "Введите минуты: "; in >> m;
    cout << "Введите секунды: "; in >> s;
    time.setHours(h);
    time.setMinutes(m);
    time.setSeconds(s);
    return in;
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "========== ТЕСТИРОВАНИЕ TRIAD ==========" << endl;
    Triad t1(1, 2, 3);
    Triad t2(1, 2, 4);

    cout << "t1: \n" << t1;
    cout << "t2: \n" << t2;
    cout << "t1 < t2: " << (t1 < t2 ? "true" : "false") << endl;
    cout << "t1 > t2: " << (t1 > t2 ? "true" : "false") << endl;

    cout << "\n========== ТЕСТИРОВАНИЕ TIME ==========" << endl;

    Time time1(10, 30, 45);
    Time time2(9, 59, 59);
    Time time3(10, 30, 45);

    cout << "Время 1: " << time1 << endl;
    cout << "Время 2: " << time2 << endl;
    cout << "Время 3: " << time3 << endl;

    cout << "\n--- Сравнение времени ---" << endl;
    cout << "time1 == time3: " << (time1 == time3 ? "true" : "false") << endl;
    cout << "time1 != time2: " << (time1 != time2 ? "true" : "false") << endl;
    cout << "time1 > time2: " << (time1 > time2 ? "true" : "false") << endl;
    cout << "time1 < time2: " << (time1 < time2 ? "true" : "false") << endl;
    cout << "time2 <= time1: " << (time2 <= time1 ? "true" : "false") << endl;

    cout << "\n--- Конвертация в секунды ---" << endl;
    cout << "time1 в секундах: " << time1.toSeconds() << " сек" << endl;
    cout << "time2 в секундах: " << time2.toSeconds() << " сек" << endl;

    cout << "\n--- Изменение времени ---" << endl;
    time1.setHours(12);
    time1.setMinutes(0);
    time1.setSeconds(0);
    cout << "После изменения: " << time1 << endl;

    cout << "\n--- Дополнительные операции ---" << endl;
    Time time4(23, 55, 50);
    cout << "Исходное время: " << time4 << endl;

    time4.addMinutes(10);
    cout << "После addMinutes(10): " << time4 << endl;

    time4.addSeconds(30);
    cout << "После addSeconds(30): " << time4 << endl;

    cout << "\n--- Форматированный вывод (ЧЧ:ММ:СС) ---" << endl;
    Time time5(8, 5, 3);
    cout << "Время: " << time5.toString() << endl;

    cout << "\n--- Ввод времени с клавиатуры ---" << endl;
    Time time6;
    cin >> time6;
    cout << "Вы ввели: " << time6 << endl;

    return 0;
}