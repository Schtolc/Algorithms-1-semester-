//#include <iostream>
#include <algorithm>
#include <deque>
#include <stack>

typedef int BlackInt;

//Сортировка вставками для малых массивов
void insertion_sort(BlackInt *begin, BlackInt *end) {
    for (BlackInt *i = begin + 1; i < end; ++i) {
        BlackInt *new_pos = std::lower_bound(begin, i, *i);
        if (new_pos < i) {
            BlackInt tmp = *i;
            for (BlackInt *k = i; k > new_pos; --k)
                *(k) = *(k - 1);
            *new_pos = tmp;
        }
    }
}


void sort(BlackInt *begin, BlackInt *end) {

    //Алгоритм использует вместо рекурсивных вызовов стек с указателями на начало и конец массивов
    std::stack<BlackInt *> Stack;
    Stack.push(begin);
    Stack.push(end);
    while (!Stack.empty()) {
        BlackInt *right = Stack.top();
        Stack.pop();
        BlackInt *left = Stack.top();
        Stack.pop();

        //Не сортируем массив из одного элемента
        if (right - left <= 1);
            //Оптимизация концевой рекурсии
        else if (right - left <= 10) {
            insertion_sort(left, right);
        } else {

            //В качестве опорных элементов выбираем две медианы
            int third = (right - left) / 3;
            BlackInt *med1 = left + third;
            BlackInt *med2 = right - third - 1;
            if (*med1 < *med2) {
                std::swap(*med1, *left);
                std::swap(*med2, *(right - 1));
            }
            else {
                std::swap(*med1, *(right - 1));
                std::swap(*med2, *left);
            }

            //Алгоритм partition - два опорных элента, два итератора (l и r) двигаются навстречу друг другу, деля
            //массив следующим образом  - | < l | l <= && <= r | < r |
            //при этом итератор l сравнивается с меньшим пивотом, а r с большим
            BlackInt *l = left + 1, *r = right - 2;
            BlackInt *i = left + 1;
            while (i <= r) {
                if (*i < *left)
                    std::swap(*l++, *i++);
                else if (*(right - 1) < *i)
                    std::swap(*i, *r--);
                else i++;
            }

            //Меняем местами пивоты и итераторы l, r
            std::swap(*left, *(--l));
            std::swap(*(right - 1), *(++r));

            //Добавляем в стек указатели на массивы получившиеся при partition
            Stack.push(left);
            Stack.push(l);
            //Если в центральной части разбитого массива есть элементы сортируем и их
            if (*l < *r) {
                Stack.push(l + 1);
                Stack.push(r);
            }
            Stack.push(r + 1);
            Stack.push(right);
        }
    }
}


