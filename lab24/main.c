#include <stdio.h>
#include "s21_calculation.h"
#include "s21_parser.h"

int main() {
    //Выделяем память на вводимую строку
    char *str = calloc(256, sizeof(char));
    //Считываем строку
    scanf("%s", str);
    //Создаем строку состояния
    char *res = calloc(256, sizeof(char));
    res = strcpy(res, "Correct\n");
    //Создаем необходимые структуры:
    //Временный и результирующий стеки
    s21_stack_char TMP, RESULT;
    //Инициализируем их
    s21_init_stack_char(&TMP);
    s21_init_stack_char(&RESULT);
    //Запускаем функцию проверку корректности строки и перевода в стековый вид
    s21_parse(&TMP, &RESULT, str);
    //Если ошибок нет
    if (RESULT.is_correct && TMP.is_correct) {
        //Создаем дерево выражений
        s21_node *result;
        //Создаем ещё один временный стек, куда перезапишем развернутый результирующий стек
        s21_stack_char TMP1;
        s21_reverse_stack_char(&RESULT);
        //Скопируем в результирующий стек его развернутую версию
        s21_copy_stack(RESULT, &TMP1);
        //Создадим дерево выражений
        result = s21_calculation(&TMP1, NULL);
        //Если создалось корректно
        if (TMP1.is_correct == 1) {
            //Выведем дерево
            s21_show_tree(result, 0);
            //Сделаем удаление всех множителей равных 1
            s21_prime(&result);
            // Покажем изменения
            s21_show_tree(result,0);
            //Переведем выражение в обратное состояние
            char *r = reverse(result);
            //Выведем его
            printf("%s\n", r);
            free(r);
        // При различных ошибках выведем соответсвующее значение
        } else if (TMP1.is_correct == 1) {
            res = strcpy(res, "Not correct\n");
        } else {
            res = strcpy(res, "Деление на 0\n");
        }
//Чистим память
        s21_remove_stack_char(&TMP1);
        if(result != NULL) {
            s21_remove_tree(&result);
        }
    } else {
        res = strcpy(res, "Not correct\n");
    }
    printf("%s", res);
    free(res);
    free(str);
    s21_remove_stack_char(&TMP);
    s21_remove_stack_char(&RESULT);
    return 0;
}
