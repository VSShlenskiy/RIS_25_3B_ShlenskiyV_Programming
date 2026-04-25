#include <iostream>

struct Node {
    int key;
    Node* next;

    Node(int value) : key(value), next(nullptr) {}
};

Node* head = nullptr;
Node* tail = nullptr;
int size = 0;

void pushBack(int value) {
    Node* newNode = new Node(value);

    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void pushFront(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void insertAfter(Node* node, int value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->next = node->next;
    node->next = newNode;

    if (node == tail) {
        tail = newNode;
    }
    size++;
}

Node* findNodeBeforeIndex(int index) {
    if (index <= 1 || index > size) return nullptr;

    Node* current = head;
    for (int i = 1; i < index - 1; i++) {
        current = current->next;
    }
    return current;
}

Node* getNodeByIndex(int index) {
    if (index < 1 || index > size) return nullptr;

    Node* current = head;
    for (int i = 1; i < index; i++) {
        current = current->next;
    }
    return current;
}

void removeAfter(Node* prevNode) {
    if (prevNode == nullptr || prevNode->next == nullptr) return;

    Node* toDelete = prevNode->next;
    prevNode->next = toDelete->next;

    if (toDelete == tail) {
        tail = prevNode;
    }

    delete toDelete;
    size--;
}

bool removeBeforeIndex(int index, int K) {
    Node* targetNode = getNodeByIndex(index);
    if (targetNode == nullptr) {
        std::cout << "Элемент с номером " << index << " не найден!" << std::endl;
        return false;
    }

    int removed = 0;

    if (index == 1) {
        while (head != targetNode && removed < K && head != nullptr) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            removed++;
            size--;
        }
        if (head == nullptr) tail = nullptr;
    }
    else {
        Node* currentPrev = findNodeBeforeIndex(index);
        Node* beforePrev = nullptr;

        if (currentPrev != head) {
            beforePrev = head;
            while (beforePrev != nullptr && beforePrev->next != currentPrev) {
                beforePrev = beforePrev->next;
            }
        }

        while (removed < K && currentPrev != nullptr) {
            if (beforePrev == nullptr) {
                head = currentPrev->next;
                delete currentPrev;
                currentPrev = nullptr;
            }
            else {
                Node* toDelete = beforePrev->next;
                beforePrev->next = toDelete->next;
                delete toDelete;
                currentPrev = beforePrev->next;
            }
            removed++;
            size--;

            if (head == nullptr) {
                tail = nullptr;
                break;
            }
        }
    }

    std::cout << "Удалено " << removed << " элементов перед элементом " << index << std::endl;
    return true;
}

void addToEnd(int K) {
    std::cout << "Введите " << K << " элементов для добавления в конец:" << std::endl;

    for (int i = 0; i < K; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        pushBack(value);
    }

    std::cout << "Добавлено " << K << " элементов в конец списка" << std::endl;
}

void printList() {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    std::cout << "Список (размер " << size << "): ";
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void clearList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

int getSize() {
    return size;
}

int main() {
    setlocale(LC_ALL, "Ru");

    int n, K, index;

    std::cout << "Введите количество элементов для начального заполнения: ";
    std::cin >> n;

    std::cout << "Введите " << n << " элементов:" << std::endl;
    for (int i = 0; i < n; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        pushBack(value);
    }

    std::cout << "\nНачальный ";
    printList();

    std::cout << "\nВведите номер элемента, перед которым нужно удалить: ";
    std::cin >> index;
    std::cout << "Введите количество элементов для удаления (K): ";
    std::cin >> K;

    if (removeBeforeIndex(index, K)) {
        std::cout << "После удаления ";
        printList();
    }

    std::cout << "\nВведите количество элементов для добавления в конец (K): ";
    std::cin >> K;

    addToEnd(K);
    std::cout << "Итоговый ";
    printList();

    clearList();

    return 0;
}