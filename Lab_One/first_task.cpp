#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x,y,z;
    cout << "Введите значение x: ";
    cin >> x;
    cout << "Введите значение y: ";
    cin >> y;
    z = pow(y, 3) - 2*pow(x, 2) + 7*x*y - 4;
    cout << z;
    return 0;
}