#ifndef STACK_H
#define STACK_H

#include <string>

#include "List.h" // Подключение заголовка LinkedList

// Структура стека
struct Stack {
    LinkedList list; // Объект списка для хранения элементов стека

    // Добавление элемента в стек
    void push(const std::string& element) {
        list.addHead(element); // Добавляем элемент в начало списка (вершина стека)
    }

    // Удаление элемента из стека
    void pop() {
        list.removeHead(); // Удаляем элемент с вершины стека
    }

    // Вывод содержимого стека
    void read() const {
        list.read(); // Выводим элементы списка
    }

    // Очистка стека
    void clear() {
        while (list.head) {
            list.removeHead(); // Удаляем все элементы из стека
        }
    }
};

#endif // STACK_H
