#include <iostream>
#include <cstring>
#include <string>


using namespace std;

// Определение структуры для самописного вектора
struct MyVector {
    bool* data;      // Динамический массив для хранения битов
    size_t size;     // Размер вектора

    // Конструктор
    MyVector(size_t size) : size(size) {
        data = new bool[size];
        memset(data, 0, size * sizeof(bool)); // Инициализация нулями (по битам)
    }

    // Деструктор
    ~MyVector() {
        delete[] data;
    }

    // Получение значения по индексу
    bool get(size_t index) const {
        return data[index];
    }

    // Установка значения по индексу
    void set(size_t index) {
        data[index] = true;
    }
};

// Определение структуры для фильтра Блума
struct BloomFilter {
    MyVector bitArray;         // Самописный вектор для хранения битов
    size_t numHashFunctions;   // Количество хэш-функций

    // Конструктор
    BloomFilter(size_t size, size_t numHashFunctions)
        : bitArray(size), numHashFunctions(numHashFunctions) {}

    // Хэш-функция 1
    size_t hash1(const string& str) const {
        size_t hash = 0;
        for (char ch : str) {
            hash += ch; // Суммируем ASCII-коды символов
        }
        return hash % bitArray.size; // Возвращаем индекс по модулю размера битового массива
    }

    // Хэш-функция 2
    size_t hash2(const string& str) const {
        size_t hash = 1;
        for (char ch : str) {
            hash *= (ch + 31); // Умножаем на символ, увеличенный на 31
        }
        return hash % bitArray.size; // Возвращаем индекс по модулю размера битового массива
    }

    // Хэш-функция 3: Простой битовый сдвиг
    size_t hash3(const string& str) const {
        size_t hash = 0;
        for (char ch : str) {
            hash = (hash << 5) ^ ch; // Битовый сдвиг влево и XOR с символом
        }
        return hash % bitArray.size; // Возвращаем индекс по модулю размера битового массива
    }

    // Добавление элемента установливаю состояние битов в 1
    void add(const string& str) {
        size_t hashIndex1 = hash1(str); // Получаем индекс из первой хэш-функции
        size_t hashIndex2 = hash2(str); // Получаем индекс из второй хэш-функции
        size_t hashIndex3 = hash3(str); // Получаем индекс из третьей хэш-функции
        bitArray.set(hashIndex1); // Устанавливаем бит по первому индексу
        bitArray.set(hashIndex2); // Устанавливаем бит по второму индексу
        bitArray.set(hashIndex3); // Устанавливаем бит по третьему индексу
    }

    // Проверка принадлежности элемента проверяю состояние битов
    bool contains(const string& str) const {
        size_t hashIndex1 = hash1(str); // Получаем индекс из первой хэш-функции
        size_t hashIndex2 = hash2(str); // Получаем индекс из второй хэш-функции
        size_t hashIndex3 = hash3(str); // Получаем индекс из третьей хэш-функции
        return bitArray.get(hashIndex1) && // Проверяем, установлен ли бит по первому индексу
            bitArray.get(hashIndex2) && // Проверяем, установлен ли бит по второму индексу
            bitArray.get(hashIndex3);    // Проверяем, установлен ли бит по третьему индексу
    }
};

int main() {
    BloomFilter bloomFilter(10, 3); // Создаём фильтр Блума с размером 10 и 3 хэш-функциями

    bloomFilter.add("example1"); // Добавляем строку "example1"
    bloomFilter.add("example2"); // Добавляем строку "example2"
    bloomFilter.add("example3"); // Добавляем строку "example3"

    cout << "Contains example1: " << bloomFilter.contains("example1") << endl; // Проверяем, содержится ли "example1" (должно вернуть true)
    cout << "Contains example4: " << bloomFilter.contains("example2") << endl; // Проверяем, содержится ли "example4" (должно вернуть false или true из-за ложного срабатывания)

    return 0; // Завершаем программу
}
