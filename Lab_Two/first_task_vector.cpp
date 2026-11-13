#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned int>(time(nullptr)));
    while (true) {
        try {
            vector<int> numbers(10);
            int sum7 = 0, count = 0;
            cout << "Массив: ";
            for (int& value : numbers) {
                value = rand() % 101 - 50; 
                cout << value << ' ';
                if (value < 0 && value % 7 == 0) {
                    sum7 += value;
                    ++count;
                }
            }
            cout << "\nСумма: " << sum7 << "\nКоличество: " << count << '\n';
            return 0;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n1 — повторить, 0 — выйти: ";
            if (cin.eof()) return 1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int answer = 0;
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (answer != 1) return 1;
        }
    }
}
