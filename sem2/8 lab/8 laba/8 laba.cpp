#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h>

using namespace std;

struct Patient {
    char surname[50];
    char name[50];
    char patronymic[50];
    char address[100];
    char numberMedicalCard[20];
    char numberInsurancePolicy[20];
};

void InitPatient(Patient& p) {
    strcpy_s(p.surname, "");
    strcpy_s(p.name, "");
    strcpy_s(p.patronymic, "");
    strcpy_s(p.address, "");
    strcpy_s(p.numberMedicalCard, "");
    strcpy_s(p.numberInsurancePolicy, "");
}

Patient InputPatient() {
    Patient p;
    InitPatient(p);

    cout << "Введите фамилию: ";
    cin >> p.surname;

    cout << "Введите имя: ";
    cin >> p.name;

    cout << "Введите отчество: ";
    cin >> p.patronymic;

    cout << "Введите домашний адрес: ";
    cin.ignore();
    cin.getline(p.address, 100);

    cout << "Введите номер медицинской карты: ";
    cin >> p.numberMedicalCard;

    cout << "Введите номер страхового полиса: ";
    cin >> p.numberInsurancePolicy;

    return p;
}

void DisplayPatient(const Patient& p) {
    cout << "ФИО: " << p.surname << " " << p.name << " " << p.patronymic << endl;
    cout << "Адрес: " << p.address << endl;
    cout << "Номер мед. карты: " << p.numberMedicalCard << endl;
    cout << "Номер полиса: " << p.numberInsurancePolicy << endl;
    cout << "------------------------" << endl;
}

int GetFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) return 0;

    int fileSize = file.tellg();
    file.close();

    if (fileSize <= 0) return 0;
    return fileSize / sizeof(Patient);
}

Patient* ReadAllFromFile(const string& filename, int& count) {
    count = GetFileSize(filename);
    if (count == 0) return nullptr;

    Patient* patients = new Patient[count];

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        delete[] patients;
        return nullptr;
    }

    file.read(reinterpret_cast<char*>(patients), count * sizeof(Patient));
    file.close();

    return patients;
}

void WriteAllToFile(const string& filename, Patient* patients, int count) {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    file.write(reinterpret_cast<char*>(patients), count * sizeof(Patient));
    file.close();
}

bool DeletePatientByCardNumber(const string& filename, const char* cardNumber) {
    int count;
    Patient* patients = ReadAllFromFile(filename, count);

    if (!patients || count == 0) {
        cout << "Файл пуст или не существует." << endl;
        return false;
    }

    int indexToDelete = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(patients[i].numberMedicalCard, cardNumber) == 0) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        delete[] patients;
        return false;
    }

    Patient* newPatients = new Patient[count - 1];

    for (int i = 0; i < indexToDelete; i++) {
        newPatients[i] = patients[i];
    }

    for (int i = indexToDelete + 1; i < count; i++) {
        newPatients[i - 1] = patients[i];
    }

    WriteAllToFile(filename, newPatients, count - 1);

    delete[] patients;
    delete[] newPatients;

    return true;
}

void AddTwoToBeginning(const string& filename) {
    int count;
    Patient* patients = ReadAllFromFile(filename, count);

    Patient* newPatients = new Patient[count + 2];

    cout << "\nВведите первого пациента для добавления в начало:" << endl;
    newPatients[0] = InputPatient();

    cout << "\nВведите второго пациента для добавления в начало:" << endl;
    newPatients[1] = InputPatient();

    if (patients && count > 0) {
        for (int i = 0; i < count; i++) {
            newPatients[i + 2] = patients[i];
        }
    }

    WriteAllToFile(filename, newPatients, count + 2);

    if (patients) delete[] patients;
    delete[] newPatients;
}

void DisplayFile(const string& filename) {
    int count;
    Patient* patients = ReadAllFromFile(filename, count);

    if (!patients || count == 0) {
        cout << "Файл пуст или не существует." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "Запись #" << i + 1 << endl;
        DisplayPatient(patients[i]);
    }

    delete[] patients;
}

void CreateTestFile(const string& filename) {
    Patient testPatients[3];

    strcpy_s(testPatients[0].surname, "Иванов");
    strcpy_s(testPatients[0].name, "Иван");
    strcpy_s(testPatients[0].patronymic, "Иванович");
    strcpy_s(testPatients[0].address, "ул. Ленина, 10");
    strcpy_s(testPatients[0].numberMedicalCard, "001");
    strcpy_s(testPatients[0].numberInsurancePolicy, "123456");

    strcpy_s(testPatients[1].surname, "Петров");
    strcpy_s(testPatients[1].name, "Петр");
    strcpy_s(testPatients[1].patronymic, "Петрович");
    strcpy_s(testPatients[1].address, "ул. Гагарина, 5");
    strcpy_s(testPatients[1].numberMedicalCard, "002");
    strcpy_s(testPatients[1].numberInsurancePolicy, "789012");

    strcpy_s(testPatients[2].surname, "Сидоров");
    strcpy_s(testPatients[2].name, "Сидор");
    strcpy_s(testPatients[2].patronymic, "Сидорович");
    strcpy_s(testPatients[2].address, "ул. Пушкина, 15");
    strcpy_s(testPatients[2].numberMedicalCard, "003");
    strcpy_s(testPatients[2].numberInsurancePolicy, "345678");

    WriteAllToFile(filename, testPatients, 3);
    cout << "Создан тестовый файл с 3 записями." << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename = "C:\\Users\\slens\\OneDrive\\Рабочий стол\\c++\\structure\\file1.dat";

    ifstream testFile(filename, ios::binary);
    if (!testFile.is_open()) {
        cout << "Файл не найден. Создаем тестовый файл..." << endl;
        CreateTestFile(filename);
    }
    else {
        testFile.close();
    }

    cout << "\n--- Исходный файл ---" << endl;
    DisplayFile(filename);

    char cardNumber[20];
    cout << "\nВведите номер медицинской карты для удаления: ";
    cin >> cardNumber;

    if (DeletePatientByCardNumber(filename, cardNumber)) {
        cout << "Пациент с номером карты " << cardNumber << " удален." << endl;
    }
    else {
        cout << "Пациент с номером карты " << cardNumber << " не найден." << endl;
    }

    AddTwoToBeginning(filename);

    cout << "\n--- Итоговый файл ---" << endl;
    DisplayFile(filename);

    cout << "\nПрограмма завершена. Данные сохранены в файл " << filename << endl;

    return 0;
}