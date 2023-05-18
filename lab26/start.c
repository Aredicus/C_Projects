#include "library.h"

int main() {
    deque *Deque1 = init_deque(0);
    deque *Deque2 = init_deque(0);
    push_right(&Deque1, 1);
    push_right(&Deque2, 1);
    push_right(&Deque1, 2);
    push_right(&Deque2, 2);
    push_right(&Deque1, 3);
    push_right(&Deque2, 3);
    push_right(&Deque1, 4);
    push_right(&Deque2, 4);
    show_deque(Deque1);
    show_deque(Deque2);
    push_left(&Deque1, -1);
    push_left(&Deque2, -1);
    pop_left(&Deque1);
    pop_left(&Deque2);
    pop_left(&Deque2);
    pop_left(&Deque2);
    pop_left(&Deque2);
    pop_left(&Deque2);
    show_deque(Deque1);
    show_deque(Deque2);
    deque *res = merge_deque(Deque1, Deque2);
    show_deque(res);
}