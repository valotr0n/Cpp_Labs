#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <string>
using namespace std;

int countVowels(const string& word) {
    const string vowels[] = {
        "a", "e", "i", "o", "u", "y", "A", "E", "I", "O", "U", "Y",
        "а", "е", "ё", "и", "о", "у", "ы", "э", "ю", "я",
        "А", "Е", "Ё", "И", "О", "У", "Ы", "Э", "Ю", "Я"
    };
    int count = 0;
    for (const string& vowel : vowels) {
        size_t pos = word.find(vowel);
        while (pos != string::npos) {
            ++count;
            pos = word.find(vowel, pos + vowel.size());
        }
    }
    return count;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        try {
            string text, best;
            cout << "Введите текст (до 1000 байт): ";
            if (!getline(cin, text) || text.size() > 1000)
                throw runtime_error("Ошибка ввода строки.");
            string separators = " \t\r.,;:!?()\"-";
            int maximum = -1;
            size_t start = text.find_first_not_of(separators);
            while (start != string::npos) {
                size_t end = text.find_first_of(separators, start);
                string word = text.substr(start, end - start);
                int count = countVowels(word);
                if (count > maximum) {
                    maximum = count;
                    best = word;
                }
                if (end == string::npos) break;
                start = text.find_first_not_of(separators, end);
            }
            if (best.empty()) throw runtime_error("В тексте нет слов.");
            cout << "Слово: " << best << "\nКоличество гласных: " << maximum << '\n';
            return 0;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n1 — повторить, 0 — выйти: ";
            if (cin.eof()) return 1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            int answer = 0;
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (answer != 1) return 1;
        }
    }
}
