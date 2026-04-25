#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// Константы
const int MAX_FIO = 100;
const int MAX_PHONE = 20;
const int MAX_ADDRESS = 200;
const char* FILENAME = "data.dat";

// Структура одной записи
struct Record {
    char fio[MAX_FIO];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    bool is_deleted;  // true - удалена, false - активна

    Record() : is_deleted(false) {
        fio[0] = '\0';
        phone[0] = '\0';
        address[0] = '\0';
    }
};

// Узел для хэш-таблицы (метод цепочек)
struct HashNode {
    Record* record;        // Указатель на запись
    HashNode* next;        // Следующий узел

    HashNode(Record* rec) : record(rec), next(nullptr) {}
};

// Структура хэш-таблицы
struct HashTable {
    HashNode** buckets;    // Массив указателей на начала цепочек
    int table_size;        // Размер таблицы
    int collisions;        // Счетчик коллизий
};

// Глобальные переменные для управления записями
vector<Record> records;              // Динамический массив записей
vector<vector<Record>> undo_stack;   // Стек для отмены операций

// ========== Функции для работы с хэш-таблицей ==========

// Хэш-функция: преобразуем строку адреса в число и берем mod M
unsigned long hashFunction(const char* key, int table_size) {
    unsigned long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % table_size;
}

// Создание хэш-таблицы
HashTable* createHashTable(int size) {
    HashTable* ht = new HashTable;
    ht->table_size = size;
    ht->collisions = 0;
    ht->buckets = new HashNode * [size];
    for (int i = 0; i < size; i++) {
        ht->buckets[i] = nullptr;
    }
    return ht;
}

// Удаление хэш-таблицы
void deleteHashTable(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < ht->table_size; i++) {
        HashNode* current = ht->buckets[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] ht->buckets;
    delete ht;
}

// Добавление записи в хэш-таблицу
void insertToHashTable(HashTable* ht, Record* record) {
    if (record->is_deleted) return;

    int index = hashFunction(record->address, ht->table_size);

    if (ht->buckets[index] != nullptr) {
        ht->collisions++;
    }

    HashNode* newNode = new HashNode(record);
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

// Поиск записи по адресу
Record* searchInHashTable(HashTable* ht, const char* address) {
    int index = hashFunction(address, ht->table_size);

    HashNode* current = ht->buckets[index];
    while (current != nullptr) {
        if (strcmp(current->record->address, address) == 0 &&
            !current->record->is_deleted) {
            return current->record;
        }
        current = current->next;
    }
    return nullptr;
}

// Перестроение хэш-таблицы
void rebuildHashTable(HashTable* ht) {
    // Очищаем текущую таблицу
    for (int i = 0; i < ht->table_size; i++) {
        HashNode* current = ht->buckets[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        ht->buckets[i] = nullptr;
    }
    ht->collisions = 0;

    // Добавляем все активные записи
    for (auto& rec : records) {
        if (!rec.is_deleted) {
            insertToHashTable(ht, &rec);
        }
    }
}

// ========== Вспомогательные функции ==========

// Генерация случайной строки
string randomString(int minLen, int maxLen) {
    int len = minLen + rand() % (maxLen - minLen + 1);
    string result;
    for (int i = 0; i < len; i++) {
        result += 'a' + rand() % 26;
    }
    return result;
}

// Генерация случайного телефона
string randomPhone() {
    return "+7" + to_string(900 + rand() % 100) +
        to_string(rand() % 10000000);
}

// Создание случайной записи
Record generateRandomRecord() {
    Record rec;
    string fio = randomString(5, 20) + " " +
        randomString(5, 15) + " " +
        randomString(5, 15);
    strcpy_s(rec.fio, MAX_FIO, fio.c_str());

    string phone = randomPhone();
    strcpy_s(rec.phone, MAX_PHONE, phone.c_str());

    string address = randomString(10, 30) + " str., " +
        to_string(rand() % 100) + " apt.";
    strcpy_s(rec.address, MAX_ADDRESS, address.c_str());

    rec.is_deleted = false;
    return rec;
}

// Создание массива из N записей
void createRandomRecords(int n) {
    records.clear();
    for (int i = 0; i < n; i++) {
        records.push_back(generateRandomRecord());
    }
    cout << "Создано " << n << " случайных записей." << endl;
}

// Сохранение в файл
void saveToFile() {
    ofstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    int count = 0;
    for (auto& rec : records) {
        if (!rec.is_deleted) {
            file.write(reinterpret_cast<char*>(&rec), sizeof(Record));
            count++;
        }
    }

    file.close();
    cout << "Сохранено " << count << " активных записей в файл." << endl;
}

// Загрузка из файла
void loadFromFile() {
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "Файл не найден или не может быть открыт!" << endl;
        return;
    }

    records.clear();
    Record rec;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        rec.is_deleted = false;
        records.push_back(rec);
    }

    file.close();
    cout << "Загружено " << records.size() << " записей из файла." << endl;
}

