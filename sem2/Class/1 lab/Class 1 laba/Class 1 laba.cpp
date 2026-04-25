#include <iostream>
#include <cmath>

using namespace std;

class Point {
private:
	double first;
	double second;

public:
	Point() {
		this->first = 0.0;
		this->second = 0.0;
	}

	double distance(double x, double y) {
		return pow(pow(x - this->first, 2) + pow(y - this->second, 2), 0.5);
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	double x, y;
	cout << "Введите x1: ";
	cin >> x;
	cout << endl;
	cout << "Введите y1: ";
	cin >> y;
	cout << endl;

	Point a;
	cout << "Дистанция: " << a.distance(x, y) << endl;

	return 0;
}