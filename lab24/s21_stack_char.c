#include "s21_stack_char.h"

//Инициализация стека
void s21_init_stack_char(s21_stack_char *stack) {
    stack->chars = (char **) calloc(256, sizeof(char));
    stack->size = 0;
    stack->is_x = 0;
    stack->is_correct = 1;
}

//Добавления нового значения в стек
void s21_push_stack_char(s21_stack_char *stack, char *symbols) {
    stack->chars[(stack->size)++] = symbols;
}

//Проверка на пустоту стека
int s21_is_empty_stack_char(s21_stack_char stack) {
    char res = 0;
    if (stack.size <= 0)
        res++;
    return res;
}


//Изъятие верхнего значения в стеке
char *s21_pop_stack_char(s21_stack_char *stack) { // присваивать и потом чистить
    char *res;
    if (stack->size == 0) {
        res = NULL;;
    } else {
        res = stack->chars[--(stack->size)];
    }
    return res;
}


//Просмотр верхнего значения стека
char *s21_show_top_char(s21_stack_char *stack) {
    char *res;
    if (s21_is_empty_stack_char(*stack)) {
        res = NULL;
    } else {
        res = stack->chars[stack->size - 1];
    }
    return res;
}


//Очистка стека
void s21_remove_stack_char(s21_stack_char *stack) {
    for (int i = 0; i < stack->size; ++i) {
        free(stack->chars[i]);
    }
    stack->size = 0;
    stack->is_x = 0;
    free(stack->chars);
}


//Переворачивание стека
void s21_reverse_stack_char(s21_stack_char *stack) {
    for (int i = 0, j = stack->size - 1; i < j; ++i, --j) {
        char *tmp = stack->chars[i];
        stack->chars[i] = stack->chars[j];
        stack->chars[j] = tmp;
    }
}

//Копирование стека
void s21_copy_stack(s21_stack_char stack_src, s21_stack_char *stack_dst) {
    stack_dst->size = stack_src.size;
    stack_dst->chars = (char **) calloc(stack_dst->size, sizeof(char *));
    stack_dst->is_x = stack_src.is_x;
    for (int i = 0; i < stack_dst->size; ++i) {
        stack_dst->chars[i] =
                (char *) calloc(strlen(stack_src.chars[i]), sizeof(char));
        strcpy(stack_dst->chars[i], stack_src.chars[i]);;
    }
    stack_dst->is_correct = stack_src.is_correct;
}

//Указание на ошибку
void s21_ERROR(s21_stack_char *stack) { stack->is_correct = 0; }