// Добавление записи в конец
void addRecord() {
    // Сохраняем состояние для отмены
    undo_stack.push_back(records);

    Record newRec;
    cout << "Введите ФИО: ";
    cin.ignore();
    cin.getline(newRec.fio, MAX_FIO);
    cout << "Введите номер телефона: ";
    cin.getline(newRec.phone, MAX_PHONE);
    cout << "Введите адрес: ";
    cin.getline(newRec.address, MAX_ADDRESS);
    newRec.is_deleted = false;

    records.push_back(newRec);
    cout << "Запись добавлена." << endl;
}

// Добавление в начало
void addToBeginning() {
    undo_stack.push_back(records);

    Record newRec;
    cout << "Введите ФИО: ";
    cin.ignore();
    cin.getline(newRec.fio, MAX_FIO);
    cout << "Введите номер телефона: ";
    cin.getline(newRec.phone, MAX_PHONE);
    cout << "Введите адрес: ";
    cin.getline(newRec.address, MAX_ADDRESS);
    newRec.is_deleted = false;

    records.insert(records.begin(), newRec);
    cout << "Запись добавлена в начало." << endl;
}

// Добавление на позицию
void addAtPosition() {
    int pos;
    cout << "Введите позицию (0-" << records.size() << "): ";
    cin >> pos;

    if (pos < 0 || pos > static_cast<int>(records.size())) {
        cout << "Неверная позиция!" << endl;
        return;
    }

    undo_stack.push_back(records);

    Record newRec;
    cout << "Введите ФИО: ";
    cin.ignore();
    cin.getline(newRec.fio, MAX_FIO);
    cout << "Введите номер телефона: ";
    cin.getline(newRec.phone, MAX_PHONE);
    cout << "Введите адрес: ";
    cin.getline(newRec.address, MAX_ADDRESS);
    newRec.is_deleted = false;

    records.insert(records.begin() + pos, newRec);
    cout << "Запись добавлена на позицию " << pos << endl;
}

// Физическое удаление помеченных записей
void physicallyDeleteDeleted() {
    vector<Record> new_records;
    for (auto& rec : records) {
        if (!rec.is_deleted) {
            new_records.push_back(rec);
        }
    }
    records = new_records;
    cout << "Физически удалено записей. Осталось: " << records.size() << endl;
}

// Проверка и физическое удаление записей, если удаленных > половины
void checkAndCleanDeleted() {
    int deleted_count = 0;
    for (auto& rec : records) {
        if (rec.is_deleted) deleted_count++;
    }

    if (deleted_count > static_cast<int>(records.size()) / 2) {
        cout << "Количество удаленных записей (" << deleted_count
            << ") превысило половину файла (" << records.size() / 2
            << "). Выполняется физическое удаление..." << endl;
        physicallyDeleteDeleted();
    }
}

// Удаление по ключу (адресу)
void deleteByKey() {
    char address[MAX_ADDRESS];
    cout << "Введите адрес для удаления: ";
    cin.ignore();
    cin.getline(address, MAX_ADDRESS);

    bool found = false;
    for (auto& rec : records) {
        if (!rec.is_deleted && strcmp(rec.address, address) == 0) {
            rec.is_deleted = true;
            found = true;
            cout << "Запись удалена (помечена как удаленная)." << endl;
        }
    }

    if (!found) {
        cout << "Запись с таким адресом не найдена!" << endl;
    }

    checkAndCleanDeleted();
}

// Удаление по номеру
void deleteByNumber() {
    int num;
    cout << "Введите номер записи (0-" << records.size() - 1 << "): ";
    cin >> num;

    if (num < 0 || num >= static_cast<int>(records.size())) {
        cout << "Неверный номер!" << endl;
        return;
    }

    if (records[num].is_deleted) {
        cout << "Запись уже удалена!" << endl;
        return;
    }

    undo_stack.push_back(records);
    records[num].is_deleted = true;
    cout << "Запись #" << num << " удалена." << endl;

    checkAndCleanDeleted();
}

// Отмена последнего удаления
void undoLastDelete() {
    if (undo_stack.empty()) {
        cout << "Нет операций для отмены!" << endl;
        return;
    }

    records = undo_stack.back();
    undo_stack.pop_back();
    cout << "Последняя операция отменена." << endl;
}

// Корректировка по ключу
void editByKey() {
    char address[MAX_ADDRESS];
    cout << "Введите адрес записи для корректировки: ";
    cin.ignore();
    cin.getline(address, MAX_ADDRESS);

    for (auto& rec : records) {
        if (!rec.is_deleted && strcmp(rec.address, address) == 0) {
            cout << "Найдена запись:" << endl;
            cout << "ФИО: " << rec.fio << endl;
            cout << "Телефон: " << rec.phone << endl;
            cout << "Адрес: " << rec.address << endl;

            cout << "Введите новые данные:" << endl;
            cout << "ФИО: ";
            cin.getline(rec.fio, MAX_FIO);
            cout << "Телефон: ";
            cin.getline(rec.phone, MAX_PHONE);
            cout << "Адрес: ";
            cin.getline(rec.address, MAX_ADDRESS);

            cout << "Запись скорректирована." << endl;
            return;
        }
    }
    cout << "Запись с таким адресом не найдена!" << endl;
}

