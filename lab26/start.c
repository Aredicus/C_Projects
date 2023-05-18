#include "library.h"

int main() {
    deque *first = NULL;
    deque *second = NULL;
    int tmp1, tmp2, tmp3;
    while (1) {
        rules();
        if ((scanf("%d", &tmp1) == 1) && tmp1 >= 1 && tmp1 <= 8) {
            switch (tmp1) {
                case 1:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        printf("Введите начальное значение: ");
                        if (scanf("%d", &tmp3) == 1) {
                            if (tmp2 == 1) {
                                first = init_deque(tmp3);
                            } else {
                                second = init_deque(tmp3);
                            }
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
                case 2:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        printf("Введите добавляемое значение: ");
                        if (scanf("%d", &tmp3) == 1) {
                            if (tmp2 == 1 && first != NULL) {
                                push_front(&first, tmp2);
                            } else if (second != NULL) {
                                push_front(&second, tmp2);
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
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 3:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        printf("Введите добавляемое значение: ");
                        if (scanf("%d", &tmp3) == 1) {
                            if (tmp2 == 1 && first != NULL) {
                                push_back(&first, tmp3);
                            } else if (second != NULL) {
                                push_back(&second, tmp3);
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
                    } else {
                        error();
                        fflush(stdin);
                        continue;
                    }
                    break;
                case 4:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        if (tmp2 == 1 && first != NULL) {
                            printf("\nВ первом деке сверху был: %d\n", pop_front(&first));
                        } else if (second != NULL) {
                            printf("\nВо втором деке сверху был: %d\n", pop_front(&second));
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
                case 5:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        if (tmp2 == 1 && first != NULL) {
                            printf("\nВ первом деке снизу был: %d\n", pop_back(&first));
                        } else if (second != NULL) {
                            printf("\nВо втором деке снизу был: %d\n", pop_back(&second));
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
                case 6:
                    printf("Выберите дек (1 или 2)\n");
                    if (scanf("%d", &tmp2) == 1 && (tmp2 == 1 || tmp2 == 2)) {
                        if (tmp2 == 1 && first != NULL) {
                            show_deque(first);
                        } else if (second != NULL) {
                            show_deque(second);
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
                case 7:
                    if (first != NULL && second != NULL) {
                        deque *tmp = merge_deque(first, second);
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
                    if (second != NULL) {
                        destroy_deque(&second);
                    }
                    printf("Прощай\n");
                    exit(0);git
            }
        } else {
            error();
            fflush(stdin);
            continue;
        }
    }
}