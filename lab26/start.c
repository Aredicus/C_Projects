#include "library.h"

int main() {
    deque *first = NULL;
    int tmp1, tmp3;
    while (1) {
        rules();
        if ((scanf("%d", &tmp1) == 1) && tmp1 >= 1 && tmp1 <= 8) {
            switch (tmp1) {
                case 1:
                    printf("Введите начальное значение: ");
                    if (scanf("%d", &tmp3) == 1) {
                        first = init_deque(tmp3);
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 2:
                    printf("Введите добавляемое значение: ");
                    if (scanf("%d", &tmp3) == 1) {
                        if (first != NULL) {
                            push_front(&first, tmp3);
                        } else {
                            error();
                            fflush(stdin);
                            continue;
                        }
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 3:
                    printf("Введите добавляемое значение: ");
                    if (scanf("%d", &tmp3) == 1) {
                        if (first != NULL) {
                            push_back(&first, tmp3);
                        } else {
                            error();
                            fflush(stdin);
                            continue;
                        }
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 4:
                    if (first != NULL) {
                        printf("\nВ Деке сверху был: %d\n", pop_front(&first));
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 5:
                    if (first != NULL) {
                        printf("\nВ Деке снизу был: %d\n", pop_back(&first));
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 6:
                    if (first != NULL) {
                        show_deque(first);
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 7:
                    if (first != NULL) {
                        deque *tmp = sort(first);
                        show_deque(tmp);
                        destroy_deque(&tmp);
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 8:
                    if (first != NULL) {
                        destroy_deque(&first);
                    }
                    printf("Прощай\n");
                    exit(0);
            }
        } else {
            error();
            fflush(stdin);
            continue;
        }
    }

}