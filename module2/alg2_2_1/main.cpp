#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class PriorityQueue {
private:
    vector<int> heap;
    int size;
public:
    PriorityQueue() : size(0) {
        //нулевой элемент массива не учитывается
        heap.push_back(0);
    }

    void insert(int x);
    int pop();
    int top() const {
        return heap[1];
    }
    bool isEmpty() const{
        return size == 0;
    }

};


void PriorityQueue::insert(int x) {
    heap.push_back(x);
    for (int i = size + 1; i > 1;) {
        if (heap[i] > heap[i / 2]) {
            swap(heap[i], heap[i / 2]);
            i = i / 2;
        } else {
            break;
        }
    }
    size++;
}

int PriorityQueue::pop() {
    assert(!isEmpty());
    int result = heap[1];

    swap(heap[size], heap[1]);
    heap.pop_back();

    for (int i = 1; 2 * i < size;) {
        i *= 2;
        if (i + 1 < size && heap[i] < heap[i + 1]) {
            i += 1;
        }
        if (heap[i / 2] < heap[i]) {
            swap(heap[i / 2], heap[i]);
        }
    }
    size--;

    return result;
}

int count_steps(PriorityQueue &P, int k) {
    int result = 0;
    //Вектор взятых яблок при подходе
    vector<int> apples;

    while (!P.isEmpty()) {
        int sum = 0;
        //Берем максимальные яблоки соблюдая грузоподъемность
        do {
            int apple = P.pop();
            sum += apple;
            apples.push_back(apple);
        } while (sum + P.top() <= k && !P.isEmpty());
        //Откусываем от взятых яблок половину и кладем обратно
        for (int i = apples.size() - 1; i >= 0; i--) {
            if (apples[i] != 1) {
                P.insert(apples[i] / 2);
            }
            apples.pop_back();
        }
        result++;
    }
    return result;
}


int main() {
    PriorityQueue P;
    int n = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int apple;
        cin >> apple;
        P.insert(apple);
    }

    int k = 0;
    cin >> k;

    cout << count_steps(P, k);
}