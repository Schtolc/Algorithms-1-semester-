#include <iostream>

//2_3. ​Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество
//таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
//n, m ≤ 100000.


using namespace std;

int find_index_amount(int *A, int Asize, int *B, int Bsize, int k) {
    int amount = 0;

    //Массив B проверяется с конца начиная со значения на котором было равенство
    //в предыдущем сравнении
    int Bborder = Bsize - 1;

    for (int i = 0; i < Asize; i++) {
        for (int j = Bborder; j >= 0; j--) {
            if (A[i] + B[j] == k)
                amount++;
            else if (A[i] + B[j] < k) {
                Bborder = j;
                break;
            }
        }
    }

    return amount;
}


int main() {
    int Asize = 0;
    int Bsize = 0;
    int k = 0;

    cin >> Asize;
    int *A = new int[Asize];
    for (int i = 0; i < Asize; i++) {
        cin >> A[i];
    }

    cin >> Bsize;
    int *B = new int[Bsize];
    for (int i = 0; i < Bsize; i++) {
        cin >> B[i];
    }

    cin >> k;

    cout << find_index_amount(A, Asize, B, Bsize, k);
    delete[] A;
    delete[] B;
}