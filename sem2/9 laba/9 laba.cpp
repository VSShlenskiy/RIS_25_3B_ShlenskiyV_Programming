#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

void copy(string line) {
    ofstream out("D:\\repositories\\RIS_25_3B_ShlenskiyV_Programming\\sem2\\9 laba\\File2.txt", ios::app);
    if (out.is_open()) {
        out << line << endl;
    }
    out.close();
}

void longWord() {
    string line, word;
    int cnt, max = INT16_MIN;

    ifstream in("D:\\repositories\\RIS_25_3B_ShlenskiyV_Programming\\sem2\\9 laba\\File2.txt");
    if (!in.is_open()) {
        cout << "Ошибка открытия файла File2.txt" << endl;
        return;
    }

    if (in.is_open()) {
        while (getline(in, line)) {
            cnt = line.length();
            if (cnt > max) {
                word = line;
                max = cnt;
            }
        }
    }
    cout << "Самое длинное слово: " << word << endl;
    in.close();
}

int main() {
    setlocale(LC_ALL, "Ru");

    string line;
    ifstream in("D:\\repositories\\RIS_25_3B_ShlenskiyV_Programming\\sem2\\9 laba\\File1.txt");

    if (!in.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    while (getline(in, line)) {
        if (line.empty()) continue;

        bool hasSpace = false;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || line[i] == '\t') {
                hasSpace = true;
                break;
            }
        }

        if (!hasSpace) {
            copy(line);
        }
    }

    cout << "Копирование прошло успешно!" << endl;

    longWord();

    in.close();
    return 0;
}