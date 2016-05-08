#include <iostream>
#include <vector>

using namespace std;


//Устанваливаем на дату флаг даты рождения - 'b' или смерти - 'e'
struct Date {
    int day;
    int month;
    int year;
    char flag;

    Date() : day(0), month(0), year(0), flag('b') { }

    Date(int d, int m, int y, char f) : day(d), month(m), year(y), flag(f) { }

    bool operator<(const Date &other) const {
        if (year < other.year) {
            return true;
        } else if (year > other.year) {
            return false;
        }
        if (month < other.month) {
            return true;
        } else if (month > other.month) {
            return false;
        }
        return day < other.day;
    }

    bool operator>(const Date &other) const {
//        if (year > other.year) {
//            return true;
//        } else if (year < other.year) {
//            return false;
//        }
//        if (month > other.month) {
//            return true;
//        } else if (month < other.month) {
//            return false;
//        }
//        return day > other.day;
        return other < (*this);
    }
};

void makeHeap(vector<Date> &V) {
    for (int i = (V.size()-1) / 2; i >= 1; --i) {
        for (int j = i; j <= (V.size()-1) / 2;) {
            int k = j * 2;
            if (k + 1 <= (V.size()-1) && V[k] < V[k + 1]) {
                ++k;
            }
            if (V[j] < V[k]) {
                swap(V[k], V[j]);
                j = k;
            } else {
                break;
            }
        }
    }
}

void pop(vector<Date> &V, int size) {
    swap(V[size], V[1]);
    for (int i = 1; 2 * i < size;) {
        i *= 2;
        if (i + 1 < size && V[i] < V[i + 1]) {
            i += 1;
        }
        if (V[i / 2] < V[i]) {
            swap(V[i / 2], V[i]);
        }
    }
}

void heapSort(vector<Date> &V, int size) {
    makeHeap(V);
    for (int i = 0; i < size; i++) {
        pop(V, size - i);
    }
}


//В зависимости от флага добавляем или отнимем количество современников
int count_contemp(vector<Date> &V, int size) {
    int result = 0;
    int current = 0;
    for (int i = 1; i <= size; i++) {
        if (V[i].flag == 'b') {
            current++;
        } else {
            result = max(result, current);
            current--;
        }
    }
    return result;
}

int main() {

    int size = 0;
    cin >> size;
    vector<Date> V;
    V.push_back(Date());

    //Количество не достигших 18летия людей
    int not18amount = 0;

    for (int i = 0; i < size; i++) {

        Date birth, death;
        cin >> birth.day >> birth.month >> birth.year >> death.day >> death.month >> death.year;
        birth.flag = 'b';
        death.flag = 'e';

        //Если человек не достиг 18летия он не добаляется в вектор
        if (death > Date(birth.day, birth.month, birth.year + 18, 'b')) {
            //Если человек умер позже 80, его дата смерти устанавливается в 80
            //Дата рождения устанавливается в 18
            if (death > Date(birth.day, birth.month, birth.year + 80, 'b')) {
                death.year = min(death.year, birth.year + 80);
                death.day = birth.day;
                death.month = birth.month;
            }
            birth.year += 18;
            V.push_back(birth);
            V.push_back(death);
        } else {
            not18amount++;
        }
    }

    size-=not18amount;
    size *= 2;

    heapSort(V, size);

    cout << count_contemp(V, size) << endl;
}