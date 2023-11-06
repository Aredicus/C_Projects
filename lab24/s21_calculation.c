#include "s21_calculation.h"

//Функция очистки стека при некорректности для избежания утечек
void s21_time_to_clean_up(s21_stack_char *stackChar) {
    while (!s21_is_empty_stack_char(*stackChar)) {
        char *tmp = s21_pop_stack_char(stackChar);
        free(tmp);
    }
    s21_ERROR(stackChar);
}

//Функция составления дерева выражений
//s21_stack_char *stackChar - Полученный результирующий стек
// Переменная x, если нужно вместо x вставить значение (в данной реализации не используется)
s21_node *s21_calculation(s21_stack_char *stackChar, double *x) {
    //Выводимое дерево
    s21_node *res = NULL;
    //Временный стек
    s21_stack_node TMP;
    //Инициализируем дерево
    s21_init_stack_node(&TMP);
    //Переводим стек в дерево выражений
    while (!s21_is_empty_stack_char(*stackChar)) {
        //Получаем верхнее значение
        char *tmp = s21_pop_stack_char(stackChar);
        //Если число или константа
        if (isdigit(tmp[0]) || *tmp == 'e' || *tmp == 'P') {
            //Пушим во временный стек
            s21_push_stack_node(&TMP, tmp);
        // Если функция
        } else if (isalpha(tmp[0]) && tmp[0] != 'm') {
            //Если во временном стеке ничего нет, значит ошибка
            if (s21_is_empty_stack_node(TMP)) {
                free(tmp);
                s21_time_to_clean_up(stackChar);
                break;
            } else {
                //Иначе пушим во временный стек
                s21_push_stack_node(&TMP, tmp);
            }
        // Если оператор
        } else {
            //Если во временном стеке ничего нет, значит ошибка
            if (s21_is_empty_stack_node(TMP)) {
                free(tmp);
                s21_time_to_clean_up(stackChar);
                break;
            //Если не унарный минус
            } else if (*tmp != '~') {
                // Если во временном стеке меньше 2 чисел, то ошибка
                if (TMP.size < 2) {
                    free(tmp);
                    s21_time_to_clean_up(stackChar);
                    break;
                }
                //Иначе пушим значения
                s21_push_stack_node(&TMP, tmp);
            // Если же унарный минус и стек не пустой, то пушим во временный стек
            } else {
                s21_push_stack_node(&TMP, tmp);
            }
        }
    }
    // Если прошла проверка корректности
    if (stackChar->is_correct == 1) {
        //Переводим стек в вид дерева
        res = s21_pop_stack_node(&TMP);
        //Чистим стек
        s21_remove_stack_node(&TMP);
    }
    //Выводим дерево
    return res;
}


//Функции ниже не используются в данной реализации и необходимы для решения выражения
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