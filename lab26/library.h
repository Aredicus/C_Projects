#ifndef LAB26_LIBRARY_H
#define LAB26_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

struct deque {
    int val;
    struct deque* left;
    struct deque* right;
} typedef deque;


deque* init_deque(int val);
void push_left(deque **Deque, int val);
void push_right(deque **Deque, int val);
int pop_left(deque **Deque);
int pop_right(deque **Deque);
void destroy_deque(deque **Deque);
deque* merge_deque(deque *Deque1, deque *Deque2);
void show_deque(deque *Deque);

#endif //LAB26_LIBRARY_H
