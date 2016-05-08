#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;


void merge(int *left, int left_size, int *right, int right_size, int *result) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] < right[j]) {
            result[k] = left[i];
            i++;
        } else {
            result[k] = right[j];
            j++;
        }
        k++;
    }

    if (i == left_size) {
        while (j < right_size) {
            result[k++] = right[j++];
        }
    } else {
        while (i < left_size) {
            result[k++] = left[i++];
        }
    }
}


void merge_sort(int *array, int size, int *buffer) {
    if (size == 1)
        return;

    merge_sort(array, size / 2, buffer);
    merge_sort(array + size / 2, size - size / 2, buffer);

    merge(array, size / 2, array + size / 2, size - size / 2, buffer);

    for (int i = 0; i < size; i++) {
        array[i] = buffer[i];
    }
}

int main() {

    int size = 0, k = 0;
    cin >> size >> k;
    int *input = new int[2 * k]();
    int *buffer = new int[2 * k]();

    //Считываем первые k элементов
    for (int i = 0; i < k; i++) {
        cin >> input[i];
    }

    //Читаем части массива по k элементов и сортируем "на месте"
    for (int j = 0; j < size / k - 1; j++) {
        for (int i = 0; i < k; i++) {
            cin >> input[i + k];
        }
        merge_sort(input, 2 * k, buffer);
        for (int i = 0; i < k; i++) {
            cout << input[i] << " ";
        }
        //Первые k элементов отсортированы - сдвигаем input на k элементов влево
        memmove(input, input + k, k * sizeof(int));
    }

    //Досортировываем оставшуюся часть
    for (int i = 0; i < size % k; i++) {
        cin >> input[k + i];
    }
    merge_sort(input, k + size % k, buffer);
    for (int i = 0; i < k + size % k; i++) {
        cout << input[i] << " ";
    }

    delete[]input;
    delete[]buffer;

}