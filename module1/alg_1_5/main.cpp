#include <iostream>

using namespace std;

//Вывести квадраты натуральных чисел от 1 до n используя только O(n)
// операций сложения и вычитания (умножением пользоваться нельзя).


//n^2 == (n-1)^2 + n + n - 1
void write_squares(int n , int* arr) {
    int prev = 0;
    for (int i = 1; i <= n; i++) {
        prev = prev + i + i - 1;
        arr[i-1] = prev;
    }
}

int main() {
    int n = 0;
    cin >> n;
    int* squares = new int[n];

    write_squares(n, squares);

    for (int i = 0; i < n; i++) {
        cout << squares[i] << " ";
    }

    delete [] squares;
    return 0;
}
