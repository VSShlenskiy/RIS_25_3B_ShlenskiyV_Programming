#include <iostream>
#include <clocale>
using namespace std;

int sumBelowMainDiagonal(int** matrix, int n) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            total += matrix[i][j];
        }
    }
    return total;
}

void completionMatrix(int** mat1, int n) {
    cout << "Введите матрицу: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat1[i][j];
        }
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    int N, MAX_SUM = -1;
    cout << "Введите кол-во матриц: " << endl;
    cin >> N;
    for (int k = 0; k < N; k++) {
        int n, total = 0;
        cout << "Введите длину стороны матрицы: " << endl;
        cin >> n;
        int** mat1 = new int* [n];
        for (int i = 0; i < n; i++) {
            mat1[i] = new int[n];
        }

        completionMatrix(mat1, n);

        total = sumBelowMainDiagonal(mat1, n);

        cout << "Сумма ниже главной диагонали: " << total << endl;

        if (total > MAX_SUM) MAX_SUM = total;

        for (int i = 0; i < n; i++) {
            delete[] mat1[i];
        }
        delete[] mat1;
    }

    cout << "Максимальное значение такой суммы в N матрицах: " << MAX_SUM;

    return 0;
}