// Корректировка по номеру
void editByNumber() {
    int num;
    cout << "Введите номер записи (0-" << records.size() - 1 << "): ";
    cin >> num;

    if (num < 0 || num >= static_cast<int>(records.size())) {
        cout << "Неверный номер!" << endl;
        return;
    }

    if (records[num].is_deleted) {
        cout << "Запись удалена!" << endl;
        return;
    }

    cout << "Текущие данные:" << endl;
    cout << "ФИО: " << records[num].fio << endl;
    cout << "Телефон: " << records[num].phone << endl;
    cout << "Адрес: " << records[num].address << endl;

    cout << "Введите новые данные:" << endl;
    cout << "ФИО: ";
    cin.ignore();
    cin.getline(records[num].fio, MAX_FIO);
    cout << "Телефон: ";
    cin.getline(records[num].phone, MAX_PHONE);
    cout << "Адрес: ";
    cin.getline(records[num].address, MAX_ADDRESS);

    cout << "Запись #" << num << " скорректирована." << endl;
}

// Вывод всех записей
void displayAll() {
    cout << "\n=== Все записи ===" << endl;
    int active_count = 0;
    for (size_t i = 0; i < records.size(); i++) {
        if (!records[i].is_deleted) {
            cout << "#" << i << " | ФИО: " << records[i].fio
                << " | Тел: " << records[i].phone
                << " | Адрес: " << records[i].address << endl;
            active_count++;
        }
    }
    cout << "Всего активных записей: " << active_count << endl;
    cout << "Всего записей (включая удаленные): " << records.size() << endl;
}

// Поиск с использованием хэш-таблицы
void searchWithHash(int table_size) {
    if (records.empty()) {
        cout << "Нет записей для поиска!" << endl;
        return;
    }

    HashTable* hashTable = createHashTable(table_size);
    rebuildHashTable(hashTable);

    char address[MAX_ADDRESS];
    cout << "Введите адрес для поиска: ";
    cin.ignore();
    cin.getline(address, MAX_ADDRESS);

    Record* found = searchInHashTable(hashTable, address);

    if (found != nullptr) {
        cout << "Запись найдена!" << endl;
        cout << "ФИО: " << found->fio << endl;
        cout << "Телефон: " << found->phone << endl;
        cout << "Адрес: " << found->address << endl;
    }
    else {
        cout << "Запись с адресом \"" << address << "\" не найдена!" << endl;
    }

    cout << "Количество коллизий при размере таблицы " << table_size
        << ": " << hashTable->collisions << endl;

    deleteHashTable(hashTable);
}

// Анализ коллизий для разных размеров таблицы
void analyzeCollisions() {
    if (records.empty()) {
        cout << "Нет записей для анализа!" << endl;
        return;
    }

    int sizes[] = { 40, 75, 90 };

    for (int i = 0; i < 3; i++) {
        int size = sizes[i];
        HashTable* hashTable = createHashTable(size);
        rebuildHashTable(hashTable);
        cout << "Размер таблицы: " << size
            << ", Коллизий: " << hashTable->collisions << endl;
        deleteHashTable(hashTable);
    }
}

// Сохранение изменений в файл
void saveChanges() {
    saveToFile();
}

// Функция отображения меню
void showMenu() {
    cout << "\n========== МЕНЮ ==========" << endl;
    cout << "1. Создать массив из 100 случайных записей" << endl;
    cout << "2. Сохранить массив в файл" << endl;
    cout << "3. Загрузить массив из файла" << endl;
    cout << "4. Добавить запись в начало" << endl;
    cout << "5. Добавить запись в конец" << endl;
    cout << "6. Добавить запись на позицию" << endl;
    cout << "7. Удалить запись по адресу (ключу)" << endl;
    cout << "8. Удалить запись по номеру" << endl;
    cout << "9. Отменить последнее удаление" << endl;
    cout << "10. Корректировать запись по адресу" << endl;
    cout << "11. Корректировать запись по номеру" << endl;
    cout << "12. Вывести все записи" << endl;
    cout << "13. Поиск по адресу (с хэш-таблицей)" << endl;
    cout << "14. Анализ коллизий (размеры 40, 75, 90)" << endl;
    cout << "15. Сохранить изменения в файл" << endl;
    cout << "0. Выход" << endl;
    cout << "========================" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Ru");

    srand(static_cast<unsigned int>(time(nullptr)));
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            createRandomRecords(100);
            break;
        case 2:
            saveToFile();
            break;
        case 3:
            loadFromFile();
            break;
        case 4:
            addToBeginning();
            break;
        case 5:
            addRecord();
            break;
        case 6:
            addAtPosition();
            break;
        case 7:
            deleteByKey();
            break;
        case 8:
            deleteByNumber();
            break;
        case 9:
            undoLastDelete();
            break;
        case 10:
            editByKey();
            break;
        case 11:
            editByNumber();
            break;
        case 12:
            displayAll();
            break;
        case 13: {
            int size;
            cout << "Введите размер хэш-таблицы: ";
            cin >> size;
            searchWithHash(size);
            break;
        }
        case 14:
            analyzeCollisions();
            break;
        case 15:
            saveChanges();
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}