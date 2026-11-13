#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <windows.h>
using namespace std;

class TextFile {
    string filename;

public:
    TextFile(const string& name) : filename(name) {
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt")
            throw runtime_error("Файл должен иметь расширение .txt.");
    }

    void removeLastLines(int k) {
        ifstream input(filename);
        if (!input) throw runtime_error("Файл не существует или недоступен для чтения.");
        input.exceptions(ios::badbit);

        vector<string> lines;
        string line;
        while (getline(input, line)) lines.push_back(line);
        input.close();

        if (lines.size() < static_cast<size_t>(k)) {
            cout << "В файле меньше " << k << " строк. Файл не изменён.\n";
            return;
        }

        ofstream output;
        output.exceptions(ios::failbit | ios::badbit);
        output.open(filename);
        for (size_t i = 0; i < lines.size() - k; ++i)
            output << lines[i] << '\n';
        output.close();
        cout << "Удалено строк: " << k << '\n';
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        string filename, line;
        cout << "Введите имя файла b (.txt): ";
        if (!getline(cin, filename)) throw runtime_error("Ввод завершён.");
        TextFile file(filename);

        int k;
        while (true) {
            cout << "Введите целое K > 0: ";
            if (!getline(cin, line)) throw runtime_error("Ввод завершён.");
            istringstream input(line);
            char extra;
            if (input >> k && k > 0 && !(input >> extra)) break;
            cout << "Нужно ввести положительное целое число.\n";
        }
        file.removeLastLines(k);
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
