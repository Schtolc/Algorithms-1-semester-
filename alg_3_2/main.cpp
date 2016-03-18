/*3_2. ​Дан массив целых чисел А[0..n­1]. Известно, что на интервале [0, m] значения массива строго
возрастают, а на интервале [m, n­1] строго убывают. Найти m за O(log m).
n ≤ 10000.*/

#include <iostream>

using namespace std;

int find_m(int *A, int size) {
    int mid = 0;
    int pos = 1;
    //за log(m) ограничиваем последовательность до размера m
    while (A[pos] > A[pos - 1]) {
        if ((pos = pos * 2) > size) {
            break;
        }
    }
    int begin = pos / 2;
    int end = pos > size ? size-1 : pos - 1;

    //за log(m) находим искомый элемент
    while (end != begin) {
        mid = (end - begin) / 2 + begin;
        if (A[mid] < A[mid + 1]) {
            begin = mid+1;
        } else {
            end = mid;
        }
    }
    return begin;
}

int main() {
    int size = 0;
    cin >> size;
    int* A = new int[size];
    for (int i = 0; i < size; i++) {
        cin>> A[i];
    }

    cout << find_m (A, size);

    delete[] A;
    return 0;
}