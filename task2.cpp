#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

struct Set {
    int* data;        // Указатель на массив элементов множества
    size_t size;      // Текущий размер множества (количество элементов)
    size_t capacity;  // Вместимость множества (максимальное количество элементов)

    // Конструктор, инициализирующий множество с заданной начальной вместимостью
    Set(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        data = new int[capacity];  // Выделяем память под множество
    }

    // Метод для добавления элемента в множество (SETADD)
    void SETADD(int element) {
        if (SET_AT(element)) {
            cout << "Элемент " << element << " уже существует в множестве." << endl;
            return;  // Элемент уже есть, не добавляем повторно
        }

        if (size >= capacity)
            resize();  // Увеличиваем размер массива при необходимости

        // Находим позицию для вставки элемента
        size_t pos = 0;
        while (pos < size && data[pos] < element) {
            ++pos;  // Ищем место для нового элемента
        }

        // Сдвигаем элементы, чтобы освободить место
        for (size_t j = size; j > pos; --j) {
            data[j] = data[j - 1];
        }

        data[pos] = element;  // Вставляем новый элемент
        ++size;  // Увеличиваем размер
    }

    // Метод для удаления элемента из множества (SETDELL)
    void SETDELL(int element) {
        if (!SET_AT(element)) {
            cout << "Элемент " << element << " не найден, удаление невозможно." << endl;
            return; // Если элемент не найден, выводим сообщение и выходим
        }

        for (size_t i = 0; i < size; ++i) {
            if (data[i] == element) {
                // Сдвигаем элементы влево, удаляя нужный элемент
                for (size_t j = i; j < size - 1; ++j) {
                    data[j] = data[j + 1];
                }
                --size;  // Уменьшаем размер множества
                cout << "Элемент " << element << " удален." << endl; // Сообщение об удалении
                return;
            }
        }
    }

    // Метод для проверки наличия элемента в множестве (SET_AT)
    bool SET_AT(int element) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == element) {
                return true;  // Элемент найден
            }
        }
        return false;  // Элемент не найден
    }

    // Метод для вывода содержимого множества
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";  // Выводим значение элемента
        }
        cout << endl; // Переход на новую строку после вывода
    }

    // Метод для изменения размера множества (динамическое расширение)
    void resize() {
        capacity *= 2;  // Увеличиваем вместимость в 2 раза
        int* newData = new int[capacity];  // Выделяем новую память

        // Копируем старые данные в новый массив
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;  // Освобождаем старый массив
        data = newData;  // Обновляем указатель на новый массив
    }
};

int main() {

    Set set;  // Создаем экземпляр множества
    cout << "\nКоманды для множества (SETADD, SETDEL, SET_AT, PRINT, EXIT): " << endl;
    string setCommand;
    while (true) {
        getline(cin, setCommand);

        if (setCommand == "SETADD") {
            int element;
            cout << "Введите элемент: ";
            cin >> element;
            cin.ignore(); // Игнорируем остаток строки
            set.SETADD(element); // Вызываем метод добавления
        }
        else if (setCommand == "SETDEL") {
            int element;
            cout << "Введите элемент для удаления: ";
            cin >> element;
            cin.ignore(); // Игнорируем остаток строки
            set.SETDELL(element); // Вызываем метод удаления
        }
        else if (setCommand == "SET_AT") {
            int element;
            cout << "Введите элемент для проверки: ";
            cin >> element;
            cin.ignore(); // Игнорируем остаток строки
            if (set.SET_AT(element)) {
                cout << "Элемент " << element << " присутствует в множестве." << endl;
            }
            else {
                cout << "Элемент " << element << " отсутствует в множестве." << endl;
            }
        }
        else if (setCommand == "PRINT") {
            cout << "Элементы в множестве:" << endl;
            set.print();
        }
        else if (setCommand == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
