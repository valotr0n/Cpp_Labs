#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
using namespace std;


bool isVowel(const char* p) {
    const char* vowels[] = {
        "a", "e", "i", "o", "u", "y", "A", "E", "I", "O", "U", "Y",
        "а", "е", "ё", "и", "о", "у", "ы", "э", "ю", "я",
        "А", "Е", "Ё", "И", "О", "У", "Ы", "Э", "Ю", "Я"
    };
    for (const char* v : vowels) {
        const char* letter = p;
        while (*v != '\0' && *letter == *v) {
            ++letter;
            ++v;
        }
        if (*v == '\0') return true;
    }
    return false;
}

bool isSeparator(char c) {
    for (const char* p = " \t\r.,;:!?()\"-"; *p != '\0'; ++p)
        if (c == *p) return true;
    return false;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        try {
            char text[1001];
            cout << "Введите текст (до 1000 байт): ";
            if (!cin.getline(text, 1001)) throw runtime_error("Ошибка ввода строки.");
            char* best = nullptr;
            int maximum = -1;
            char* p = text;
            while (*p != '\0') {
                while (isSeparator(*p)) ++p;
                if (*p == '\0') break;
                char* start = p;
                int count = 0;
                while (*p != '\0' && !isSeparator(*p)) {
                    if (isVowel(p)) ++count;
                    ++p;
                }
                if (*p != '\0') {
                    *p = '\0';
                    ++p;
                }
                if (count > maximum) {
                    maximum = count;
                    best = start;
                }
            }
            if (!best) throw runtime_error("В тексте нет слов.");
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
