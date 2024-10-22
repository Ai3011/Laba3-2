#include <iostream>
#include <cctype>  // Для функции isupper
#include "Array.h" // Самописный массив StringArray

using namespace std;

// Функция для проверки, является ли буква гласной
bool isVowel(char c) {
    c = tolower(c); // Приводим к нижнему регистру для универсальности
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y'; // Проверяем на гласную
}

// Функция для подсчета заглавных букв-гласных (ударений) в слове
int countAccents(const string& word) {
    int count = 0;
    for (char ch : word) {
        if (isupper(ch) && isVowel(ch)) {
            count++;  // Увеличиваем счетчик при встрече заглавной гласной
        }
    }
    return count;
}

// Функция для проверки, есть ли слово с правильным ударением в словаре
bool checkInDictionary(const StringArray& dictionary, const string& word) {
    for (size_t i = 0; i < dictionary.length(); ++i) {
        if (dictionary.get(i) == word) {
            return true;  // Если слово с ударением найдено в словаре
        }
    }
    return false;
}

// Функция для добавления слова в словарь с проверкой корректности ударения
void addWordToDictionary(StringArray& dictionary) {
    string word;
    while (true) {
        cout << "Введите слово с правильным ударением (только одно ударение на гласной): ";
        getline(cin, word);

        int accentCount = 0;
        bool valid = true;

        for (char c : word) {
            if (isupper(c)) { // Если заглавная буква
                if (isVowel(c)) {
                    accentCount++;
                }
                else {
                    valid = false; // Заглавная согласная - ошибка
                    break;
                }
            }
        }

        if (valid && accentCount == 1) {
            dictionary.add(word); // Добавляем слово в словарь
            break;
        }
        else if (accentCount > 1) {
            cout << "Ошибка: в слове должно быть только одно ударение. Попробуйте снова." << endl;
        }
        else if (accentCount == 0) {
            cout << "Ошибка: в слове должно быть одно ударение на гласной букве. Попробуйте снова." << endl;
        }
        else {
            cout << "Ошибка: ударение должно быть на гласной букве. Попробуйте снова." << endl;
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
    while ((pos = line.find(' ')) != string::npos) {
        textWords.add(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    textWords.add(line);  // Добавляем последнее слово

    // Подсчет ошибок
    int errors = 0;
    for (size_t i = 0; i < textWords.length(); ++i) {
        string word = textWords.get(i);
        bool foundInDictionary = false;

        // Проверяем слово по словарю
        for (size_t j = 0; j < dictionary.length(); ++j) {
            if (dictionary.get(j).size() == word.size()) {
                bool isSameWord = true;
                for (size_t k = 0; k < word.size(); ++k) {
                    if (tolower(word[k]) != tolower(dictionary.get(j)[k])) {
                        isSameWord = false;
                        break;
                    }
                }
                if (isSameWord) {
                    foundInDictionary = true;
                    if (dictionary.get(j) == word) {
                        // Найдено правильное ударение
                        break;
                    }
                    else {
                        // Слово есть, но ударение неверное
                        errors++;
                        break;
                    }
                }
            }
        }

        if (!foundInDictionary) {
            // Если слова нет в словаре, проверяем количество ударений
            int accentCount = countAccents(word);
            if (accentCount != 1) {
                errors++;  // Ошибка, если ударений нет или их больше одного
            }
        }
    }

    // Вывод результата
    cout << "Количество ошибок: " << errors << endl;

    return 0;
}
