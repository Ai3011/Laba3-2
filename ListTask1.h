#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Узел односвязного списка
struct Node {
    string data;      // Данные узла
    Node* next;       // Указатель на следующий узел

    // Конструктор для инициализации узла
    Node(const string& data) : data(data), next(nullptr) {}
};

// Односвязный список
struct LinkedList {
    Node* head;       // Указатель на первый узел (голову) списка
    Node* tail;       // Указатель на последний узел (хвост) списка
    size_t count;     // Счетчик количества элементов в списке

    // Конструктор, инициализирующий пустой список
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Деструктор для освобождения памяти
    ~LinkedList() {
        clear(); // Очищаем список при уничтожении
    }

    // Метод для добавления элемента в начало списка
    void addHead(const string& element) {
        Node* newNode = new Node(element); // Создаем новый узел
        newNode->next = head; // Новый узел указывает на текущую голову списка
        head = newNode; // Обновляем указатель на голову списка
        if (!tail) tail = head; // Если список был пустым, обновляем указатель на хвост
        count++; // Увеличиваем счетчик
    }

    // Метод для добавления элемента в конец списка
    void addTail(const string& element) {
        Node* newNode = new Node(element); // Создаем новый узел
        if (tail) {
            tail->next = newNode; // Если список не пустой, добавляем новый узел после хвоста
        }
        else {
            head = newNode; // Если список был пустым, обновляем указатель на голову
        }
        tail = newNode; // Обновляем указатель на хвост
        count++; // Увеличиваем счетчик
    }

    // Метод для удаления головы списка
    void removeHead() {
        if (!head) return; // Если список пуст, ничего не делаем
        Node* temp = head; // Сохраняем указатель на текущую голову
        head = head->next; // Перемещаем указатель на следующий узел
        if (!head) tail = nullptr; // Если список стал пустым, обнуляем указатель на хвост
        delete temp; // Освобождаем память текущего узла
        count--; // Уменьшаем счетчик
    }

    // Метод для удаления хвоста списка
    void removeTail() {
        if (!head) return; // Если список пуст, ничего не делаем
        if (head == tail) { // Если в списке только один элемент
            delete head; // Освобождаем память
            head = tail = nullptr; // Обнуляем указатели
            count--; // Уменьшаем счетчик
            return;
        }
        Node* current = head; // Указатель для прохода по списку
        while (current->next != tail) { // Находим узел перед хвостом
            current = current->next; // Перемещаемся к следующему узлу
        }
        delete tail; // Освобождаем память хвоста
        tail = current; // Обновляем указатель на хвост
        tail->next = nullptr; // Убираем указатель на следующий элемент
        count--; // Уменьшаем счетчик
    }

    // Метод для очистки всего списка
    void clear() {
        while (head) {
            removeHead(); // Удаляем все элементы из списка
        }
    }

    // Метод для получения количества элементов в списке
    size_t size() const {
        return count; // Возвращаем текущее количество элементов
    }

    // Метод для вывода элементов списка на экран
    void read() const {
        Node* current = head; // Указатель для прохода по списку
        size_t index = 0; // Индекс текущего элемента
        while (current) {
            cout << index++ << ": " << current->data << endl; // Выводим индекс и данные узла
            current = current->next; // Перемещаемся к следующему узлу
        }
    }

    // Поиск элемента по значению с выводом индекса
    int find(const string& element) const {
        Node* current = head; // Указатель для прохода по списку
        int index = 0; // Индекс текущего элемента
        while (current) {
            if (current->data == element) { // Если элемент найден
                return index; // Возвращаем его индекс
            }
            current = current->next; // Перемещаемся к следующему узлу
            index++;
        }
        return -1; // Элемент не найден, возвращаем -1
    }

    // Удаление элемента по значению
    bool removeByValue(const string& value) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) {
                    previous->next = current->next; // Пропускаем текущий узел
                }
                else {
                    head = current->next; // Удаляем голову
                }
                if (current == tail) { // Если удаляем хвост, обновляем его
                    tail = previous;
                }
                delete current; // Освобождаем память
                count--; // Уменьшаем счетчик
                return true; // Успешное удаление
            }
            previous = current; // Переход к следующему узлу
            current = current->next;
        }
        return false; // Элемент не найден
    }
};

#endif // LIST_H
