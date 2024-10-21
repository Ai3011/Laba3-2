#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h" // Подключаем ваш односвязный список
#include "Stack.h" // Подключаем ваш стек

using namespace std;

// Функция для проверки возможности завершения всех задач
bool canCompleteTasks(LinkedList& tasks, LinkedList& zav) {
    // Создаем граф зависимостей
    LinkedList graph[26]; // Максимум 26 задач (A-Z)
    int indegree[26] = { 0 }; // Массив для хранения степени входа для каждой задачи

    // ЗаполняеМ зависимостИ
    Node* current = zav.head; // Проходим по зависимостям
    while (current) {
        char from = current->data[0]; // Первая задача (A)
        char to = current->data[1]; // Вторая задача (B)
        int fromIndex = from - 'A'; // Индекс первой задачи
        int toIndex = to - 'A'; // Индекс второй задачи

        graph[fromIndex].addTail(string(1, to)); // Добавляем зависимость
        indegree[toIndex]++; // Увеличиваем степень входа для задачи
        current = current->next; // Переходим к следующей зависимости
    }

    // Инициализируем стек
    Stack stack;

    // Добавляем задачи без зависимостей в стек
    Node* taskNode = tasks.head; // Проходим по задачам
    while (taskNode) {
        int taskIndex = taskNode->data[0] - 'A'; // Получаем индекс задачи
        if (indegree[taskIndex] == 0) {
            stack.push(taskNode->data); // Добавляем задачу в стек
        }
        taskNode = taskNode->next; // Переходим к следующей задаче
    }

    int completedTasks = 0; // Счетчик завершенных задач

    // Обработка стека
    while (stack.list.head != nullptr) { // Пока стек не пуст
        string task = stack.list.head->data; // Получаем верхнюю задачу
        stack.pop(); // Удаляем её из стека
        completedTasks++; // Увеличиваем счетчик завершенных задач

        // Обрабатываем все зависимости для текущей задачи
        int taskIndex = task[0] - 'A'; // Индекс текущей задачи
        Node* dependencyNode = graph[taskIndex].head; // Узел зависимостей
        while (dependencyNode) {
            int dependentIndex = dependencyNode->data[0] - 'A'; // Задача, которая зависит от текущей
            indegree[dependentIndex]--; // Уменьшаем степень входа

            // Если степень входа стала 0, добавляем в стек
            if (indegree[dependentIndex] == 0) {
                stack.push(dependencyNode->data); // Добавляем зависимую задачу в стек
            }
            dependencyNode = dependencyNode->next; // Переходим к следующей зависимости
        }
    }

    // Проверяем, все ли задачи завершены
    return completedTasks == tasks.size();
}

int main() {
    setlocale(LC_ALL, "ru");
    LinkedList tasks;
    LinkedList zav;

    // Ввод задач
    cout << "Введите задачи (например, A, B, C): ";
    string tasksInput;
    getline(cin, tasksInput);

    // Обработка ввода задач
    size_t pos = 0;
    while ((pos = tasksInput.find(',')) != string::npos) {
        string task = tasksInput.substr(0, pos);
        tasks.addTail(task.erase(0, task.find_first_not_of(" "))); // Добавляем в список без пробелов
        tasksInput.erase(0, pos + 1);
    }
    tasks.addTail(tasksInput.erase(0, tasksInput.find_first_not_of(" "))); // Добавляем последний элемент

    // Ввод зависимостей
    cout << "Введите зависимости (например, AB, BC): ";
    string dependenciesInput;
    getline(cin, dependenciesInput);

    // Обработка ввода зависимостей
    pos = 0;
    while ((pos = dependenciesInput.find(',')) != string::npos) {
        string dependency = dependenciesInput.substr(0, pos);
        zav.addTail(dependency.erase(0, dependency.find_first_not_of(" "))); // Добавляем в список без пробелов
        dependenciesInput.erase(0, pos + 1);
    }
    zav.addTail(dependenciesInput.erase(0, dependenciesInput.find_first_not_of(" "))); // Добавляем последний элемент

    // Проверка возможности завершения задач
    if (canCompleteTasks(tasks, zav)) {
        cout << "Возможно завершить все задачи." << endl; // Можно завершить все задачи
    }
    else {
        cout << "Невозможно завершить все задачи." << endl; // Нельзя завершить все задачи
    }

    return 0;
}
