/*5_4. Вычисление выражения.

Дано выражение в инфиксной записи. Вычислить его, используя перевод выражения в постфиксную запись.
Выражение не содержит отрицительных чисел.

Формат входных данных. ​Строка, состоящая их символов “0123456789­+()"
Гарантируется, что входное выражение корректно, нет деления на 0, вычислимо в целых числах. Деление
целочисленное.

Формат выходных данных.
Значение выражения.*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#define BUFFER 100
#define NUM_LENGTH 10

using namespace std;

struct node {
    int data;
    node* next;
};

struct my_pair {
    int in;
    int out;
};

class Stack {
private:
    node* head;
public:
    Stack() : head(0) {}
    ~Stack();
    void push(int);
    int pop();
    int top() {
        if (head==NULL) {
            return -1;
        }
        return head->data;
    }
};

Stack::~Stack() {
    node* iter = head;
    node* tmp = NULL;
    while (iter) {
        tmp = iter->next;
        delete iter;
        iter = tmp;
    }
}

void Stack::push(int data) {
    node* new_node = new node();
    new_node->next = head;
    new_node->data = data;
    head = new_node;
}

int Stack::pop() {
    if (head==NULL) {
        return -1;
    }
    node* tmp = head->next;
    int  result = head->data;
    delete head;
    head = tmp;
    return result;
}

//returns 1 if a>b in priority
int priority(char a, char b) {
    if (b == '(') {
        return 1;
    }
    else if (a == '/' || a == '*') {
        if (b == '/' || b=='*')
            return 0;
        else if (b == '+' || b == '-')
            return 1;
    } else
        return 0;
    return -1;
}

void read_num(char* in, char* out, my_pair* index) {
    while ('0' <= in[index->in] && in[index->in] <= '9') {
        out[index->out++] = in[index->in++];
    }
    out[index->out++]=' ';
    index->in--;
}

void yard_alg(char *in, char *out) {

    my_pair index;
    index.in = index.out = 0;
    Stack st;

    while (in[index.in] != '\0') {

        //parsing number
        if ('0' <= in[index.in] && in[index.in] <= '9') {
            read_num(in,out,&index);
        }

            //parsing spaces
        else if (isspace(in[index.in]));

            //parsing end brace ")"
        else if (in[index.in] == ')') {
                while (st.top()!= '(') {
                    out[index.out++] = st.pop();
                }
                st.pop();
            }

            //parsing first operand or start brace "("
        else if (st.top() == -1 || in[index.in] == '(') {
            st.push(in[index.in]);
        }

            //parsing operands "^" "U" "/"
        else if (in[index.in] == '-' || tolower(in[index.in]) == '+' || in[index.in] == '/'
                                                                        || in[index.in] == '*') {
            int top = st.top();
            if (priority(in[index.in], top) == 1) {
                st.push(in[index.in]);
            } else if (priority(in[index.in], top) == 0) {
                out[index.out++] = st.pop();
                st.push(in[index.in]);
            }
        }
        index.in++;
    }

    while (st.top() != -1) {
        out[index.out++] = st.pop();
    }
}

char* push_num(char** iter, Stack* st) {
    char buffer[NUM_LENGTH];
    int i = 0;
    while ('0' <= *(*iter) && *(*iter) <= '9') {
        buffer[i++] = *(*iter);
        (*iter)++;
    }
    buffer[i] = '\0';
    st->push(atoi(buffer));
    return *iter;
}

int RPN_alg(char* str) {

    Stack st;
    char *iter = str;
    while (*iter != '\0') {
        if ('0' <= *iter && *iter <= '9') {
            iter = push_num(&iter, &st);
        } else if (*iter == '+') {
            st.push(st.pop() + st.pop());
        } else if (*iter == '-') {
            int tmp = st.pop();
            st.push(st.pop() - tmp);
        } else if (*iter == '*') {
            st.push(st.pop() * st.pop());
        } else if (*iter == '/') {
            int tmp = st.pop();
            st.push(st.pop() / tmp);
        }
        iter++;
    }
    return st.pop();
}


int main() {
    char* str = new char[BUFFER];
    char* yard_str = new char[BUFFER];
    assert(fgets(str, BUFFER, stdin) != NULL);
    yard_alg(str, yard_str);
    //cout << yard_str << endl;
    cout << RPN_alg(yard_str);
    delete [] str;
    delete [] yard_str;
    return 0;
}