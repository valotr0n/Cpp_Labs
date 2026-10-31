#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int n = 10;
    int *arr = new int[n];

    for (int *i = arr; i < arr + n; ++i) {
        *i = rand() % 61 - 50;
    }
    cout << "Массив: ";
    for (int *i = arr; i < arr + n; ++i) {
        cout << *i << " ";
    }
    cout << endl;

    int sum = 0;
    int count = 0;

    for (int *i = arr; i < arr + n; ++i) {
        if (*i < 0 && *i % 7 ==0) {
            sum += *i;
            count++;
        }
    }
    cout << sum << "/n";
    cout << sum << "/n";
    
    delete[] arr;
}