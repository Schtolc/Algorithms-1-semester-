/*7_2. Заявки на переговоры.
В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел — начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число — максимальное число заявок.
*/



#include <iostream>
#include <algorithm>
#include <string.h>


using namespace std;


struct hours {
    int begin;
    int end;

    bool operator<(const hours &item) const {
        return (this->end < item.end);
    }
};

class Vector {
private:
    int size;
    int capacity;
    hours *arr;
public:
    Vector() : size(0), capacity(4), arr(NULL) {
        arr = new hours[4];
    }

    ~Vector() {
        delete[] arr;
    }

    int get_size() {
        return size;
    }

    void push_back(hours a) {
        if (size == capacity) {
            grow();
        }
        arr[size++] = a;
    }

    void grow() {
        capacity *= 2;
        hours *tmp = new hours[capacity];
        for (int i = 0; i < size; i++) {
            tmp[i] = arr[i];
        }
        delete[]arr;
        arr = tmp;
    }

    const hours &operator[](int index) {
        return arr[index];
    }

    void my_sort() {
        sort(arr, arr + size);
    }
};


int greed_alg(Vector &times) {
    int amount = 1;

    times.my_sort();
    int max_i = 0;
    for (int i = 1; i < times.get_size(); i++) {
        if (times[i].begin >= times[max_i].end) {
            amount++;
            max_i = i;
        }
    }
    return amount;
}

int main() {

    Vector times;
    hours bufer;
    do {
        cin >> bufer.begin >> bufer.end;
        times.push_back(bufer);
    } while (!cin.eof());

    cout << greed_alg(times);

}