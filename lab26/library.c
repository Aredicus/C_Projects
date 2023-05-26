#include "library.h"


deque *init_deque(int val) {
    deque *res;
    res = malloc(sizeof(deque));
    if (res == 0) {
        exit(0);
    }
    res->left = NULL;
    res->right = NULL;
    res->val = val;
    res->topLeft = res;
    res->topRight = res;
    res->size = 1;
    return res;
}

void push_back(deque **Deque, int val) {
    if (*Deque != NULL) {
        deque *res = init_deque(val);
        (*Deque)->topRight->right = res;
        res->topLeft = (*Deque)->topLeft;
        res->left = (*Deque)->topRight;
        (*Deque)->topRight = res;
        (*Deque)->size++;
    }
}

void push_front(deque **Deque, int val) {
    if (*Deque != NULL) {
        deque *res = init_deque(val);
        (*Deque)->topLeft->left = res;
        res->topRight = (*Deque)->topRight;
        res->right = (*Deque)->topLeft;
        (*Deque)->topLeft = res;
        (*Deque)->size++;
    }
}

int pop_back(deque **Deque) {
    if (*Deque != NULL) {
        int res = (*Deque)->topRight->val;
        deque *tmp = (*Deque)->topRight;
        if (tmp == (*Deque)->topLeft) {
            free(*Deque);
            *Deque = NULL;
        } else {
            (*Deque)->topRight = tmp->left;
            (*Deque)->topRight->right = NULL;
            free(tmp);
            ((*Deque)->size)--;
        }
        return res;
    } else {
        printf("\nEmpty Deque\nReturn 0\n");
        return 0;
    }
}

int pop_front(deque **Deque) {
    if (*Deque != NULL) {
        int res = (*Deque)->topLeft->val;
        deque *tmp = (*Deque)->topLeft;
        if (tmp == (*Deque)->topRight) {
            free(*Deque);
            *Deque = NULL;
        } else {
            (*Deque)->topLeft = tmp->right;
            (*Deque)->topLeft->left = NULL;
            free(tmp);
            ((*Deque)->size)--;
        }
        return res;
    } else {
        printf("\nEmpty Deque\nReturn 0\n");
        return 0;
    }
}

void destroy_deque(deque **Deque) {
    if ((*Deque)->right != NULL) {
        destroy_deque(&((*Deque)->right));
    }
    free(*Deque);
    *Deque = NULL;
}

deque *merge_deque(deque *Deque1, deque *Deque2) {
    if (Deque1 != NULL && Deque2 != NULL) {
        deque *res = Deque1->val > Deque2->val ? Deque2 : Deque1;
        deque *tmp = res;
        if (tmp->val == Deque1->val) Deque1 = Deque1->right;
        else Deque2 = Deque2->right;
        while (Deque1 != NULL || Deque2 != NULL) {
            if (Deque1 != NULL && Deque2 != NULL) {
                if (Deque1->val > Deque2->val) {
                    tmp->right = Deque2;
                    Deque2 = Deque2->right;
                } else {
                    tmp->right = Deque1;
                    Deque1 = Deque1->right;
                }
                tmp = tmp->right;
            } else if (Deque1 != NULL) {
                tmp->right = Deque1;
                return res;
            } else {
                tmp->right = Deque2;
                return res;
            }
        }
        return res;
    } else if (Deque1 != NULL) {
        return Deque1;
    } else if (Deque2 != NULL) {
        return Deque2;
    } else {
        return NULL;
    }
}

void show_deque(deque *Deque) {
    deque *tmp = Deque->topLeft;
    printf("\n");
    while (tmp != NULL) {
        printf("%d ", tmp->val);
        tmp = tmp->right;
    }
    printf("\n");
}

void cpy_Deq(deque **dst, deque *src) {
    if (src->size != 0) {
        *dst = init_deque(pop_back(&src));
        while (src->size != 0) {
            push_front(dst, pop_back(&src));
        }
    }
}

deque *sort(deque *Deque) { // check
    if (Deque != NULL && Deque->size != 0) {
        deque *cpy;
        cpy_Deq(&cpy, Deque);
        if (cpy->size == 1 || cpy->size == 2) {
            if (cpy->size == 1) return cpy;
            else {
                deque *tmp1 = init_deque(pop_back(&cpy));
                deque *tmp2 = init_deque(pop_back(&cpy));
                deque *res = merge_deque(tmp1, tmp2);
                destroy_deque(&tmp1);
                destroy_deque(&tmp2);
                return res;
            }
        } else {
            int n = cpy->size;
            int mid = n / 2;
            deque *tmp1 = init_deque(pop_back(&cpy));
            for (int i = 1; i < mid; ++i) {
                push_front(&tmp1, pop_back(&cpy));
            }
            deque *tmp2 = init_deque(pop_back(&cpy));
            for (int i = mid + 1; i < n; ++i) {
                push_front(&tmp2, pop_back(&cpy));
            }
            sort(tmp1);
            sort(tmp2);
            deque *res = merge_deque(tmp1, tmp2);
            destroy_deque(&tmp1);
            destroy_deque(&tmp2);
            return res;
        }
    }
    return NULL;
}

void rules() {
    printf("\n1. Создать дек\n");
    printf("2. Добавить в дек вверх\n");
    printf("3. Добавить в дек вниз\n");
    printf("4. Получить из дека сверху\n");
    printf("5. Получить из дека снизу\n");
    printf("6. Показать дек\n");
    printf("7. Вывести сортировку дека\n");
    printf("8. Завершить программу\n");
    printf("\nВведите нужный пункт\n");
}

void error() {
    printf("\n\nЧто-то пошло не так\n");
    printf("Попробуй ещё раз\n");
    printf("Это не жизнь, тут прощаются ошибки\n\n");
}
