#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

//Функтор для сравнения строчек начиная с позиции d
class StringCompare {
private:
    int d;
public:
    StringCompare() : d(0) { }

    StringCompare(int D) : d(D) { }

    //Сделал strcmp начиная с позиции d
    bool operator()(const string &left, const string &right) const {
        int s1 = d, s2 = d;
        while (s1 < left.size() && left[s1] == right[s1]) {
            s1++;
            s2++;
        }
        return left[s1] < right[s2];
    }
};

//Сортировка вставками для малых массивов
void insertion_sort(vector<string>::iterator begin, vector<string>::iterator end, StringCompare compFuncor) {
    for (vector<string>::iterator i = begin + 1; i < end; ++i) {
        vector<string>::iterator new_pos = lower_bound(begin, i, *i, compFuncor);
        if (new_pos < i) {
            string tmp = *i;
            for (vector<string>::iterator k = i; k > new_pos; --k)
                *(k) = *(k - 1);
            *new_pos = tmp;
        }
    }
}


void MSD_sort(vector<string> &V, int begin, int end, int d, vector<string> &result) {

    if (end <= begin + 1) return;

    //Если вектор небольшой используем сортировку вставками
    if (end <= begin + 5) {
        insertion_sort(V.begin() + begin, V.begin() + end, StringCompare(d));
        return;
    }

    //Заполняем массив счетчиков и вычисляем в нем "скользящую" сумму
    vector<int> count(257, 0);
    for (int i = begin; i < end; ++i) {
        ++count[V[i][d] + 1];
    }
    for (int i = 1; i < 257; i++) {
        count[i] += count[i - 1];
    }

    //Начиная с конца вектора получаем индекс элемента в упорядоченном векторе result
    //и прибавляем счетчик в массиве счетчиков

    for (int i = end - 1; i >= begin; --i) {
        result[count[V[i][d]]++] = V[i];
    }
    for (int i = begin; i < end; i++) {
        V[i] = result[i - begin];
    }

    //Здесь мы перебираем массив count в котором каждый элемент содержит индекс с которого в массиве V[]
    //лежат символы count[i]+1, т.е. примерный вид массива count[](индексы, значения):
    // |int('/0')  |1                        |2                        |...|255                          |256              |
    // |кол-во '/0'|кол-во char(1) + count[0]|кол-во char(2) + count[1]|...|кол-во char(255) + count[254]|не имеет значения|
    for (int i = 0; i < 255; ++i) {
        MSD_sort(V, begin + count[i], begin + count[i + 1], d + 1, result);
    }
}

int main() {
    vector<string> V;
    string tmp;
    while (!cin.eof()) {
        cin >> tmp;
        V.push_back(tmp);
    }
    V.pop_back();
    vector<string> result(V.size());
    MSD_sort(V, 0, V.size(), 0, result);
    for (int i = 0; i < V.size(); i++) {
        cout << V[i] << endl;
    }

}