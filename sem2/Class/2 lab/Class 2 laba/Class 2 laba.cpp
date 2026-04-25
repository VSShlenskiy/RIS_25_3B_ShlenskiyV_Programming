#include <iostream>

using namespace std;

class Employer {
public:
	string FIO;
	string dolzhnost;
	double zarplata;
public:
	Employer() {
		this->FIO = "Иванов Иван Иванович";
		this->dolzhnost = "Менеджер";
		this->zarplata = 15000.5;
	}

	Employer(string FIO, string dolzhnost, double zarplata) {
		this->FIO = FIO;
		this->dolzhnost = dolzhnost;
		this->zarplata = zarplata;
	}

	Employer(Employer& a) {
		this->FIO = a.FIO;
		this->dolzhnost = a.dolzhnost;
		this->zarplata = a.zarplata;
	}

	void Set(string FIO, string dolzhnost, double zarplata) {
		this->FIO = FIO;
		this->dolzhnost = dolzhnost;
		this->zarplata = zarplata;
	}

	string GetFIO() {
		return this->FIO;
	}

	string GetDolzhnost() {
		return this->dolzhnost;
	}

	double GetZarplata() {
		return this->zarplata;
	}

	~Employer() {}

	void Print() {
		cout << "ФИО: " << this->FIO << endl;
		cout << "Должность: " << this->dolzhnost << endl;
		cout << "Зарплата: " << this->zarplata << endl;
		cout << endl;
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	Employer manager;
	Employer director("Петров Пётр Петрович", "Директор", 100000);
	Employer economyst{ director };

	cout << "Конструктор без параметров: " << endl;
	manager.Print();

	cout << "Конструктор с параметрами: " << endl;
	director.Print();

	cout << "Конструктор копирования: " << endl;
	economyst.Print();

	cout << "С помощью сеттера: " << endl;
	manager.Set("Алгоритмов Алгоритм Алгоритмович", "Смысловик", 666666666666666);
	manager.Print();

	return 0;
}