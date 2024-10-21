#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Структура для реализации упорядоченного множества
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

// Функция для извлечения пар оснований из генома
void extractPairs(const string& genome, Set& set) {
    for (size_t i = 0; i < genome.size() - 1; ++i) {
        // Создаем пару оснований
        int pair = (genome[i] - 'A') * 26 + (genome[i + 1] - 'A'); // Кодируем пару в одно число
        cout << pair << endl;
        set.SETADD(pair);
    }
}

// Функция для подсчета степени близости
int calculateSimilarity(const string& genome1, const string& genome2) {
    Set set1;
    Set set2;

    // Извлекаем пары из обоих геномов
    extractPairs(genome1, set1);
    extractPairs(genome2, set2);

    // Подсчитываем количество пар из первого генома, которые есть во втором
    int similarityCount = 0;
    for (size_t i = 0; i < set1.size; ++i) {
        if (set2.SET_AT(set1.data[i])) {
            similarityCount++;
        }
    }

    return similarityCount;
}

int main() {
    setlocale(LC_ALL, "ru");

    // Ввод геномов
    string genome1, genome2;
    cout << "Введите первый геном: ";
    cin >> genome1;
    cout << "Введите второй геном: ";
    cin >> genome2;

    // Вычисляем степень близости
    int similarity = calculateSimilarity(genome1, genome2);
    cout << "Степень близости: " << similarity << endl;

    return 0;
}
