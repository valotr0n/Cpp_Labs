#include <iostream>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include <cmath>
#include <vector>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        try {
            int n;
            double a, b;
            cout << "Введите размер массива (1..100000): ";
            if (!(cin >> n) || n < 1 || n > 100000)
                throw runtime_error("Неверный размер массива.");
            vector<double> arr(n);
            cout << "Введите элементы массива: ";
            for (double& value : arr)
                if (!(cin >> value) || !isfinite(value))
                    throw runtime_error("Нужно ввести конечные числа.");
            cout << "Введите a и b: ";
            if (!(cin >> a >> b) || !isfinite(a) || !isfinite(b) || a > b)
                throw runtime_error("Неверные границы интервала.");
            int maximum = 0;
            double sum = 0;
            bool found = false;
            for (int i = 0; i < n; ++i) {
                if (fabs(arr[i]) > fabs(arr[maximum])) maximum = i;
                if (found) sum += arr[i];
                if (arr[i] > 0) found = true;
            }
            if (!isfinite(sum)) throw runtime_error("Переполнение суммы.");
            cout << "Номер максимального по модулю: " << maximum + 1 << '\n';
            if (found) cout << "Сумма после первого положительного: " << sum << '\n';
            else cout << "Положительных элементов нет.\n";
            int place = 0;
            for (int i = 0; i < n; ++i) {
                if (trunc(arr[i]) >= a && trunc(arr[i]) <= b) {
                    double temp = arr[place];
                    arr[place] = arr[i];
                    arr[i] = temp;
                    ++place;
                }
            }
            cout << "Преобразованный массив: ";
            for (double value : arr) cout << value << ' ';
            cout << '\n';
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
