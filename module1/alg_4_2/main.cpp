/*Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды
push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 ­ push front
a = 2 ­ pop front
a = 3 ­ push back
a = 4 ­ pop back
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b ­ ожидаемое значение.Если команда pop вызвана для пустой структуры
данных, то ожидается “­1”.
Формат выходных данных.
Требуется напечатать YES ­ если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не
оправдалось, то напечатать NO.

4_2. ​Реализовать дек с динамическим зацикленным буфером.*/

#include <iostream>
#include <langinfo.h>
#include <string.h>

using namespace std;

/*struct node{
    int data;
    node* prev;
    node* next;
};


class Deque {
private:
    node* head;
    node* tail;
public:
    Deque() : head(NULL), tail(NULL) { }
    ~Deque();
    void push_front(int data);
    int pop_front();
    void push_back(int data);
    int pop_back();
};

void Deque::push_front(int data) {
    node *new_node = new node();
    new_node->data = data;
    new_node->prev = head;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
        tail = new_node;
        tail->prev = head;
    } else {
        head->next = new_node;
        head = new_node;
    }
    head->next = tail;

}

int Deque::pop_front() {
    if (head == NULL) {
        return -1;
    }
    node* tmp = head->prev;
    int result = head->data;
    delete head;
    if (tmp == NULL || head == tail) {
        head = tail = NULL;
        return result;
    }
    tmp->next = NULL;
    head = tmp;
    return result;
}

void Deque::push_back(int data) {
    node* new_node = new node();
    new_node->data = data;
    new_node->next = tail;
    new_node->prev = NULL;

    if (tail== NULL) {
        head = new_node;
        tail = new_node;
        head->next = tail;
    } else {
        tail->prev = new_node;
        tail = new_node;
    }
    tail->prev = head;
}

int Deque::pop_back() {
    if (tail == NULL) {
        return -1;
    }
    node* tmp = tail->next;
    int result = tail->data;
    delete tail;
    if (tmp == NULL || head == tail) {
        head = tail = NULL;
        return result;
    }
    tmp->prev = NULL;
    tail = tmp;
    return result;
}

Deque::~Deque() {
    node* iter = head;
    node* tmp = NULL;
    while (iter!=tail) {
        tmp = iter->prev;
        delete iter;
        iter = tmp;
    }
    delete tail;
}*/

#define SIZE 4

class Deque {
private:
    int length;
    int *arr;
    int capacity;
    int head;
    int tail;

public:
    Deque() : length(0), arr(NULL), capacity(SIZE), head(0), tail(0) {
        arr = new int[SIZE];
    }
    ~Deque() {
       delete[] arr;
    }
    void push_front(int data);
    int pop_front();
    void push_back(int data);
    int pop_back();
    void grow();
    void print();
    int& operator[](int &index);

};

//Выпоняет операцию взятия по модулю индекса
//Работает с отрицательными индексами
int& Deque::operator[](int &index) {
    if (index < 0) {
        index = capacity + index;
    } else
        index%=capacity;
    return arr[index];
}

void Deque::print(){

    /*for (int i= 0; i < capacity; i++) {
        cout << arr[i] << " " ;
    }
    cout << endl;*/
}

void Deque::push_front(int data) {
   if (length == capacity-1){
        grow();
    }
    (*this)[tail] = data;
    tail++;
    length++;
    print();
}

void Deque::push_back(int data) {
    if (length == capacity-1){
        grow();
    }
    --head;
    (*this)[head] = data;
    length++;
    print();
}

int Deque::pop_back() {
    if (head%capacity == tail%capacity)
        return -1;

    int result = (*this)[head];
    (*this)[head]=0;
    head++;
    length--;
    print();
    return result;
}

int Deque::pop_front() {
    if (head%capacity == tail%capacity)
        return -1;
    --tail;
    int result = (*this)[tail];
    (*this)[tail]=0;
    length--;
    print();
    return result;
}

void Deque::grow() {
    int new_capacity = capacity*2;
    int *tmp = new int[new_capacity];
    int i = 0;
    int elem = 0;
    while ((elem = this->pop_back()) != -1 ){
        tmp[i] = elem;
        i++;
        length++;
    }
    delete [] arr;
    tail = i;
    head = 0;
    capacity = new_capacity;
    arr=tmp;
}

int main() {
    int size =0;
    cin >> size;
    Deque my_d;

    int command, result;

    for (int i =0 ; i < size; i++) {
        cin >> command >> result;
        switch (command) {
            case 1:
                my_d.push_front(result);
                break;
            case 2:
                if (my_d.pop_front() != result) {
                    cout << "NO";
                    return 0;
                }
                break;
            case 3:
                my_d.push_back(result);
                break;
            case 4:
                if (my_d.pop_back() != result){
                    cout << "NO";
                    return 0;
                }
                break;
        }
    }
    cout << "YES";
    return 0;
}