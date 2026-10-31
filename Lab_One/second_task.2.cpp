#include <iostream>
using namespace std;
const int MAX_SIZE = 100;

int main() {
    int n;
    cout << "Введите размер матрицы N(до 100): ";
    cin >> n;

    int x[MAX_SIZE][MAX_SIZE];
    cout << "Введите " << n * n << " элементов матрицы построчно: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x[i][j];
        }
    }

    int y[MAX_SIZE];
    for (int j = 0; j < n; j++) {
        y[j] = 0;
        for (int i = 0; i < n; i++) {
            y[j] += x[i][j];
        }
    }

    cout << "Массив Y: ";
    for (int j = 0; j < n; j++) {
        cout << y[j] << " ";
    }
    cout << "\n\n";
    return 0;
}
