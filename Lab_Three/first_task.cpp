#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

double findMax(const double arr[], int size) {
    double maximum = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > maximum) maximum = arr[i];
    }
    return maximum;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    double x[20], y[15];
    cout << "Введите 20 элементов массива X: ";
    for (int i = 0; i < 20; ++i) {
        if (!(cin >> x[i]) || !isfinite(x[i])) {
            cout << "Ошибка ввода.\n";
            return 1;
        }
    }

    cout << "Введите 15 элементов массива Y: ";
    for (int i = 0; i < 15; ++i) {
        if (!(cin >> y[i]) || !isfinite(y[i])) {
            cout << "Ошибка ввода.\n";
            return 1;
        }
    }

    double xMax = findMax(x, 20);
    double yMax = findMax(y, 15);
    cout << "Максимум X: " << xMax << '\n';
    cout << "Максимум Y: " << yMax << '\n';

    if (xMax == 0 || yMax == 0) {
        cout << "Вычисление невозможно: знаменатель равен нулю.\n";
        return 1;
    }

    // z = (e^|xMax| - e^|yMax|) / sqrt(|xMax * yMax|).
    double z = (exp(fabs(xMax)) - exp(fabs(yMax)))
               / sqrt(fabs(xMax * yMax));
    if (!isfinite(z)) {
        cout << "Результат выходит за диапазон типа double.\n";
        return 1;
    }

    cout << "z = " << z << '\n';
    return 0;
}
