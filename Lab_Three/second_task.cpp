#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

double PowerN(double X, long long N) {
    if (N == 0) return 1;
    if (N < 0) return 1 / PowerN(X, -N);
    if (N % 2 == 0) {
        double half = PowerN(X, N / 2);
        return half * half;
    }
    return X * PowerN(X, N - 1);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    double x;
    int n[5];
    cout << "Введите X: ";
    if (!(cin >> x) || !isfinite(x)) {
        cout << "Ошибка ввода.\n";
        return 1;
    }

    cout << "Введите пять целых показателей степени N: ";
    for (int i = 0; i < 5; ++i) {
        if (!(cin >> n[i])) {
            cout << "Ошибка ввода.\n";
            return 1;
        }
    }

    for (int i = 0; i < 5; ++i) {
        cout << x << " ^ " << n[i] << " = ";
        if (x == 0 && n[i] < 0) {
            cout << "не определено: деление на ноль.\n";
        } else {
            double result = PowerN(x, n[i]);
            if (isfinite(result)) cout << result << '\n';
            else cout << "результат выходит за диапазон типа double.\n";
        }
    }
    return 0;
}
