#include <iostream>
#include <vector>


#define ever (;;)

using namespace std;

int partition(vector<int> &V, int begin, int end) {
    swap(V[begin + rand() % (end - begin)], V[begin]);
    int i = end - 1, j = end - 1;
    while (j != begin) {
        if (V[j] >= V[begin]) {
            swap(V[i], V[j]);
            i--;
        }
        j--;
    }
    swap(V[begin], V[i]);
    return i;

}

int find_k(vector<int> &V, int k) {
    int begin = 0, end = V.size();
    for ever {
        int pos = partition(V, begin, end);
        if (pos < k)
            begin = pos + 1;
        else if (pos > k)
            end = pos;
        else return V[k];
    }
}

int main() {
    int size = 0, k = 0;
    cin >> size >> k;
    vector<int> V;
    for (int i = 0; i < size; i++) {
        int tmp;
        cin >> tmp;
        V.push_back(tmp);
    }
    cout << find_k(V, k) << endl;

}