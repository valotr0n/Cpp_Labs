#include <iostream>
using namespace std;
const int MAX_SIZE = 100;

int main() {
    int n;
    cout << "Введите размер массива N(до 100): ";
    cin >> n;

    int arr[MAX_SIZE];
    cout << "Введите" << n << "Элементов массива через пробел: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int res = 0;
    for (int i = 1; i < n; i++) {
        if ((arr[i] % 2) == (arr[i - 1] % 2)) {
            res = i + 1;
            break;
        }
    }

    cout << "Результат: " << res << "\n\n";
    return 0;
}