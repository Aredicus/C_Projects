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
    return res;
}

void push_back(deque **Deque, int val) {
    deque *res = init_deque(val);
    res->right = (*Deque);
    if ((*Deque) != NULL) {
        (*Deque)->left = res;
    }
    *Deque = res;
}

void push_front(deque **Deque, int val) {
    deque *res = init_deque(val);
    deque *tmp = (*Deque);
    if (tmp != NULL) {
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        tmp->right = res;
        res->left = tmp;
    } else {
        (*Deque) = res;
    }
}

int pop_back(deque **Deque) {
    if (*Deque != NULL) {
        int res = (*Deque)->val;
        deque *tmp = (*Deque);
        (*Deque) = (*Deque)->right;
        if ((*Deque) != NULL) {
            (*Deque)->left = NULL;
        }
        free(tmp);
        tmp = NULL;
        return res;
    } else {
        printf("\nEmpty Deque\nReturn 0\n");
        return 0;
    }
}

int pop_front(deque **Deque) {
    if (*Deque != NULL) {
        if ((*Deque)->right != NULL) {
            deque *tmp = (*Deque);
            while (tmp->right->right != NULL) {
                tmp = tmp->right;
            }
            int res = tmp->right->val;
            free(tmp->right);
            tmp->right = NULL;
            return res;
        } else {
            int res = (*Deque)->val;
            free((*Deque));
            (*Deque) = NULL;
            return res;
        }
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
    deque *tmp = Deque;
    printf("\n");
    while (tmp != NULL) {
        printf("%d ", tmp->val);
        tmp = tmp->right;
    }
    printf("\n");
}

void rules() {
    printf("1. Создать дек\n");
    printf("2. Добавить в дек вверх\n");
    printf("3. Добавить в дек вниз\n");
    printf("4. Получить из дека сверху\n");
    printf("5. Получить из дека снизу\n");
    printf("6. Показать дек\n");
    printf("7. Вывести дек сортировки двух деков\n");
    printf("8. Завершить программу\n");
    printf("\nВведите нужный пункт\n");
}

void error() {
    printf("Что-то пошло не так\n");
    printf("Попробуй ещё раз\n");
    printf("Это не жизнь, тут прощаются ошибки\n");
}