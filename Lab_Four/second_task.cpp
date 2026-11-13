#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <windows.h>
using namespace std;

class WordCounter {
    string filename;

    wstring fromUtf8(const string& text) const {
        if (text.empty()) return L"";
        int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                                      text.data(), static_cast<int>(text.size()), nullptr, 0);
        if (size == 0) throw runtime_error("Текст должен быть в кодировке UTF-8.");
        wstring result(size, L'\0');
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                            text.data(), static_cast<int>(text.size()), &result[0], size);
        return result;
    }

    bool isWordChar(wchar_t c) const {
        return (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z')
            || (c >= L'а' && c <= L'я') || (c >= L'А' && c <= L'Я')
            || c == L'ё' || c == L'Ё' || (c >= L'0' && c <= L'9');
    }

public:
    WordCounter(const string& name) : filename(name) {
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt")
            throw runtime_error("Файл должен иметь расширение .txt.");
    }

    size_t count(const string& word) const {
        wstring target = fromUtf8(word);
        if (target.empty()) throw runtime_error("Слово не должно быть пустым.");
        for (wchar_t c : target)
            if (!isWordChar(c)) throw runtime_error("Введите одно слово без знаков препинания.");

        ifstream input(filename);
        if (!input) throw runtime_error("Файл не существует или недоступен для чтения.");
        input.exceptions(ios::badbit);

        size_t result = 0;
        string line;
        while (getline(input, line)) {
            wstring current;
            for (wchar_t c : fromUtf8(line) + L' ') {
                if (isWordChar(c)) {
                    current += c;
                } else {
                    if (current == target) ++result;
                    current.clear();
                }
            }
        }
        return result;
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        string filename, word;
        cout << "Введите имя текстового файла (.txt, UTF-8): ";
        if (!getline(cin, filename)) throw runtime_error("Ввод завершён.");
        cout << "Введите слово (регистр учитывается): ";
        if (!getline(cin, word)) throw runtime_error("Ввод завершён.");

        WordCounter counter(filename);
        size_t count = counter.count(word);
        if (count == 0) cout << "Слово в файле не найдено.\n";
        else cout << "Количество вхождений: " << count << '\n';
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
