#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Coordinate {
    int x;
    int y;

    Coordinate() : x(0), y(0) { }

    Coordinate(int X, int Y) : x(X), y(Y) { }

    bool operator<(const Coordinate &other) {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        }
        return y < other.y;
    }
};

//Функтор для сравнения координат - чтобы хранить в нем координаты начальной точки
class AngleCompare {
private:
    int x_main;
    int y_main;
public:
    AngleCompare() : x_main(0), y_main(0) { }

    AngleCompare(int x, int y) : x_main(x), y_main(y) { }

    bool operator()(const Coordinate &left, const Coordinate &right) const {
        return atan2(left.y - y_main, left.x - x_main) > atan2(right.y - y_main, right.x - x_main);
    }
};

//Находим начальную точку и ставим ее на позицую 0 за O(N)
void place_min_point(vector<Coordinate>::iterator start, vector<Coordinate>::iterator end) {
    vector<Coordinate>::iterator result = start;
    for (vector<Coordinate>::iterator i = start; i < end; ++i) {
        if (*i < *result) {
            result = i;
        }
    }
    swap(*start, *result);
}


//Сортируем вектор по углам за O(NlogN) сравнений
void insertion_sort(vector<Coordinate>::iterator begin, vector<Coordinate>::iterator end, AngleCompare compFuncor) {
    for (vector<Coordinate>::iterator i = begin + 1; i < end; ++i) {
        vector<Coordinate>::iterator new_pos = lower_bound(begin, i, *i, compFuncor);
        if (new_pos < i) {
            Coordinate tmp = *i;
            for (vector<Coordinate>::iterator k = i; k > new_pos; --k)
                *(k) = *(k - 1);
            *new_pos = tmp;
        }
    }
}

int main() {

    vector<Coordinate> A;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Coordinate coordinate;
        cin >> coordinate.x >> coordinate.y;
        A.push_back(coordinate);
    }

    place_min_point(A.begin(), A.end());
    insertion_sort(A.begin() + 1, A.end(), AngleCompare(A[0].x, A[0].y));

    for (int i = 0; i < n; i++) {
        cout << A[i].x << " " << A[i].y << endl;
    }
}