#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        try {
            string text;
            vector<string> words;
            cout << "Введите 2..30 слов, по 2..10 латинских букв (до 1000 байт): ";
            if (!getline(cin, text) || text.size() > 1000)
                throw runtime_error("Ошибка ввода строки.");
            size_t start = text.find_first_not_of(' ');
            while (start != string::npos) {
                size_t end = text.find(' ', start);
                string word = text.substr(start, end - start);
                if (word.size() < 2 || word.size() > 10)
                    throw runtime_error("Длина слова должна быть 2..10.");
                if (word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
                    throw runtime_error("Допустимы только латинские буквы.");
                words.push_back(word);
                if (end == string::npos) break;
                start = text.find_first_not_of(' ', end);
            }
            if (words.size() < 2 || words.size() > 30)
                throw runtime_error("Нужно от 2 до 30 слов.");
            cout << "Слова, отличные от последнего: ";
            bool printed = false;
            for (const string& word : words) {
                if (word != words.back()) {
                    cout << word << ' ';
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
