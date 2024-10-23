#include <iostream>
#include <cctype>  // Для функции isupper
#include "Array.h" // Самописный массив StringArray

using namespace std;

// Функция для подсчета заглавных букв (ударений) в слове
int countAccents(const string& word) {
    int count = 0;
    for (char ch : word) {
        if (isupper(ch)) {
            count++;  // Увеличиваем счетчик при встрече заглавной буквы
        }
    }
    return count;
}

// Функция для сравнения двух слов с учетом ударения
bool compareWithAccent(const string& word, const string& dictWord) {
    if (word.size() != dictWord.size()) return false;

    for (size_t i = 0; i < word.size(); ++i) {
        if (tolower(word[i]) != tolower(dictWord[i])) {
            return false;  // Слова отличаются
        }
        // Если в словаре на этой позиции заглавная буква, проверяем, что и в тексте заглавная
        if (isupper(dictWord[i]) && word[i] != dictWord[i]) {
            return false;  // Ударение не на той букве
        }
    }
    return true;  // Слова совпадают с учетом ударений
}

// Функция для добавления слова в словарь с проверкой корректности ударения
void addWordToDictionary(StringArray& dictionary) {
    string word;
    while (true) {
        cout << "Введите слово с правильным ударением (только одно ударение): ";
        getline(cin, word);

        int accentCount = countAccents(word);

        if (accentCount == 1) {
            dictionary.add(word); // Добавляем слово в словарь
            break;
        }
        else if (accentCount > 1) {
            cout << "Ошибка: в слове должно быть только одно ударение. Попробуйте снова." << endl;
        }
        else if (accentCount == 0) {
            cout << "Ошибка: в слове должно быть одно ударение. Попробуйте снова." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    StringArray dictionary;  // Массив для хранения словаря
    StringArray textWords;   // Массив для хранения слов из текста

    // Ввод количества слов в словаре
    int n;
    cout << "Введите количество слов в словаре: ";
    cin >> n;
    cin.ignore();  // Игнорируем символ новой строки после ввода числа

    // Ввод слов с правильными ударениями с проверкой
    for (int i = 0; i < n; ++i) {
        addWordToDictionary(dictionary); // Используем функцию для ввода и проверки
    }

    // Ввод текста Пети
    cout << "Введите текст, который Петя написал:" << endl;
    string line;
    getline(cin, line);

    // Разбиение текста на слова и сохранение в массив textWords
    size_t pos = 0;
    while ((pos = line.find_first_of(" \t")) != string::npos) {
        if (pos > 0) {
            textWords.add(line.substr(0, pos));
        }
        line.erase(0, pos + 1);
    }
    if (!line.empty()) {
        textWords.add(line);  // Добавляем последнее слово
    }

    // Подсчет ошибок
    int errors = 0;
    for (size_t i = 0; i < textWords.length(); ++i) {
        string word = textWords.get(i);
        bool foundCorrectAccent = false;

        // Проверяем слово по словарю
        for (size_t j = 0; j < dictionary.length(); ++j) {
            int count = countAccents(word);
            if (compareWithAccent(word, dictionary.get(j))  && count == 1) {
                foundCorrectAccent = true;  // Найдено слово с правильным ударением
                break;
            }
        }

        if (!foundCorrectAccent) {
            // Если слово не найдено в словаре, проверяем количество ударений
            int accentCount = countAccents(word);
            // Ошибка, если слово не найдено в словаре или количество ударений не равно 1
            if (accentCount != 1) {
                errors++;  // Ошибка, если ударений нет или их больше одного
            }
        }
    }

    // Вывод результата
    cout << "Количество ошибок: " << errors << endl;

    return 0;
}
