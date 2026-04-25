#include <iostream>

struct Node {
    int key;
    Node* next;

    Node(int value) : key(value), next(nullptr) {}
};

struct Stack {
    Node* top;
    int size;
};

// Инициализация стека
void initStack(Stack& stack) {
    stack.top = nullptr;
    stack.size = 0;
}

// Очистка стека (освобождение памяти)
void clearStack(Stack& stack) {
    while (stack.top != nullptr) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
    stack.size = 0;
}

// Функция для добавления элемента в стек
void push(Stack& stack, int value) {
    Node* newNode = new Node(value);

    if (stack.top == nullptr) {
        stack.top = newNode;
    }
    else {
        newNode->next = stack.top;
        stack.top = newNode;
    }
    stack.size++;
}

// Функция для удаления элемента из стека
int pop(Stack& stack) {
    if (stack.top == nullptr) {
        std::cout << "Стек пуст!" << std::endl;
        return -1;
    }

    Node* toDelete = stack.top;
    int value = toDelete->key;
    stack.top = stack.top->next;
    delete toDelete;
    stack.size--;

    return value;
}

// Функция для просмотра верхнего элемента
int peek(Stack& stack) {
    if (stack.top == nullptr) {
        std::cout << "Стек пуст!" << std::endl;
        return -1;
    }
    return stack.top->key;
}

// Функция для добавления K элементов в стек
void addToTop(Stack& stack, int K) {
    std::cout << "Введите " << K << " элементов для добавления в стек:" << std::endl;

    for (int i = 0; i < K; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        push(stack, value);
    }

    std::cout << "Добавлено " << K << " элементов в стек" << std::endl;
}

// Функция для удаления K элементов из стека
void removeFromTop(Stack& stack, int K) {
    int removed = 0;

    for (int i = 0; i < K && stack.top != nullptr; i++) {
        int value = pop(stack);
        if (value != -1) {
            removed++;
        }
    }

    std::cout << "Удалено " << removed << " элементов из стека" << std::endl;
}

// Функция для вывода стека
void printStack(Stack& stack) {
    if (stack.top == nullptr) {
        std::cout << "Стек пуст" << std::endl;
        return;
    }

    std::cout << "Стек (размер " << stack.size << "): ";
    Node* current = stack.top;
    while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Функция для получения размера стека
int getSize(Stack& stack) {
    return stack.size;
}

int main() {
    setlocale(LC_ALL, "Ru");

    Stack stack;
    initStack(stack);

    int n, K;

    std::cout << "Введите количество элементов для начального заполнения: ";
    std::cin >> n;

    std::cout << "Введите " << n << " элементов:" << std::endl;
    for (int i = 0; i < n; i++) {
        int value;
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> value;
        push(stack, value);
    }

    std::cout << "\nНачальный ";
    printStack(stack);

    std::cout << "\nВведите количество элементов для удаления (K): ";
    std::cin >> K;

    removeFromTop(stack, K);
    std::cout << "После удаления ";
    printStack(stack);

    std::cout << "\nВведите количество элементов для добавления в стек (K): ";
    std::cin >> K;

    addToTop(stack, K);
    std::cout << "Итоговый ";
    printStack(stack);

    // Освобождаем память перед завершением программы
    clearStack(stack);

    return 0;
}