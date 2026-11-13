#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <cmath>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        double* arr = nullptr;
        try {
            int n;
            double a, b;
            cout << "Введите размер массива (1..100000): ";
            if (!(cin >> n) || n < 1 || n > 100000)
                throw runtime_error("Неверный размер массива.");
            arr = new double[n];
            cout << "Введите элементы массива: ";
            for (double* p = arr; p < arr + n; ++p)
                if (!(cin >> *p) || !isfinite(*p))
                    throw runtime_error("Нужно ввести конечные числа.");
            cout << "Введите a и b: ";
            if (!(cin >> a >> b) || !isfinite(a) || !isfinite(b) || a > b)
                throw runtime_error("Неверные границы интервала.");
            double* maximum = arr;
            double sum = 0;
            bool found = false;
            for (double* p = arr; p < arr + n; ++p) {
                if (fabs(*p) > fabs(*maximum)) maximum = p;
                if (found) sum += *p;
                if (*p > 0) found = true;
            }
            if (!isfinite(sum)) throw runtime_error("Переполнение суммы.");
            cout << "Номер максимального по модулю: " << maximum - arr + 1 << '\n';
            if (found) cout << "Сумма после первого положительного: " << sum << '\n';
            else cout << "Положительных элементов нет.\n";
            double* place = arr;
            for (double* p = arr; p < arr + n; ++p) {
                if (trunc(*p) >= a && trunc(*p) <= b) {
                    double temp = *place;
                    *place = *p;
                    *p = temp;
                    ++place;
                }
            }
            cout << "Преобразованный массив: ";
            for (double* p = arr; p < arr + n; ++p) cout << *p << ' ';
            cout << '\n';
            delete[] arr;
            return 0;
        } catch (const exception& e) {
            delete[] arr;
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
