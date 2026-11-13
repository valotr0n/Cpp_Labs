#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
using namespace std;

bool sameWord(const char* a, const char* b) {
    while (*a != '\0' && *a == *b) {
        ++a;
        ++b;
    }
    return *a == *b;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        try {
            char text[1001];
            char* words[30];
            int count = 0;
            cout << "Введите 2..30 слов, по 2..10 латинских букв (до 1000 байт): ";
            if (!cin.getline(text, 1001)) throw runtime_error("Ошибка ввода строки.");
            char* p = text;
            while (*p != '\0') {
                while (*p == ' ') ++p;
                if (*p == '\0') break;
                if (count == 30) throw runtime_error("Слишком много слов.");
                words[count] = p; 
                ++count;
                int length = 0;
                while (*p != '\0' && *p != ' ') {
                    if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')))
                        throw runtime_error("Допустимы только латинские буквы.");
                    ++length;
                    ++p;
                }
                if (length < 2 || length > 10) throw runtime_error("Длина слова должна быть 2..10.");
                if (*p != '\0') {
                    *p = '\0'; 
                    ++p;
                }
            }
            if (count < 2) throw runtime_error("Нужно хотя бы два слова.");
            cout << "Слова, отличные от последнего: ";
            bool printed = false;
            for (int i = 0; i < count; ++i) {
                if (!sameWord(words[i], words[count - 1])) {
                    cout << words[i] << ' ';
                    printed = true;
                }
            }
            if (!printed) cout << "таких слов нет";
            cout << '\n';
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
