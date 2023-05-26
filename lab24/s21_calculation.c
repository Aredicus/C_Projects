#include "s21_calculation.h"

void s21_time_to_clean_up(s21_stack_char *stackChar) {
    while (!s21_is_empty_stack_char(*stackChar)) {
        char *tmp = s21_pop_stack_char(stackChar);
        free(tmp);
    }
    s21_ERROR(stackChar);
}

s21_node *s21_calculation(s21_stack_char *stackChar, double *x) {
    s21_node *res = NULL;
    s21_stack_node TMP;
    s21_init_stack_node(&TMP);
    while (!s21_is_empty_stack_char(*stackChar)) {
        char *tmp = s21_pop_stack_char(stackChar);
        if (isdigit(tmp[0]) || *tmp == 'e' || *tmp == 'P') {
            s21_push_stack_node(&TMP, tmp);
        } else if (isalpha(tmp[0]) && tmp[0] != 'm') {
            if (s21_is_empty_stack_node(TMP)) {
                free(tmp);
                s21_time_to_clean_up(stackChar);
                break;
            } else {
                s21_push_stack_node(&TMP, tmp);
            }
        } else {
            if (s21_is_empty_stack_node(TMP)) {
                free(tmp);
                s21_time_to_clean_up(stackChar);
                break;
            } else if (*tmp != '~') {
                if (TMP.size < 2) {
                    free(tmp);
                    s21_time_to_clean_up(stackChar);
                    break;
                }
                s21_push_stack_node(&TMP, tmp);
            } else {
                s21_push_stack_node(&TMP, tmp);
            }
        }
    }
    if (stackChar->is_correct == 1) {
        res = s21_pop_stack_node(&TMP);
        s21_remove_stack_node(&TMP);
    }
    return res;
}

double s21_get_operator(char *opr, double first, double *second) {
    double res = 0;
    char tmp = *opr;
    switch (tmp) {
        case '~':
            res = -first;
            break;
        case '+':
            res = first + (*second);
            break;
        case '-':
            res = (*second) - first;
            break;
        case '*':
            res = first * (*second);
            break;
        case '/':
            res = (*second) / first;
            break;
        case '^':
            res = pow(*second, first);
            break;
        case 'm':
            res = fmod(*second, first);
            break;
    }
    return res;
}

double s21_get_function(char *fun, double arg) {
    double res = 0;
    char tmp = *fun;
    switch (tmp) {
        case 's':
            if (strcmp(fun, "sin") == 0) {
                res = sin(arg);
            } else
                res = sqrt(arg);
            break;
        case 'c':
            res = cos(arg);
            break;
        case 't':
            res = tan(arg);
            break;
        case 'a':
            if (strcmp(fun, "acos") == 0) {
                res = acos(arg);
            } else if (strcmp(fun, "asin") == 0) {
                res = asin(arg);
            } else {
                res = atan(arg);
            }
            break;
        case 'l':
            if (strcmp(fun, "ln") == 0) {
                res = log(arg);
            } else {
                res = log10(arg);
            }
            break;
    }
    return res;
}