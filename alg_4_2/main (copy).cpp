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

using namespace std;

struct node{
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
    } else {
        head->next = new_node;
        head = new_node;
    }
    //head->next = tail;

}

int Deque::pop_front() {
    if (head == NULL) {
        return -1;
    }
    node* tmp = head->prev;
    int result = head->data;
    delete head;
    if (tmp == NULL) {
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
    } else {
        tail->prev = new_node;
        tail = new_node;
    }
    //tail->prev = head;
}

int Deque::pop_back() {
    if (tail == NULL) {
        return -1;
    }
    node* tmp = tail->next;
    int result = tail->data;
    delete tail;
    if (tmp == NULL) {
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
    while (iter!=NULL) {
        tmp = iter->prev;
        delete iter;
        iter = tmp;
    }
    //delete tail;
}



int main() {
    Deque my_d;
    int amount, command, result;
    cin >> amount;
    for (int i =0; i < amount; i++) {
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
                if (my_d.pop_back() != result) {
                    cout << "NO";
                    return 0;
                }
                break;
        }
    }
    cout << "YES";
    return 0;
}
