#include <iostream>
#include <clocale>

using namespace std;

int** createMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrix(int** matrix, int rows, int cols) {
    cout << "Заполните матрицу: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << endl;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int** addColumn(int** matrix, int& cols, int rows, int defaultValue) {
    int columnIndex;
    cout << "Введите индекс столбца, куда добавить столбец: " << endl;
    cin >> columnIndex;
    cout << endl;
    while (columnIndex < 0 || columnIndex > cols) {
        cout << "Ошибка: недопустимый индекс столбца! " << "Введите индекс ещё раз: " << endl;
        cin >> columnIndex;
        cout << endl;
    }

    int** newMatrix = createMatrix(rows, cols + 1);

    for (int i = 0; i < rows; i++) {
        int newCol = 0;
        for (int j = 0; j < cols; j++) {
            if (newCol == columnIndex) {
                newMatrix[i][newCol++] = defaultValue;
            }
            newMatrix[i][newCol++] = matrix[i][j];
        }
        
        if (columnIndex == cols) {
            newMatrix[i][columnIndex] = defaultValue;
        }
    }

    deleteMatrix(matrix, rows);

    cols++;

    return newMatrix;
}

int main() {
    setlocale(LC_ALL, "Ru");
    int rows, cols;
    cout << "Введите кол-во строк и столбцов: " << endl;
    cin >> rows >> cols;
    cout << endl;
    
    int** matrix = createMatrix(rows, cols);
    fillMatrix(matrix, rows, cols);

    cout << "Исходный массив:" << endl;
    printMatrix(matrix, rows, cols);

    int defaultValue;
    cout << "Введите одно значение, которое будет записано в столбце: " << endl;
    cin >> defaultValue;
    cout << endl;
    matrix = addColumn(matrix, cols, rows, defaultValue);

    if (matrix) {
        cout << "После добавления столбца: " << endl;
        printMatrix(matrix, rows, cols);
    }
    
    deleteMatrix(matrix, rows);

    return 0;
}