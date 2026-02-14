#include <iostream>
#include <cstdlib>
#include <clocale>

using namespace std;

// Функция для печати массива
void printArray(int arr[], int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция для удаления первого элемента с заданным значением
int removeFirstValue(int arr[], int& size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--;
            return 1;
        }
    }
    return 0;
}

// Функция для циклического сдвига массива вправо на K элементов
void cyclicShiftRight(int arr[], int size, int K) {
    if (size == 0) return;

    K = K % size;
    if (K == 0) return;

    int* temp = new int[K];

    for (int i = 0; i < K; i++) {
        temp[i] = arr[size - K + i];
    }

    for (int i = size - 1; i >= K; i--) {
        arr[i] = arr[i - K];
    }

    for (int i = 0; i < K; i++) {
        arr[i] = temp[i];
    }

    delete[] temp;
}

int main() {
    setlocale(LC_ALL, "Ru");

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    // 1) Формирование одномерного массива целых чисел
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    int currentSize = n;

    // 2) Распечатка полученного массива
    cout << "\nСгенерированный массив:" << endl;
    printArray(arr, currentSize);

    // 3) Удаление первого элемента с заданным значением
    int valueToRemove;
    cout << "\nВведите значение для удаления первого элемента: ";
    cin >> valueToRemove;

    if (removeFirstValue(arr, currentSize, valueToRemove)) {
        printArray(arr, currentSize);
    }
    else {
        cout << "Элемент со значением " << valueToRemove << " не найден." << endl;
    }

    // 4) Циклический сдвиг массива вправо на K элементов
    int K;
    cout << "\nВведите количество элементов для сдвига (K): ";
    cin >> K;

    cyclicShiftRight(arr, currentSize, K);

    // 5) Распечатка полученного массива
    cout << "\nМассив после циклического сдвига вправо на " << K << " элементов:" << endl;
    printArray(arr, currentSize);

    delete[] arr;

    return 0;
}