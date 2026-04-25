#include <iostream>

struct Node {
    int key;
    Node* next;

    Node(int value) : key(value), next(nullptr) {}
};

struct Queue {
    Node* front;   // начало очереди (откуда удаляем)
    Node* rear;    // конец очереди (куда добавляем)
    int size;
};

// Инициализация очереди
void initQueue(Queue& queue) {
    queue.front = nullptr;
    queue.rear = nullptr;
    queue.size = 0;
}

// Очистка очереди (освобождение памяти)
void clearQueue(Queue& queue) {
    while (queue.front != nullptr) {
        Node* temp = queue.front;
        queue.front = queue.front->next;
        delete temp;
    }
    queue.rear = nullptr;
    queue.size = 0;
}

// Функция для добавления элемента в конец очереди (enqueue)
void enqueue(Queue& queue, int value) {
    Node* newNode = new Node(value);

    if (queue.rear == nullptr) {
        queue.front = queue.rear = newNode;
    }
    else {
        queue.rear->next = newNode;
        queue.rear = newNode;
    }
    queue.size++;
}

// Функция для удаления элемента из начала очереди (dequeue)
int dequeue(Queue& queue) {
    if (queue.front == nullptr) {
        std::cout << "Очередь пуста!" << std::endl;
        return -1;
    }

    Node* toDelete = queue.front;
    int value = toDelete->key;
    queue.front = queue.front->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }

    delete toDelete;
    queue.size--;

    return value;
}

// Функция для просмотра первого элемента очереди
int peek(Queue& queue) {
    if (queue.front == nullptr) {
        std::cout << "Очередь пуста!" << std::endl;
        return -1;
    }
    return queue.front->key;
}

// Функция для добавления K элементов в конец очереди
void addToEnd(Queue& queue, int K) {
    std::cout << "Введите " << K << " элементов для добавления в очередь:" << std::endl;

    for (int i = 0; i < K; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        enqueue(queue, value);
    }

    std::cout << "Добавлено " << K << " элементов в очередь" << std::endl;
}

// Функция для удаления K элементов из начала очереди
void removeFromFront(Queue& queue, int K) {
    int removed = 0;

    for (int i = 0; i < K && queue.front != nullptr; i++) {
        int value = dequeue(queue);
        if (value != -1) {
            std::cout << "Удален элемент: " << value << std::endl;
            removed++;
        }
    }

    std::cout << "Удалено " << removed << " элементов из очереди" << std::endl;
}

// Функция для вывода очереди
void printQueue(Queue& queue) {
    if (queue.front == nullptr) {
        std::cout << "Очередь пуста" << std::endl;
        return;
    }

    std::cout << "Очередь (размер " << queue.size << "): ";
    Node* current = queue.front;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->key;
        if (current->next != nullptr) {
            std::cout << ", ";
        }
        current = current->next;
    }
    std::cout << "] (начало слева, конец справа)" << std::endl;
}

// Функция для получения размера очереди
int getSize(Queue& queue) {
    return queue.size;
}

// Функция для поиска элемента в очереди
bool searchInQueue(Queue& queue, int value) {
    Node* current = queue.front;
    int position = 1;

    while (current != nullptr) {
        if (current->key == value) {
            std::cout << "Элемент " << value << " найден на позиции " << position
                << " (от начала очереди)" << std::endl;
            return true;
        }
        current = current->next;
        position++;
    }

    std::cout << "Элемент " << value << " не найден в очереди" << std::endl;
    return false;
}

// Функция для удаления K элементов перед указанным индексом
bool removeBeforeIndex(Queue& queue, int index, int K) {
    if (index < 1 || index > queue.size) {
        std::cout << "Элемент с номером " << index << " не найден!" << std::endl;
        return false;
    }

    if (index == 1) {
        std::cout << "Перед первым элементом нет элементов для удаления" << std::endl;
        return false;
    }

    // Создаем временную очередь для хранения элементов
    Queue tempQueue;
    initQueue(tempQueue);

    int removed = 0;
    int currentPos = 1;

    // Переносим элементы во временную очередь до нужного индекса
    while (queue.front != nullptr && currentPos < index) {
        int value = dequeue(queue);

        if (currentPos < index - K) {
            // Сохраняем элементы, которые не нужно удалять
            enqueue(tempQueue, value);
        }
        else if (currentPos < index) {
            // Удаляем эти элементы
            std::cout << "Удален элемент: " << value << std::endl;
            removed++;
        }
        currentPos++;
    }

    // Переносим оставшиеся элементы (включая целевой и после него)
    while (queue.front != nullptr) {
        enqueue(tempQueue, dequeue(queue));
    }

    // Возвращаем элементы обратно в исходную очередь
    while (tempQueue.front != nullptr) {
        enqueue(queue, dequeue(tempQueue));
    }

    clearQueue(tempQueue);

    std::cout << "Удалено " << removed << " элементов перед элементом " << index << std::endl;
    return true;
}

int main() {
    setlocale(LC_ALL, "Ru");

    Queue queue;
    initQueue(queue);

    int n, K, index;

    std::cout << "Введите количество элементов для начального заполнения: ";
    std::cin >> n;

    std::cout << "Введите " << n << " элементов:" << std::endl;
    for (int i = 0; i < n; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        enqueue(queue, value);
    }

    std::cout << "\nНачальная ";
    printQueue(queue);

    std::cout << "\nВведите номер элемента, перед которым нужно удалить: ";
    std::cin >> index;
    std::cout << "Введите количество элементов для удаления (K): ";
    std::cin >> K;

    if (removeBeforeIndex(queue, index, K)) {
        std::cout << "После удаления ";
        printQueue(queue);
    }

    std::cout << "\nВведите количество элементов для добавления в конец очереди (K): ";
    std::cin >> K;

    addToEnd(queue, K);
    std::cout << "Итоговая ";
    printQueue(queue);

    // Освобождаем память перед завершением программы
    clearQueue(queue);

    return 0;
}