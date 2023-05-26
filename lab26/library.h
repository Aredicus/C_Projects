#ifndef LAB26_LIBRARY_H
#define LAB26_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

struct deque { //дек
    int val;
    struct deque *left;
    struct deque *right;
    struct deque *topLeft;
    struct deque *topRight;
    int size;
} typedef deque;


deque *init_deque(int val); // создание дека по начальному значению

void push_back(deque * *Deque, int
val); // добавление в конец дека

void push_front(deque * *Deque, int
val); // добавление в начала дека

int pop_back(deque * *Deque); // взятие с конца дека

int pop_front(deque * *Deque); // взятие с начала дека

void destroy_deque(deque * *Deque); // утилизация дека

deque *merge_deque(deque * Deque1, deque * Deque2); // создание третьего дека из мержа двух других

void show_deque(deque * Deque); // демонстрация дека

void rules(); // вывод правил

void error(); // вывод ошибки

void tmp(deque * Deque);

deque *sort(deque *Deque);

void cpy_Deq(deque **dst, deque *src);

#endif //LAB26_LIBRARY_H
