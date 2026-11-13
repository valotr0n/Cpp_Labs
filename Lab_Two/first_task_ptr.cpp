#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned int>(time(nullptr)));
    while (true) {
        int* numbers = nullptr;
        try {
            numbers = new int[10];
            int sum7 = 0, count = 0;
            cout << "Массив: ";
            for (int* p = numbers; p < numbers + 10; ++p) {
                *p = rand() % 101 - 50; 
                cout << *p << ' ';
                if (*p < 0 && *p % 7 == 0) {
                    sum7 += *p;
                    ++count;
                }
            }
            cout << "\nСумма: " << sum7 << "\nКоличество: " << count << '\n';
            delete[] numbers;
            return 0;
        } catch (const exception& e) {
            delete[] numbers;
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
